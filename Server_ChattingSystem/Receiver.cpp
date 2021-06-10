#include "pch.h"
#include "Receiver.h"
#include "AMQPServer.h"

Receiver::Receiver() {}
Receiver::~Receiver() {}

bool Receiver::Job() {
    std::string consumer_tag = mainThread->channelRecvOnly->BasicConsume("server", "");

    while (onWork) {
        AmqpClient::Envelope::ptr_t envolope;

        bool check = mainThread->channelRecvOnly->BasicConsumeMessage(consumer_tag, envolope, 50);

        if (check) {
            std::string buffer = envolope->Message()->Body();
            mainThread->MessageDecoding(buffer);
        }
        else {

        }
    }
    mainThread->channelRecvOnly->BasicCancel(consumer_tag);

    return true;
}
void Receiver::SetReceiver(AMQPServer* mainThread) {
    this->mainThread = mainThread;
    YouHaveWork();
}