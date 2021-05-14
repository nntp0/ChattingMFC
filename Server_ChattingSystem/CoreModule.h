#pragma once

#include "iCoreModule.h"
#include "iTransmission.h"
#include <memory>

#ifndef __CoreModule_H_INCLUDED__
#define __CoreModule_H_INCLUDED__
class CoreModule : public iCoreModule {

	// Constructor / Destructor
public:
	CoreModule();
	virtual ~CoreModule();

	// Method Override
public:
	virtual void CoreModule::EventController(EventList eventID, void* argv);

	// Properties ( Modules )	
private:
	std::shared_ptr<iTransmission> transmission;

	// Method
public:
	void DependencyInjection();

	CString MessageEncoding(CString msg);
	CString MessageDecoding(CString msg);
};
#endif