#pragma once

#include <afxsock.h>

#include <Transmission>;

class CClientSocket : public CSocket {

public:
	CClientSocket();
	virtual ~CClientSocket();

public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
private:

	Transmission transmission;
};