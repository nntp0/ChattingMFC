#pragma once

#include "iTransmission.h"
#include "ProtocolSettings.h"

#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__
#include <memory>
#endif

class Transmission;

#include "ListenSocket.h"
#include "AcceptSocket.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class Transmission : public iTransmission
{
	// Constructor & Destructor
public:
	Transmission();
	virtual ~Transmission();

	// Override Methods
public:
	virtual void Accept();
	virtual void Close();

public:
	void Receive();

	// Properties
private:
	CListenSocket* listenSocket;
	CAcceptSocket* acceptSocket;
	//CList<std::shared_ptr<CAcceptSocket>, std::shared_ptr<CAcceptSocket>> *acceptSocketList;
};
#endif