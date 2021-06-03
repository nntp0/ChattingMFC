#pragma once

#include "iCoreModule.h"
#include "iTransmissionServer.h"
#include "iDisplayModule.h"
#include "iDataModule.h"
#include <memory>

#ifndef __CoreModule_H_INCLUDED__
#define __CoreModule_H_INCLUDED__
class CoreModule : public iCoreModule, public iServer {

	// Constructor / Destructor
public:
	CoreModule(iDisplayModule*);
	virtual ~CoreModule();

	// Method Override
public:
	// iCore.h
	virtual void CoreModule::EventController(EventList eventID, void* argv);


	// iServer.h
	virtual void Tick();
	virtual void Connect(UID);
	virtual void Disconnect(UID);
	virtual void RecvMessage(std::string msg);


	// Properties ( Modules )	
private:
	std::shared_ptr<iTransmissionServer> transmission;
	iDisplayModule* displayModule;
	std::shared_ptr<iDataModule> dataModule;
	

	// Method
public:
	void DependencyInjection(iDisplayModule*);

	CString MessageEncoding(CustomMessage msg);
	CustomMessage MessageDecoding(CString msg);
};
#endif