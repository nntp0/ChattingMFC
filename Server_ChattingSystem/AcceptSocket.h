#pragma once

#include <afxsock.h>

#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
class CAcceptSocket : public CSocket
{
	// Constructor, Destructor
public:
	CAcceptSocket(SocketTransmission *transmission);
	virtual ~CAcceptSocket();

	// Method Override
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
public:
	void SetTransmission(SocketTransmission* transmission);
	void SetSocketID(UINT id);

	void RecvMsg();
	void SendMsg(CString);
private:
	SocketTransmission *transmission;
	MessageForm m_msg;

	UINT id;

	// Getter, Setter
public:
	void SetMsg(MessageForm msg);
	MessageForm* GetMsg();

	UINT GetSocketID();
};
#endif