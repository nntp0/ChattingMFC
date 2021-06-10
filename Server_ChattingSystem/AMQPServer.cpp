#include "pch.h"

#include "AMQPServer.h"

#include <thread>

void AMQPServer::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);

    if (type == "conn") {
        Accept(buffer.substr(4));
    }
    else if (type == "disc") {
        Close(buffer.substr(4));
    }
    else {
        this->server->RecvMessage(buffer);
    }
}
void AMQPServer::SetServer(iServer* server) {
    this->server = server;
}

AMQPServer::AMQPServer() : clientList()
{
    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
    channelRecvOnly = AmqpClient::Channel::Open(ret);
    channelSendOnly = AmqpClient::Channel::Open(ret);

    this->messageQueueName = channelRecvOnly->DeclareQueue("server", false, true, false, false);

    receiver.SetReceiver(this);
    receiver.Start();
}
AMQPServer::~AMQPServer() {
    receiver.Stop();
}

void AMQPServer::Accept(std::string messageQueueName) {
    for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
        if (iter->messageQueueName == messageQueueName) {
            iter->isOpened = true;
            this->server->Connect(iter->uid);
            return;
        }
    }

    ConnectionInfo client(createID(), messageQueueName);
    clientList.push_back(client);

    SendTo(client.uid, "conn" + client.uid);

    this->server->Connect(client.uid);
}
void AMQPServer::Close(UID id) {
    for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
        if (iter->uid == id) {
            this->server->Disconnect(iter->uid);
            iter->isOpened = false;
        }
    }
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
        channelSendOnly->BasicPublish("", targetQueue, AmqpClient::BasicMessage::Create(message));
    }
    else {
        AfxMessageBox(_T("Doesn't Exist"));
    }
}