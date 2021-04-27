#pragma once
#ifndef __afxsock_H_INCLUDED__
#define __afxsock_H_INCLUDED__
#include <afxsock.h>
#endif
#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
#include "Transmission.h"
#endif

#define SIZE_OF_BUFFER 256
struct MessageForm {
	int messageLen;
	TCHAR message[SIZE_OF_BUFFER];
};


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

