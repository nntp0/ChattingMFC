#pragma once

#include <memory>
#include <queue>

#include "EventSettings.h"

#include "iDisplayModule.h"
#include "iDataModule.h"
#include "iTransmissionServer.h"

#include "NNTPlib.h"

#ifndef __Processor_H_INCLUDED__
#define __Processor_H_INCLUDED__
class Processor : public nntp::thread {

	// Constructor / Destructor
public:
	Processor();
	virtual ~Processor();	

	// Method
public:
	void SetModules(std::shared_ptr<iTransmissionServer>, iDisplayModule*, std::shared_ptr<iDataModule>);
	

	// Helper Methods
private:

	std::string MessageEncoding(ResponseList, ResponseInfo);
	CustomMessage MessageDecoding(std::string);

	// Modules
private:
	std::shared_ptr<iTransmissionServer> transmission;
	iDisplayModule* displayModule = nullptr;
	std::shared_ptr<iDataModule> dataModule;

	// method override
private:
	void ProcessEvent(EventList, std::string args);
	virtual bool Job();

public:
	void RegisterEvent(std::string);

private:
	std::queue<std::string> messageList;
	std::mutex messageListLock;
};
#endif