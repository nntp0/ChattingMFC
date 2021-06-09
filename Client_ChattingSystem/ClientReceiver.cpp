#include "pch.h"
#include "ClientReceiver.h"
#include "AMQPClient.h"


Receiver::Receiver() {}
Receiver::~Receiver() {}

bool Receiver::Job() {

    mainThread->connectionLock.lock();
    std::string consumer_tag = mainThread->channel->BasicConsume(mainThread->messageQueueName, "");
    mainThread->connectionLock.unlock();

    while (onWork) {
        AmqpClient::Envelope::ptr_t envolope;
        mainThread->connectionLock.lock();
        bool check = mainThread->channel->BasicConsumeMessage(consumer_tag, envolope, 50);
        mainThread->connectionLock.unlock();

        if (check) {
            std::string buffer = envolope->Message()->Body();
            mainThread->MessageDecoding(buffer);
        }
        else {

        }
    }
    mainThread->connectionLock.lock();
    mainThread->channel->BasicCancel(consumer_tag);
    mainThread->connectionLock.unlock();

    AfxMessageBox(_T("Dead"));
	return true;
}
void Receiver::SetReceiver(AMQPClient* mainThread) {
    this->mainThread = mainThread;
    YouHaveWork();
}