#pragma once
#include <afxsock.h>

#include "ProtocolSettings.h"

class SocketTransmission;

#include "ClientSocket.h"
#include "iMainFrame.h"
#include "iTransmission.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class SocketTransmission : public iTransmission {

public:
	TCHAR buf[256];

public:
	SocketTransmission(iMainFrame* mainFrame);
	~SocketTransmission();

	// Method Override
public:
	virtual void Close();
	virtual void SetMainFrame(iMainFrame* mainFrame);
	virtual void Send(CString msg);
	virtual void Receive();

	// Methods
public:
	CString MessageEncoding(CString msg);
	CString MessageDecoding(CString msg);
	// properties
private:
	CClientSocket* clientSocket;
	iMainFrame* mainFrame;
};
#endif