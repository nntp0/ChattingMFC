#include "pch.h"

#include "Transmission.h"
#include "SimpleAmqpClient/SimpleAmqpClient.h"

#include <thread>

std::string queue_name = "hello";

bool AMQPTransmission::isRunning = true;

void recvThread(AMQPTransmission* mainThread) {

    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");

    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(ret);
    channel->DeclareQueue(queue_name, false, true, false, false);

    std::string consumer_tag = channel->BasicConsume(queue_name, "");

    while (AMQPTransmission::isRunning) {
        AmqpClient::Envelope::ptr_t envelope = channel->BasicConsumeMessage(consumer_tag);

        std::string buffer = envelope->Message()->Body();
        
        mainThread->MessageDecoding(buffer);
    }

    channel->BasicCancel(consumer_tag);
}

void AMQPTransmission::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 2);
    
    if (type == "lg") {
        AfxMessageBox(_T("login"));
        Accept();
    }
    else if (type == "rc") {
        AfxMessageBox(_T("receive"));

    }
    else if (type == "cl") {
        AfxMessageBox(_T("close"));
    }
}

void toggle(AMQPTransmission* thisModule) {

    std::this_thread::sleep_for(std::chrono::seconds(3));
    thisModule->SendTo(1, _T("qr"));
}
AMQPTransmission::AMQPTransmission(iCoreModule* pCoreModule) {
    this->pCoreModule = pCoreModule;

    std::thread threadToggle(toggle, this);
    threadToggle.detach();

    std::thread receiver(recvThread, this);
    receiver.detach();
}
AMQPTransmission::~AMQPTransmission() {
    TRACE("Transmission Destructor");
}

void AMQPTransmission::Accept() {
    TRACE(_T("SocketTransmission.cpp Accept"));

    AfxMessageBox(_T("Accept"));
}
void AMQPTransmission::Close(UINT socketID) {
    TRACE(_T("AcceptSocket Close"));
}

void AMQPTransmission::SendTo(UINT id, CString msg) {
    TRACE(_T("Transmission Send"));

    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");

    //Create channel
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(ret);

    //Create a queue, the first parameter is the queue name.
    channel->DeclareQueue(queue_name, false, true, false, false);

    std::string message(CT2CA((LPCTSTR)msg));
    //The first is the exchange name, and the second parameter is routing_key (this can be understood as the queue to which the message will be sent).
    channel->BasicPublish("", queue_name, AmqpClient::BasicMessage::Create(message));

    AMQPTransmission::isRunning = false;
}
void AMQPTransmission::RecvFrom(UINT id, CString msg) {
    TRACE(_T("Transmission Receive"));

    AfxMessageBox(msg);
}

