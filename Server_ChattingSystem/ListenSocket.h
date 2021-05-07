#pragma once
#ifndef __afxsock_H_INCLUDED__
#define __afxsock_H_INCLUDED__
#include <afxsock.h>
#endif

#ifndef __ListenSocket_H_INCLUDED__
#define __ListenSocket_H_INCLUDED__
class CListenSocket : public CSocket
{
public:
	//CListenSocket();
	CListenSocket(SocketTransmission *transmission);
	virtual ~CListenSocket();
public:
	void SetTransmission(SocketTransmission* transmission);
public:
	virtual void OnAccept(int nErrorCode);
private:
	SocketTransmission *transmission;

};
#endif