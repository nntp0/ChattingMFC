#pragma once

#include <string>
#include "ProtocolSettings.h"

__interface iServer {
public:
	virtual void Tick();
	virtual void Connect(UID);
	virtual void Disconnect(UID);

	virtual void RecvMessage(std::string msg);
};