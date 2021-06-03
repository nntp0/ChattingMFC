#include "pch.h"

#include "CoreModule.h"

#include "AMQPServer.h"
#include "DataModule.h"


CoreModule::CoreModule(iDisplayModule* displayModule) { DependencyInjection(displayModule); }
CoreModule::~CoreModule() {}

void CoreModule::DependencyInjection(iDisplayModule* displayModule) {
	this->transmission = std::shared_ptr<AMQPServer>(new AMQPServer);
	this->displayModule = displayModule;
	this->dataModule = std::shared_ptr<DataModule>(new DataModule);
}

void CoreModule::EventController(EventList eventID, void* argv) {

	switch (eventID) {
		case EventList::ClientConnection:
		{
			auto eventData = *static_cast<std::shared_ptr<Info_ClientConnection>*>(argv);
		
			TCHAR buf[30];
			wsprintf(buf, _T("%d Connected"), eventData->socketID);
			this->displayModule->DisplayLog(buf);

			Client newClient;
			newClient.clientID = eventData->socketID;
			wsprintf(buf, _T("Client %d"), eventData->socketID);
			newClient.name = buf;
			this->dataModule->newClient(newClient);

			// Greetings to Client
			wsprintf(buf, _T("Hello %d\n"), eventData->socketID);
			this->transmission->SendTo(eventData->socketID, "Hello % d\n");

			break;
		}
		case EventList::ClientDisconnection:
		{
			auto eventData = *static_cast<std::shared_ptr<Info_ClientDisconnection>*>(argv);

			Client leftClient;
			leftClient.clientID = eventData->socketID;
			this->dataModule->closeClient(leftClient);

			TCHAR buf[30];
			wsprintf(buf, _T("%d DisConnected"), eventData->socketID);
			this->displayModule->DisplayLog(buf);

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
				this->transmission->SendTo(eventData->socketID, "RoomCreated");
				break;
			}
			case MessageType::RoomLeave:
			{
				this->transmission->SendTo(eventData->socketID, "RoomLeaved");
				break;
			}
			case MessageType::RoomList:
			{
				auto roomList = this->dataModule->getRoomList();

				TCHAR buf[30];
				CString message = _T("");
				for (auto it = roomList.begin(); it != roomList.end(); it++) {
					wsprintf(buf, _T("%d: "), it->roomID);
					message += buf + it->name + _T("\n");
				}
				this->transmission->SendTo(eventData->socketID, std::string(CT2CA(message.operator LPCWSTR())));
				break;
			}
			case MessageType::RoomJoin:
			{
				Room room;
				room.roomID = _ttoi(decodedMessage.msg);
				Client client;
				client.clientID = eventData->socketID;

				this->dataModule->JoinRoom(room, client);

				this->transmission->SendTo(eventData->socketID, "RoomJoined");
				break;
			}
			case MessageType::ClientList:
			{
				UINT roomID = 0;
				auto clientList = this->dataModule->getClientList();
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->clientID == eventData->socketID) {
						roomID = it->joinedRoomID;
					}
				}

				CString msg = _T("");
				TCHAR buf[30];
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->joinedRoomID == roomID) {
						wsprintf(buf, _T("%d|"), it->clientID);
						msg += buf;
					}
				}

				this->transmission->SendTo(eventData->socketID, std::string(CT2CA(msg.operator LPCWSTR())));
			}

			case MessageType::Normal:
			{
				auto temp = this->dataModule->getClientList();
				UINT roomID = -1;

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->clientID == eventData->socketID) {
						roomID = it->joinedRoomID;
					}
				}

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->joinedRoomID == roomID) {
						this->transmission->SendTo(it->clientID, std::string(CT2CA(decodedMessage.msg.operator LPCWSTR())));
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
	else if (code == _T("cl")) {
		decodedMessage.type = MessageType::ClientList;
	}
	else {
		decodedMessage.type = MessageType::Normal;
		decodedMessage.msg = msg;
		return decodedMessage;
	}
	decodedMessage.msg = msg.Mid(2);

	return decodedMessage;
}