#pragma once

#include <afxsock.h>

class CClientSocket : public CSocket {

public:
	CClientSocket();
	virtual ~CClientSocket();

public:
	virtual void OnClose(int nErrorCode);
private:
};