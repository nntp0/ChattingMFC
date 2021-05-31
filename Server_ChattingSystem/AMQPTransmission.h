#pragma once

#include "iTransmissionModule.h"
#include "iCoreModule.h"

#include <memory>
#include <vector>

class AMQPTransmission;

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class AMQPTransmission : public iTransmissionModule
{
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

	// Properties
private:
	iCoreModule* pCoreModule;
};
#endif