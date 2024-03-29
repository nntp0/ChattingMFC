#pragma once

#include <afxsock.h>

#ifndef __ClientSocket_H_INCLUDED__
#define __ClientSocket_H_INCLUDED__
class CClientSocket : public CSocket {
	// Constructor, Destructor
public:
	CClientSocket(SocketTransmission *transmission);
	virtual ~CClientSocket();

	// method override
public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

public:
	void SetTransmission(SocketTransmission* transmission);
	
	void RecvMsg();
	void SendMsg(CString);
	// properties
private:
	SocketTransmission *transmission;
	CString m_msg;

	// Getter, Setter
public:
	void SetMsg(CString msg);
	CString* GetMsg();
};
#endif