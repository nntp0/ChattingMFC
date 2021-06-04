#pragma once

#include <memory>

#include "EventSettings.h"

#include "iDisplayModule.h"
#include "iDataModule.h"
#include "iTransmissionServer.h"


#ifndef __Processor_H_INCLUDED__
#define __Processor_H_INCLUDED__
class Processor {

	// Constructor / Destructor
public:
	Processor();
	virtual ~Processor();
	

	// Method
public:
	void SetModules(std::shared_ptr<iTransmissionServer>, iDisplayModule*, std::shared_ptr<iDataModule>);
	void ProcessEvent(EventList, std::string args);

	// Helper Methods
private:

	std::string MessageEncoding(CustomMessage);
	CustomMessage MessageDecoding(std::string);

	// Modules
private:
	std::shared_ptr<iTransmissionServer> transmission;
	iDisplayModule* displayModule = nullptr;
	std::shared_ptr<iDataModule> dataModule;
};
#endif