#pragma once

#include <afxsock.h>

#ifndef __ListenSocket_H_INCLUDED__
#define __ListenSocket_H_INCLUDED__
class CListenSocket : public CSocket
{
public:
	CListenSocket(SocketTransmission *transmission);
	virtual ~CListenSocket();
public:
	void SetTransmission(SocketTransmission* transmission);
public:
	virtual void OnAccept(int nErrorCode);
private:
	SocketTransmission *transmission;

	// deprecated
/*
public:
	CListenSocket();
*/
};
#endif