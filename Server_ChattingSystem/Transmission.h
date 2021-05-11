#pragma once

#include "iTransmission.h"
#include "ProtocolSettings.h"

#include <memory>
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
	virtual void Close(UINT id);

	virtual void SendTo(UINT id, CString);
	virtual void RecvFrom(UINT id, CString);
	
	// Properties
private:
	CListenSocket* listenSocket;
	std::vector<std::shared_ptr<CAcceptSocket>> acceptSocketList;

	// deprecated
public:
	//void Send(CString);
	//void Receive(CString);
};
#endif