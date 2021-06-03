#pragma once

#include "iTransmission.h"
#include "iApplication.h"

#include "SimpleAmqpClient/SimpleAmqpClient.h"

class AMQPTransmission : public iTransmission 
{
	// static memebers
public:
	static std::shared_ptr<bool> isRunning;

	// Constructor & Destructor
public:
	AMQPTransmission();
	virtual ~AMQPTransmission();

	// Method Override
public:
	virtual void Connect();
	virtual void Close();
	virtual void Send(std::string);

	virtual void SetApplication(iApplication* application);

	// Method
public:
	void RecvThread();
	void MessageDecoding(std::string);

	// properties
private:
	iApplication* application;

	AmqpClient::Channel::ptr_t channel;
	std::string messageQueueName;

	UID uid;
};