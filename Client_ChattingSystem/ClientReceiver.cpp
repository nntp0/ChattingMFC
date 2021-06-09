#include "pch.h"
#include "ClientReceiver.h"
#include "AMQPClient.h"


Receiver::Receiver() {}
Receiver::~Receiver() {}

bool Receiver::Job() {
    std::string consumer_tag = mainThread->channelRecvOnly->BasicConsume(mainThread->messageQueueName, "");

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
void Receiver::SetReceiver(AMQPClient* mainThread) {
    this->mainThread = mainThread;
    YouHaveWork();
}