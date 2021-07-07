#pragma once

#include <string>
#include <memory>

#include "ProtocolSettings.h"

#ifndef __iServer_H_INCLUDED__
#define __iServer_H_INCLUDED__
__interface iServer {
public:
	virtual void Tick();
	virtual void Connect(UID);
	virtual void Disconnect(UID);

	virtual void RecvMessage(std::string msg);
	virtual void ProcCommand(std::string msg);

	virtual void Run();
};
#endif