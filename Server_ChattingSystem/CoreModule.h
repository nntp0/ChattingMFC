#pragma once

#include "iCoreModule.h"
#include "iTransmissionModule.h"
#include "iDisplayModule.h"
#include "iDataModule.h"
#include <memory>

#ifndef __CoreModule_H_INCLUDED__
#define __CoreModule_H_INCLUDED__
class CoreModule : public iCoreModule {

	// Constructor / Destructor
public:
	CoreModule(iDisplayModule*);
	virtual ~CoreModule();

	// Method Override
public:
	virtual void CoreModule::EventController(EventList eventID, void* argv);

	// Properties ( Modules )	
private:
	std::shared_ptr<iTransmissionModule> transmission;
	iDisplayModule* displayModule;

	std::shared_ptr<iDataModule> dataModule;
	

	// Method
public:
	void DependencyInjection(iDisplayModule*);

	CString MessageEncoding(CustomMessage msg);
	CustomMessage MessageDecoding(CString msg);
};
#endif