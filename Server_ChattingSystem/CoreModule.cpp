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
			wsprintf(buf, _T("%d Connected"), eventData->id);
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

			/*auto temp = this->dataModule->getClientList();
			TCHAR buf[30];

			CString clientList = _T("");
			for (auto it = temp.begin(); it != temp.end(); it++) {
				wsprintf(buf, _T("%d, "), it->id);
				clientList += buf;
			}
			AfxMessageBox(clientList);*/

			break;
		}
		case EventList::ReceiveMessage:
		{
			auto eventData = *static_cast<std::shared_ptr<Info_ReceiveMessage>*>(argv);

			auto decodedMessage = this->MessageDecoding(eventData->msg);

			switch (decodedMessage.type) {
			case MessageType::RoomCreation:
			{
				Room newRoom;
				newRoom.name = decodedMessage.msg;
				this->dataModule->newRoom(newRoom);
				this->transmission->SendTo(eventData->id, _T("RoomCreated"));
				break;
			}
			case MessageType::RoomLeave:
			{
				this->transmission->SendTo(eventData->id, _T("RoomLeaved"));
				break;
			}
			case MessageType::RoomList:
			{
				auto roomList = this->dataModule->getRoomList();

				TCHAR buf[30];
				CString message = _T("");
				for (auto it = roomList.begin(); it != roomList.end(); it++) {
					wsprintf(buf, _T("%d: "), it->id);
					message += buf + it->name + _T("\n");
				}
				this->transmission->SendTo(eventData->id, message);
				break;
			}
			case MessageType::RoomJoin:
			{
				Room room;
				room.id = _ttoi(decodedMessage.msg);
				Client client;
				client.id = eventData->id;
				this->dataModule->JoinRoom(room, client);
				this->transmission->SendTo(eventData->id, _T("RoomJoined"));
				break;
			}
			case MessageType::Normal:
			{
				auto temp = this->dataModule->getClientList();
				UINT roomID = -1;

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->id == eventData->id) {
						roomID = it->joinedRoom;
					}
				}

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->joinedRoom == roomID) {
						this->transmission->SendTo(it->id, decodedMessage.msg);
					}
				}
				
				break;
			}
			default:
				break;
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
CString CoreModule::MessageEncoding(CustomMessage msg) {
	TRACE(_T("SocketTransmssion MessageEncoding"));
	return msg.msg;
}
CustomMessage CoreModule::MessageDecoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageDecoding"));
	
	CustomMessage decodedMessage;

	auto code = msg.Left(2);
	if (code == _T("rc")) {
		decodedMessage.type = MessageType::RoomCreation;
	}
	else if (code == _T("rq")) {
		decodedMessage.type = MessageType::RoomList;
	}
	else if (code == _T("rj")) {
		decodedMessage.type = MessageType::RoomJoin;
	}
	else if (code == _T("rl")) {
		decodedMessage.type = MessageType::RoomLeave;
	}
	else if (code == _T("nm")) {
		decodedMessage.type = MessageType::Normal;
	}
	else {
		decodedMessage.type = MessageType::Normal;
		decodedMessage.msg = msg;
		return decodedMessage;
	}
	decodedMessage.msg = msg.Mid(2);

	return decodedMessage;
}