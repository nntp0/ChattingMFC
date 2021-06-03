#pragma once

#include "iTransmissionServer.h"
#include "iServer.h"
#include "SimpleAmqpClient/SimpleAmqpClient.h"

#include <string>
#include <vector>

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
	virtual void Close(UID id);
	virtual void SendTo(UID id, std::string);

	virtual void SetServer(iServer*);

	// Methods
public:
	void Accept(std::string);

	void RecvThread();
	void MessageDecoding(std::string);

	// Properties
private:
	iServer* server;

	AmqpClient::Channel::ptr_t channel;
	std::string messageQueueName;

	std::vector<ConnectionInfo> clientList;

	// Helper Method
private:
	UID createID() {
		static int id = 0;
		return std::to_string(id++);
	}
};