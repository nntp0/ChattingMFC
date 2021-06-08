#pragma once

#include <string>

#include "iServer.h"

#ifndef __iTransmissionServer_H_INCLUDED__
#define __iTransmissionServer_H_INCLUDED__
__interface iTransmissionServer
{
public:
	virtual void Close(UID id) = 0;
	virtual void SendTo(UID id, std::string msg);
	virtual void Accept(std::string);

	virtual void SetServer(iServer*);
};
#endif