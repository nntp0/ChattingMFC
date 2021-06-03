#pragma once

#include <string>
#include "AMQPSettings.h"
#include "iServer.h"

__interface iTransmissionServer
{
public:
	virtual void Close(UID id) = 0;
	virtual void SendTo(UID id, std::string msg);

	virtual void SetServer(iServer*);
};