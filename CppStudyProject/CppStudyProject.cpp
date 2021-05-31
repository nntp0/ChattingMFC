#include "Threading.h"

int main() {
	Threading::run();
}




//#include "SimpleAmqpClient/SimpleAmqpClient.h"
//#include <iostream>
//
//#include <windows.h>
//
//std::string queue_name = "hello";
//
//void TestSend() {
//
//    AmqpClient::Channel::OpenOpts ret;
//    ret.host = std::string("localhost");
//    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
//
//    //Create channel
//    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(ret);
//
//    //Create a queue, the first parameter is the queue name.
//    channel->DeclareQueue(queue_name, false, true, false, false);
//
//    std::string message = "hello,aaron";
//    //The first is the exchange name, and the second parameter is routing_key (this can be understood as the queue to which the message will be sent).
//    channel->BasicPublish("", queue_name, AmqpClient::BasicMessage::Create(message));
//
//    std::cout << "[x] send " << message << std::endl;
//}
//
//void TestRev() {
//
//    AmqpClient::Channel::OpenOpts ret;
//    ret.host = std::string("localhost");
//    ret.auth = AmqpClient::Channel::OpenOpts::BasicAuth("guest", "guest");
//
//    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(ret);
//    channel->DeclareQueue(queue_name, false, true, false, false);
//    //The second parameter is the name of the consumer, and the return value is also the name of the consumer.
//    std::string consumer_tag = channel->BasicConsume(queue_name, "");
//
//    while (1) {
//        AmqpClient::Envelope::ptr_t envelope = channel->BasicConsumeMessage(consumer_tag);
//
//        std::string buffer = envelope->Message()->Body();
//        //The message is placed in the envelope and needs to be parsed
//
//        std::cout << "[y] receve " << buffer << std::endl;
//    }
//
//    channel->BasicCancel(consumer_tag);
//    //Close the consumer.
//}
//
//int main() {
//    TestSend();
//    TestRev();
//}