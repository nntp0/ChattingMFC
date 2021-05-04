#pragma once
#include <afxsock.h>

#include "ProtocolSettings.h"

class Transmission;

#include "ClientSocket.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class Transmission {

public:
	TCHAR buf[256];

public:
	Transmission(); 
	~Transmission();

public:
	void Send(CString msg);
	void Receive();
	void Close();

	// properties
private:
	CClientSocket* clientSocket;
};
#endif