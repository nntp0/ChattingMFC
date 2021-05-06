#pragma once
#include <afxsock.h>

#include "ProtocolSettings.h"

class Transmission;

#include "ClientSocket.h"
#include "iMainFrame.h"
#include "iTransmission.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class Transmission : public iTransmission {

public:
	TCHAR buf[256];

public:
	Transmission(iMainFrame* mainFrame);
	~Transmission();

	// Method Override
public:
	virtual void Close();
	virtual void SetMainFrame(iMainFrame* mainFrame);
	virtual void Send(CString msg);
	virtual void Receive();
public:

	// properties
private:
	CClientSocket* clientSocket;
	iMainFrame* mainFrame;
};
#endif