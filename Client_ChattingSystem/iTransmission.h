#pragma once

#include "iApplication.h"
#include "ProtocolSettings.h"
#include <string>

#ifndef __iTransmission_H_INCLUDED__
#define __iTransmission_H_INCLUDED__
__interface iTransmission
{
public:

	virtual void Connect() = 0;
	virtual void Close() = 0;
	virtual void Send(std::string msg);

	virtual void SetApplication(iApplication*);
};
#endif