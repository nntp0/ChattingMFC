#pragma once


#include <memory>

#include "Processor.h"

#include "iDisplayModule.h"
#include "iDataModule.h"
#include "iTransmissionServer.h"

class CoreModule : public iServer {

	// Constructor / Destructor
public:
	CoreModule(iDisplayModule*);
	virtual ~CoreModule();

	// Method Override
public:

	// iServer.h
	virtual void Tick();
	virtual void Connect(UID);
	virtual void Disconnect(UID);
	virtual void RecvMessage(std::string msg);

	// Method
public:
	std::shared_ptr<Processor> FindIdleProcessor();

	// Properties ( Modules )	
private:
	std::shared_ptr<iTransmissionServer> transmission;
	iDisplayModule* displayModule;
	std::shared_ptr<iDataModule> dataModule;
	
	std::shared_ptr<Processor> processor;
};