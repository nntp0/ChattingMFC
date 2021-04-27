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

class CAcceptSocket : public CSocket {
public:
	CAcceptSocket();
	CAcceptSocket(Transmission *transmission);
	virtual ~CAcceptSocket();
public:
	void SetTransmission(Transmission* transmission);
private:
	Transmission *transmission;
};