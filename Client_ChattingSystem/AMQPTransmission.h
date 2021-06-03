#pragma once

#include "iTransmission.h"
#include "iApplication.h"

#include "SimpleAmqpClient/SimpleAmqpClient.h"

class AMQPTransmission : public iTransmission {

public:
	AMQPTransmission();
	virtual ~AMQPTransmission();

	// Method Override
public:
	virtual void Connect();
	virtual void Close();
	virtual void Send(std::string);
	virtual void Receive(std::string);


	// Method
public:
	void SetApplication(iApplication* application);

	// properties
private:
	iApplication* application;
	AmqpClient::Channel::ptr_t channel;
	std::string messageQueueName;
};