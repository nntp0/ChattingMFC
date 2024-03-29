#pragma once

#include "iTransmission.h"
#include "iApplication.h"

#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "ClientReceiver.h"

class AMQPClient : public iTransmission 
{
	// static memebers
public:
	//static std::shared_ptr<bool> isRunning;

	// Constructor & Destructor
public:
	AMQPClient();
	virtual ~AMQPClient();

	// Method Override
public:
	virtual void Connect();
	virtual void Close();
	virtual void Send(std::string);

	virtual void SetApplication(iApplication* application);

	// Method
public:
	//void RecvThread();
	void MessageDecoding(std::string);

	// properties
private:
	iApplication* application;

	AmqpClient::Channel::ptr_t channelRecvOnly;
	AmqpClient::Channel::ptr_t channelSendOnly;
	std::string messageQueueName;

	UID uid;

	friend class Receiver;
	Receiver receiver;
};