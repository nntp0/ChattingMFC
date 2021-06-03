#pragma once

#include "iTransmissionServer.h"
#include "SimpleAmqpClient/SimpleAmqpClient.h"

#include <string>

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
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
	virtual void Accept();
	virtual void Close(int id);
	virtual void SendTo(int id, std::string);
	virtual void ReceiveFrom(int id, std::string);

	// Methods
public:
	void MessageDecoding(std::string);

	// Properties
private:
	AmqpClient::Channel::ptr_t channel;
	std::string messageQueueName;
};
#endif