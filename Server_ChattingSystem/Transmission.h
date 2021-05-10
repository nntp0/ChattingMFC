#pragma once

#include "iTransmission.h"
#include "ProtocolSettings.h"

#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__
#include <memory>
#endif
#include <vector>

class SocketTransmission;

#include "ListenSocket.h"
#include "AcceptSocket.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class SocketTransmission : public iTransmission
{
	// Constructor & Destructor
public:
	SocketTransmission();
	virtual ~SocketTransmission();

	// Override Methods
public:
	virtual void Accept();
	virtual void Close(UINT portNum);

public:
	void Send(CString);
	void Receive(CString);

	CString MessageEncoding(CString msg);
	CString MessageDecoding(CString msg);
	// Properties
private:
	CListenSocket* listenSocket;
	
	std::vector<std::shared_ptr<CAcceptSocket>> acceptSocketList;
};
#endif