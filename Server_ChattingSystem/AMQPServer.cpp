#include "pch.h"

#include "AMQPServer.h"

#include <thread>

std::shared_ptr<bool> AMQPServer::isRunning = std::make_shared<bool>(true);

void AMQPServer::RecvThread() {
    std::string consumer_tag = channel->BasicConsume("server", "");

    while (isRunning) {
        AmqpClient::Envelope::ptr_t envolope;
        bool check = channel->BasicConsumeMessage(consumer_tag, envolope, 0);

        if (check) {
            std::string buffer = envolope->Message()->Body();
            MessageDecoding(buffer);
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    channel->BasicCancel(consumer_tag);
}
void AMQPServer::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);
    
    if (type == "conn") {
        AfxMessageBox(_T("login"));
        Accept(buffer.substr(4));
    }
    else {
        AfxMessageBox(_T("message"));
    }
}
void AMQPServer::SetServer(iServer* server) {
    this->server = server;

    this->server->Tick();
}

AMQPServer::AMQPServer() : sequenceNum(0), clientList()
{
    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
    channel = AmqpClient::Channel::Open(ret);

    this->messageQueueName = channel->DeclareQueue("server", false, true, false, false);

    std::thread receiver(&AMQPServer::RecvThread, this);
    receiver.detach();
}
AMQPServer::~AMQPServer() {
    AMQPServer::isRunning = false;
}

void AMQPServer::Accept(std::string messageQueueName) {
    TRACE(_T("SocketTransmission.cpp Accept"));

    //AfxMessageBox(CString::CStringT(CA2CT(messageQueueName.c_str())));
    ConnectionInfo client(++sequenceNum, messageQueueName);
    clientList.push_back(client);

    SendTo(sequenceNum, "conn" + std::to_string(sequenceNum));
    SendTo(sequenceNum, "Hello?");
}
void AMQPServer::Close(UID socketID) {
    TRACE(_T("AcceptSocket Close"));
}

void AMQPServer::SendTo(UID id, std::string message) {

    std::string targetQueue = "";
    for (auto iter = clientList.cbegin(); iter != clientList.cend(); iter++) {
        if (iter->uid == id) {
            if (iter->isOpened)
                targetQueue = iter->messageQueueName;
            break;
        }
    }

    if (targetQueue != "") {
        AfxMessageBox(_T("send"));
        channel->BasicPublish("", targetQueue, AmqpClient::BasicMessage::Create(message));
    }
    else {
        AfxMessageBox(_T("Doesn't Exist"));
    }
}

