#include "pch.h"

#include "CoreModule.h"

#include "AMQPServer.h"
#include "DataModule.h"
#include "Processor.h"

#include "EventSettings.h"

CoreModule::CoreModule(iDisplayModule* displayModule) {
	this->transmission = std::shared_ptr<AMQPServer>(new AMQPServer);
	this->displayModule = displayModule;
	this->dataModule = std::shared_ptr<DataModule>(new DataModule);
	this->processor = std::shared_ptr<Processor>(new Processor);

	this->transmission->SetServer(this);
	this->processor->SetModules(this->transmission, displayModule, this->dataModule);
}
CoreModule::~CoreModule() {}


void CoreModule::Tick() { AfxMessageBox(_T("Hello. I am Server")); }
void CoreModule::Connect(UID id) {
	auto idleProcessor = FindIdleProcessor();
	idleProcessor->ProcessEvent(EventList::ClientConnection, id);
}
void CoreModule::Disconnect(UID id) {
	auto idleProcessor = FindIdleProcessor();
	idleProcessor->ProcessEvent(EventList::ClientDisconnection, id);
}
void CoreModule::RecvMessage(std::string msg) {
	auto idleProcessor = FindIdleProcessor();
	idleProcessor->ProcessEvent(EventList::ReceiveMessage, msg);
}


std::shared_ptr<Processor> CoreModule::FindIdleProcessor() {
	return processor;
}