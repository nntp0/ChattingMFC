#pragma once

#include "iTransmissionServer.h"

#include "SimpleAmqpClient/SimpleAmqpClient.h"

#include <vector>

#ifndef __AMQPServer_H_INCLUDED__
#define __AMQPServer_H_INCLUDED__
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
	virtual void Accept(std::string);

	virtual void SetServer(iServer*);

	// Methods
public:
	

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
		char buf[10];
		sprintf_s(buf, 10, "%04d", id++);
		return std::string(buf);
	}
};
#endif