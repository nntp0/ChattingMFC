#pragma once

class CListenSocket : public CSocket {
public:
	CListenSocket();
	~CListenSocket();

// Message Processing Methods
public:
	virtual void OnAccept(int nErrorCode);
};