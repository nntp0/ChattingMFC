#pragma once

#include "iTransmissionModule.h"
#include "iCoreModule.h"

#include <memory>
#include <vector>

class SocketTransmission;

#include "ListenSocket.h"
#include "AcceptSocket.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class SocketTransmission : public iTransmissionModule
{
	// Constructor & Destructor
public:
	SocketTransmission(iCoreModule*);
	virtual ~SocketTransmission();

	// Override Methods
public:
	virtual void Accept();
	virtual void Close(UINT id);

	virtual void SendTo(UINT id, CString);
	virtual void RecvFrom(UINT id, CString);
	
	// Properties
private:
	iCoreModule* pCoreModule;

	CListenSocket* listenSocket;
	std::vector<std::shared_ptr<CAcceptSocket>> acceptSocketList;

	// deprecated
/*public:
	SocketTransmission();
	 
	void Send(CString);
	void Receive(CString);*/
};
#endif