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

public:
	SocketTransmission(iMainFrame* mainFrame);
	~SocketTransmission();

	// Method Override
public:
	virtual void Close();
	virtual void SetMainFrame(iMainFrame* mainFrame);
	virtual void Send(CString);
	virtual void Receive(CString);

	// Methods
public:
	CString MessageEncoding(CString);
	CString MessageDecoding(CString);
	// properties
private:
	CClientSocket* clientSocket;
	iMainFrame* mainFrame;
};
#endif