#pragma once

#include <afxsock.h>

#ifndef __ClientSocket_H_INCLUDED__
#define __ClientSocket_H_INCLUDED__
class CClientSocket : public CSocket {
	// Constructor, Destructor
public:
	CClientSocket(Transmission *transmission);
	virtual ~CClientSocket();

	// method override
public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

public:
	void SetTransmission(Transmission* transmission);

	// properties
private:
	Transmission *transmission;
	MessageForm m_msg;

	// Getter, Setter
public:
	void SetMsg(MessageForm msg);
	MessageForm* GetMsg();
};

#endif