#pragma once

#include "iMainFrame.h"
#include "iTransmission.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
class AMQPTransmission : public iTransmission {

public:

public:
	AMQPTransmission(iMainFrame* mainFrame);
	~AMQPTransmission();

	// Method Override
public:
	virtual void Close();
	virtual void SetMainFrame(iMainFrame* mainFrame);
	virtual void Send(CString);
	virtual void Receive(CString);

	// Methods
public:
	CString MessageEncoding(CString);
	CString MessageDecoding(CString);
	// properties
private:
	iMainFrame* mainFrame;
};
#endif