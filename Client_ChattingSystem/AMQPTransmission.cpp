#include "pch.h"

#include "AMQPTransmission.h"


AMQPTransmission::AMQPTransmission() {
	AmqpClient::Channel::OpenOpts ret;
	ret.host = std::string("localhost");
	ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
	channel = AmqpClient::Channel::Open(ret);

	this->messageQueueName = channel->DeclareQueue("", false, true, true, false);
}


void AMQPTransmission::Connect() {
	channel->BasicPublish("server", "", AmqpClient::BasicMessage::Create(this->messageQueueName));
}
void AMQPTransmission::Close() {}
void AMQPTransmission::Send(std::string  msg) {}
void AMQPTransmission::Receive(std::string  msg) {}


void AMQPTransmission::SetApplication(iApplication* application) {
	this->application = application;
}