#include "pch.h"

#include "CoreModule.h"

#include "Transmission.h"


CoreModule::CoreModule() {}
CoreModule::~CoreModule() {}

void CoreModule::DependencyInjection() {
	this->transmission = std::shared_ptr<SocketTransmission>(new SocketTransmission(this));
}

void CoreModule::EventController(EventList eventID, void* argv) {

	switch (eventID) {
	case EventList::ClientConnection:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ClientConnection>*>(argv);

		break;
	}
	case EventList::ClientDisconnection:
	{
		AfxMessageBox(_T("EventController ClientDisconnection"));
		auto eventData = *static_cast<std::shared_ptr<Info_ClientDisconnection>*>(argv);

		TCHAR buf[30];
		wsprintf(buf, _T("ID: %d\n"), eventData->id);
		AfxMessageBox(buf);

		break;
	}
	case EventList::ReceiveMessage:
	{
		auto eventData = *static_cast<std::shared_ptr<Info_ReceiveMessage>*>(argv);
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