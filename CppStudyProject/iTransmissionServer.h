#define USERID unsigned short

#pragma once

#include <string>

__interface iTransmissionServer
{
public:
	virtual void Accept() = 0;
	virtual void Close(USERID id) = 0;
	virtual void SendTo(USERID id, std::string msg);
	virtual void ReceiveFrom(USERID id, std::string msg);
};