#pragma once
#ifndef __afxsock_H_INCLUDED__
#define __afxsock_H_INCLUDED__
#include <afxsock.h>
#endif

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	CListenSocket(Transmission *transmission);
	virtual ~CListenSocket();
public:
	void SetTransmission(Transmission* transmission);
public:
	virtual void OnAccept(int nErrorCode);
private:
	Transmission *transmission;
	MessageForm m_msg;
};

