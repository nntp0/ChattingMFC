#pragma once
#include <combaseapi.h>

__interface iTransmission
{
public:
	virtual void Accept();
	virtual void Close();
};