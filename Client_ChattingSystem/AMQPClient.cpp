#include "pch.h"

#include "AMQPClient.h"

#include <thread>

void AMQPClient::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);

    if (type == "conn") {
        this->uid = buffer.substr(4);
    }
    else {
        this->application->RecvMessage("sc" + buffer);
    }
}

AMQPClient::AMQPClient() {
	AmqpClient::Channel::OpenOpts ret;
	ret.host = std::string("localhost");
	ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
	channel = AmqpClient::Channel::Open(ret);

	this->messageQueueName = channel->DeclareQueue("", false, true, true, false);

    receiver.SetReceiver(this);
	Connect();
}

AMQPClient::~AMQPClient() {
    Close();
}

void AMQPClient::Connect() {
    connectionLock.lock();
    AfxMessageBox(CString("AMQPClient::Connect Lock"));
	channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("conn") + this->messageQueueName));
    AfxMessageBox(CString("AMQPClient::Connect UnLock"));
    connectionLock.unlock();
    receiver.Start();
}
void AMQPClient::Close() {
    receiver.Stop();
    connectionLock.lock();
    AfxMessageBox(CString("AMQPClient::Close Lock"));
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("disc") + this->uid));
    AfxMessageBox(CString("AMQPClient::Close UnLock"));
    connectionLock.unlock();
}
void AMQPClient::Send(std::string  msg) {
    
    AfxMessageBox(CString("AMQPClient::Send LockWait"));
    connectionLock.lock();
    AfxMessageBox(CString("AMQPClient::Send Lock"));
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(this->uid + msg));
    AfxMessageBox(CString("AMQPClient::Send UnLock"));
    connectionLock.unlock();
}

void AMQPClient::SetApplication(iApplication* application) {
	this->application = application;
}