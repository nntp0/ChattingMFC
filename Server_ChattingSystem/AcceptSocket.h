#pragma once

#include <afxsock.h>

#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
class CAcceptSocket : public CSocket
{
	// Constructor, Destructor
public:
	CAcceptSocket(SocketTransmission*);
	virtual ~CAcceptSocket();

	// Method Override
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	// Methods
public:

	void RecvMsg();
	void SendMsg(CString);

	// Properties
private:
	SocketTransmission *transmission;
	
	UINT id;
	MessageForm m_msg;

	// Getter / Setter
public:
	void SetSocketID(UINT id);
	UINT GetSocketID();

	void SetMsg(MessageForm);
	MessageForm* GetMsg();

	void SetTransmission(SocketTransmission*);
};
#endif