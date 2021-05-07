#pragma once
#include <combaseapi.h>

#ifndef __afxsock_H_INCLUDED__
#define __afxsock_H_INCLUDED__
#include <afxsock.h>
#endif

__interface iTransmission
{
public:
	virtual void Accept();
	virtual void Close(UINT id);
};