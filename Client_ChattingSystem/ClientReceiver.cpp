#include "pch.h"
#include "ClientReceiver.h"
#include "AMQPClient.h"


Receiver::Receiver() {}
Receiver::~Receiver() {}

bool Receiver::Job() {

    std::string consumer_tag = mainThread->channel->BasicConsume(mainThread->messageQueueName, "");

    while (onWork) {
        AmqpClient::Envelope::ptr_t envolope;
        bool check = mainThread->channel->BasicConsumeMessage(consumer_tag, envolope, 3000);

        if (check) {
            std::string buffer = envolope->Message()->Body();
            //mainThread->MessageDecoding(buffer);
        }
        else {
            AfxMessageBox(_T("No Message"));
        }
    }
    mainThread->channel->BasicCancel(consumer_tag);

	return true;
}
void Receiver::SetReceiver(AMQPClient* mainThread) {
    this->mainThread = mainThread;
    YouHaveWork();
}