#pragma once
#include <afxsock.h>

#include "ClientSocket.h"

class Transmission {

public:
	CClientSocket clientSocket;
	TCHAR buf[256];
	int nbytes;

	CWinThread* m_sender = nullptr;
	CWinThread* m_receiver = nullptr;

public:
	Transmission(); 
	~Transmission();

public:
	void SendMsg(CString msg);
	void RecvMsg();
};