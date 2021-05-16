#include "pch.h"

#include "CoreModule.h"

#include "Transmission.h"
#include "DataModule.h"


CoreModule::CoreModule(iDisplayModule* displayModule) { DependencyInjection(displayModule); }
CoreModule::~CoreModule() {}

void CoreModule::DependencyInjection(iDisplayModule* displayModule) {
	this->transmission = std::shared_ptr<SocketTransmission>(new SocketTransmission(this));
	this->displayModule = displayModule;
	this->dataModule = std::shared_ptr<DataModule>(new DataModule);
}

void CoreModule::EventController(EventList eventID, void* argv) {

	switch (eventID) {
	case EventList::ClientConnection:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ClientConnection>*>(argv);
		
		TCHAR buf[30];
		wsprintf(buf, _T("%d"), eventData->id);
		this->displayModule->DisplayLog(buf);

		Client newClient;
		newClient.id = eventData->id;
		newClient.name = _T("New Customer");
		this->dataModule->newClient(newClient);

		// Greetings to Client
		wsprintf(buf, _T("Hello %d\n"), eventData->id);
		this->transmission->SendTo(eventData->id, buf);

		break;
	}
	case EventList::ClientDisconnection:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ClientDisconnection>*>(argv);

		Client newClient;
		newClient.id = eventData->id;
		newClient.name = _T("Closed Customer");
		this->dataModule->closeClient(newClient);

		auto temp = this->dataModule->getClientList();
		TCHAR buf[30];

		CString clientList = _T("");
		for (auto it = temp.begin(); it != temp.end(); it++) {
			wsprintf(buf, _T("%d, "), it->id);
			clientList += buf;
		}
		AfxMessageBox(clientList);

		break;
	}
	case EventList::ReceiveMessage:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ReceiveMessage>*>(argv);

		auto temp = this->dataModule->getClientList();
		for (auto it = temp.begin(); it != temp.end(); it++) {
			if (it->id == eventData->id) continue;
			this->transmission->SendTo(it->id, eventData->msg);
		}

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