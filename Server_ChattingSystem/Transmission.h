#pragma once

#include "iTransmissionModule.h"
#include "iCoreModule.h"
#include <string>

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class AMQPTransmission : public iTransmissionModule
{
	// static memebers
public:
	static bool isRunning;

	// Constructor & Destructor
public:
	AMQPTransmission(iCoreModule*);
	virtual ~AMQPTransmission();

	// Override Methods
public:
	virtual void Accept();
	virtual void Close(UINT id);

	virtual void SendTo(UINT id, CString);
	virtual void RecvFrom(UINT id, CString);

	// Methods
public:
	void MessageDecoding(std::string);

	// Properties
private:
	iCoreModule* pCoreModule;
};
#endif