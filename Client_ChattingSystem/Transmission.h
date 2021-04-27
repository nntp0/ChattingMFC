#pragma once
#include <afxsock.h>

class Transmission {

public:
	CSocket clientSocket;
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