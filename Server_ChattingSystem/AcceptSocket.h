#pragma once
#ifndef __afxsock_H_INCLUDED__
#define __afxsock_H_INCLUDED__
#include <afxsock.h>
#endif

#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
class CAcceptSocket : public CSocket
{
public:
	CAcceptSocket();
	CAcceptSocket(Transmission *transmission);
	virtual ~CAcceptSocket();
public:
	void SetTransmission(Transmission* transmission);
private:
	Transmission *transmission;
};
#endif