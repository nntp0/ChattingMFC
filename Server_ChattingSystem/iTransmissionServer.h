#pragma once

#define UID unsigned int

#include <string>

__interface iTransmissionServer
{
public:
	virtual void Accept(std::string msg) = 0;
	virtual void Close(UID id) = 0;
	virtual void SendTo(UID id, std::string msg);
	virtual void ReceiveFrom(UID id, std::string msg);
};