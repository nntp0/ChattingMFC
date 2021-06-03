#include "pch.h"

#include "AMQPTransmission.h"

#include <thread>

std::shared_ptr<bool> AMQPTransmission::isRunning = std::make_shared<bool>(true);

void AMQPTransmission::RecvThread() {
    std::string consumer_tag = channel->BasicConsume(this->messageQueueName, "");

    while (*isRunning) {
        AmqpClient::Envelope::ptr_t envolope;
        bool check = channel->BasicConsumeMessage(consumer_tag, envolope, 0);

        if (check) {
            std::string buffer = envolope->Message()->Body();
            this->MessageDecoding(buffer);
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    channel->BasicCancel(consumer_tag);
}
void AMQPTransmission::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);

    if (type == "conn") {
        this->uid = buffer.substr(4);
    }
    else {
        this->application->RecvMessage(buffer);
    }
}

AMQPTransmission::AMQPTransmission() {
	AmqpClient::Channel::OpenOpts ret;
	ret.host = std::string("localhost");
	ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
	channel = AmqpClient::Channel::Open(ret);

	this->messageQueueName = channel->DeclareQueue("", false, true, true, false);

	Connect();
}
AMQPTransmission::~AMQPTransmission() {
    Close();
}

void AMQPTransmission::Connect() {
	channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("conn") + this->messageQueueName));

    *AMQPTransmission::isRunning = true;
    std::thread receiver(&AMQPTransmission::RecvThread, this);
    receiver.detach();
}
void AMQPTransmission::Close() {
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("disc") + this->uid));

    *AMQPTransmission::isRunning = false;
}
void AMQPTransmission::Send(std::string  msg) {}

void AMQPTransmission::SetApplication(iApplication* application) {
	this->application = application;
}