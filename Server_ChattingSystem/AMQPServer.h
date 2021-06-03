#pragma once

#include "iTransmissionServer.h"
#include "iApplication.h"
#include "SimpleAmqpClient/SimpleAmqpClient.h"

#include <string>

class AMQPServer : public iTransmissionServer
{
	// static memebers
public:
	static std::shared_ptr<bool> isRunning;

	// Constructor & Destructor
public:
	AMQPServer();
	virtual ~AMQPServer();

	// Method Override
public:
	virtual void Accept(std::string);
	virtual void Close(UID id);
	virtual void SendTo(UID id, std::string);
	virtual void ReceiveFrom(UID id, std::string);

	// Methods
public:
	void MessageDecoding(std::string);
	void RecvThread();

	// Properties
private:
	iApplication* application;
	AmqpClient::Channel::ptr_t channel;
	std::string messageQueueName;

	UID sequenceNum;
};