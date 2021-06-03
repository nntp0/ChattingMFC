#include "AMQPServer.h"

#include <thread>

std::shared_ptr<bool> AMQPServer::isRunning = std::make_shared<bool>(true);

void recvThread(AMQPServer* mainThread) {
    std::shared_ptr<bool> isRunning = mainThread->isRunning;

    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
    auto channel = AmqpClient::Channel::Open(ret);

    channel->DeclareQueue("listen", false, true, true, false);

    std::string consumer_tag = channel->BasicConsume("listen", "");

    while (isRunning) {
        AmqpClient::Envelope::ptr_t envelope = channel->BasicConsumeMessage(consumer_tag);

        std::string buffer = envelope->Message()->Body();

        mainThread->MessageDecoding(buffer);
    }
    printf("Hello?");
    channel->BasicCancel(consumer_tag);
}

void AMQPServer::MessageDecoding(std::string buffer) {
    std::string type = buffer.substr(0, 4);

    if (type == "conn") {
    }
    else {
    }
}

AMQPServer::AMQPServer()
{
    AmqpClient::Channel::OpenOpts ret;
    ret.host = std::string("localhost");
    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
    channel = AmqpClient::Channel::Open(ret);

    this->messageQueueName = channel->DeclareQueue("server", false, true, false, false);

    std::thread receiver(recvThread, this);
    receiver.detach();
}
AMQPServer::~AMQPServer() {
    *this->isRunning = false;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void AMQPServer::Accept() {
}
void AMQPServer::Close(int socketID) {
}

void AMQPServer::SendTo(int id, std::string) {
    //TRACE(_T("Transmission Send"));

    //AmqpClient::Channel::OpenOpts ret;
    //ret.host = std::string("localhost");
    //ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");

    ////Create channel
    //AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(ret);

    ////Create a queue, the first parameter is the queue name.
    //channel->DeclareQueue(queue_name, false, true, false, false);

    //std::string message(CT2CA((LPCTSTR)msg));
    ////The first is the exchange name, and the second parameter is routing_key (this can be understood as the queue to which the message will be sent).
    //channel->BasicPublish("", queue_name, AmqpClient::BasicMessage::Create(message));

    //AMQPServer::isRunning = false;
}
void AMQPServer::ReceiveFrom(int id, std::string) {
    //TRACE(_T("Transmission Receive"));

    //AfxMessageBox(msg);
}

