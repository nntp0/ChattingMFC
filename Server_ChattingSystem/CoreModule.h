#pragma once

#include "iCoreModule.h"
#include "iTransmission.h"
#include "iDisplayModule.h"
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
	std::shared_ptr<iTransmission> transmission;
	iDisplayModule* displayModule;

	// Method
public:
	void DependencyInjection(iDisplayModule*);

	CString MessageEncoding(CString msg);
	CString MessageDecoding(CString msg);
};
#endif