#include "pch.h"

#include "AMQPClient.h"

#include <thread>

void AMQPClient::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);

    if (type == "conn") {
        this->uid = buffer.substr(4);
    }
    else {
        this->application->RecvMessage(buffer);
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
	channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("conn") + this->messageQueueName));
    connectionLock.unlock();
    receiver.Start();
}
void AMQPClient::Close() {
    receiver.Stop();
    connectionLock.lock();
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("disc") + this->uid));
    connectionLock.unlock();
}
void AMQPClient::Send(std::string  msg) {
    connectionLock.lock();
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(this->uid + msg));
    connectionLock.unlock();
}

void AMQPClient::SetApplication(iApplication* application) {
	this->application = application;
}