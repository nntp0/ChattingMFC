#pragma once
#include <combaseapi.h>

#ifndef __iTransmission_H_INCLUDED__
#define __iTransmission_H_INCLUDED__
__interface iTransmission
{
public:
	virtual void Close() = 0;
	virtual void SetMainFrame(iMainFrame* mainFrame) = 0;
	virtual void Send(CString msg);
	virtual void Receive();
};
#endif