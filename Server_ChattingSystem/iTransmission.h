#pragma once
#include <combaseapi.h>

__interface iTransmission
{
public:
	virtual void Accept() = 0;
	virtual void Close() = 0;
};