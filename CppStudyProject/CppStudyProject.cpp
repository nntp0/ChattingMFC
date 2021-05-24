#include "RabbitMQ.h"



//#include "MessageControl.h"
//#include "SmartPointer.h"
//#include "pVoidTester.h"

//#include "SpreadsheetCell.h"

int main()
{
    /*MessageControlModule ex1;
    ex1.Test();

    SmartPointerPractice ex2;
    ex2.Test();

    pVoidTester ex3;
    ex3.Test();*/

    //SpreadsheetCell::Test();

    // create an instance of your own connection handler
    MyConnectionHandler myHandler;

    // create a AMQP connection object
    AMQP::Connection connection(&myHandler, AMQP::Login("hi", "hi"), "localhost/5672");

    // and create a channel
    AMQP::Channel channel(&connection);

    // use the channel object to call the AMQP method you like
    channel.declareExchange("my-exchange", AMQP::fanout);
    channel.declareQueue("my-queue");
    channel.bindQueue("my-exchange", "my-queue", "my-routing-key");

    channel.publish("my-exchange", "my-routing-key", "my first message");
}