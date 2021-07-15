#pragma once

#include <memory>
#include <queue>

#include "EventSettings.h"

#include "iDisplayModule.h"
#include "iDataModule.h"
#include "iTransmissionServer.h"
#include "iCommand.h"

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
	void SetModules(
		std::shared_ptr<iTransmissionServer>, 
		std::shared_ptr<iDisplayModule>, 
		std::shared_ptr<iDataModule>,
		std::shared_ptr<iCommand>
	);
	

	// Helper Methods
private:

	std::string MessageEncoding(ResponseList, ResponseInfo);
	CustomMessage MessageDecoding(const std::string&);

	CustomCommand CommandParse(std::string);

	// Modules
private:
	std::shared_ptr<iTransmissionServer> transmission;
	std::shared_ptr<iDisplayModule> displayModule;
	std::shared_ptr<iDataModule> dataModule;
	std::shared_ptr<iCommand> command;

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