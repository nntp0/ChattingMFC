#include "pch.h"

#include "AMQPClient.h"

#include <thread>

//std::shared_ptr<bool> AMQPClient::isRunning = std::make_shared<bool>(true);

//void AMQPClient::RecvThread() {
//    std::string consumer_tag = channel->BasicConsume(this->messageQueueName, "");
//
//    while (*isRunning) {
//        AmqpClient::Envelope::ptr_t envolope;
//        bool check = channel->BasicConsumeMessage(consumer_tag, envolope, 0);
//
//        if (check) {
//            std::string buffer = envolope->Message()->Body();
//            this->MessageDecoding(buffer);
//        }
//        else {
//            std::this_thread::sleep_for(std::chrono::seconds(2));
//        }
//    }
//    channel->BasicCancel(consumer_tag);
//    *isRunning = true;
//}
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
	channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("conn") + this->messageQueueName));

    receiver.Start();
}
void AMQPClient::Close() {
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(std::string("disc") + this->uid));

    receiver.Stop();
}
void AMQPClient::Send(std::string  msg) {
    channel->BasicPublish("", "server", AmqpClient::BasicMessage::Create(this->uid + msg));
}

void AMQPClient::SetApplication(iApplication* application) {
	this->application = application;
}