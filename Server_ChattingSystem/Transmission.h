#pragma once

#include "iTransmission.h"
#include "ProtocolSettings.h"

#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__
#include <memory>
#endif

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class Transmission : public iTransmission
{
	// Constructor & Destructor
public:
	Transmission();
	virtual ~Transmission();

	// Methods
public:
	virtual void Accept();

	// Properties
private:
	/*CListenSocket *listenSocket;
	CList<std::shared_ptr<CAcceptSocket>, std::shared_ptr<CAcceptSocket>> *acceptSocketList;*/
};
#endif