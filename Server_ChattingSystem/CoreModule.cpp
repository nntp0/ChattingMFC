#include "pch.h"

#include "CoreModule.h"

#include "DataModule.h"
#include "Processor.h"

#include "EventSettings.h"

CoreModule::CoreModule() {}
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

void CoreModule::SetTransmission(std::shared_ptr<iTransmissionServer>  transmission) {
	this->transmission = transmission;
}
void CoreModule::Run() {
	this->dataModule = std::shared_ptr<DataModule>(new DataModule);
	this->displayModule = display;

	this->transmission->SetServer(this);

	this->processor = std::shared_ptr<Processor>(new Processor);
	this->processor->SetModules(this->transmission, displayModule, this->dataModule);
}

std::shared_ptr<Processor> CoreModule::FindIdleProcessor() {
	return processor;
}