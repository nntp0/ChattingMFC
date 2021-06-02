#pragma once

#include <string>

__interface iTransmission
{
public:
	virtual void Connect() = 0;
	virtual void Close() = 0;
	virtual void Send(std::string msg);
	virtual void Receive(std::string msg);
};