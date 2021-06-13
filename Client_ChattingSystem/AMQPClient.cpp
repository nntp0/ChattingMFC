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
	channelRecvOnly = AmqpClient::Channel::Open(ret);
    channelSendOnly = AmqpClient::Channel::Open(ret);

	this->messageQueueName = channelRecvOnly->DeclareQueue("", false, true, true, false);

    receiver.SetReceiver(this);
	Connect();
}

AMQPClient::~AMQPClient() {
    Close();
}

void AMQPClient::Connect() {
    channelSendOnly->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("conn") + this->messageQueueName));
    receiver.Start();
}
void AMQPClient::Close() {
    receiver.Stop();
    channelSendOnly->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("disc") + this->uid));
}
void AMQPClient::Send(std::string  msg) {
    channelSendOnly->BasicPublish("", "server", AmqpClient::BasicMessage::Create(this->uid + msg));
}

void AMQPClient::SetApplication(iApplication* application) {
	this->application = application;
}