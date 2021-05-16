#pragma once

#include "ProtocolSettings.h"

__interface iTransmissionModule
{
public:
	virtual void Accept();
	virtual void Close(UINT id);

	virtual void SendTo(UINT id, CString);
	virtual void RecvFrom(UINT id, CString);
};