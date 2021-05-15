#include "pch.h"

#include "CoreModule.h"

#include "Transmission.h"



CoreModule::CoreModule(iDisplayModule* displayModule) { DependencyInjection(displayModule); }
CoreModule::~CoreModule() {}

void CoreModule::DependencyInjection(iDisplayModule* displayModule) {
	this->transmission = std::shared_ptr<SocketTransmission>(new SocketTransmission(this));
	this->displayModule = displayModule;
}

void CoreModule::EventController(EventList eventID, void* argv) {

	switch (eventID) {
	case EventList::ClientConnection:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ClientConnection>*>(argv);
		
		TCHAR buf[30];
		wsprintf(buf, _T("%d"), eventData->id);
		this->displayModule->DisplayLog(buf);

		// Greetings to Client
		wsprintf(buf, _T("Hello %d\n"), eventData->id);
		this->transmission->SendTo(eventData->id, buf);

		break;
	}
	case EventList::ClientDisconnection:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ClientDisconnection>*>(argv);

		break;
	}
	case EventList::ReceiveMessage:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ReceiveMessage>*>(argv);

		this->transmission->SendTo(eventData->id, eventData->msg);

		break;
	}
	case EventList::Notification:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_Notification>*>(argv);
		break;
	}
	default:
	{
		break;
	}
	}
}

// Transmission Methods
CString CoreModule::MessageEncoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageEncoding"));
	return msg;
}
CString CoreModule::MessageDecoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageDecoding"));
	return msg;
}