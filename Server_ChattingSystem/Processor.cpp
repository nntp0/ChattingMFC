#include "pch.h"
#include "Processor.h"

Processor::Processor() {}
Processor::~Processor () {}

void Processor::SetModules(
	std::shared_ptr<iTransmissionServer> transmission, 
	iDisplayModule* display, 
	std::shared_ptr<iDataModule> data) {
	
	this->transmission = transmission;
	this->displayModule = display;
	this->dataModule = data;
}

void Processor::ProcessEvent(EventList eType, std::string args) {

	switch (eType) {
		case EventList::ClientConnection: 
		{
			std::string buf = args + " connected";
			CString cstr = CString::CStringT(CA2CT(buf.c_str()));

			this->displayModule->DisplayLog(cstr);

			Client newClient;
			newClient.clientID = std::stoul(args);
			buf = "Client " + args;
			newClient.name = CString::CStringT(CA2CT(buf.c_str()));
			this->dataModule->newClient(newClient);

			this->transmission->SendTo(args, "Hello " + buf);

			break;
		}
		case EventList::ClientDisconnection:
		{
			std::string buf = args + " disconnected";
			CString cstr = CString::CStringT(CA2CT(buf.c_str()));

			this->displayModule->DisplayLog(cstr);

			Client leftClient;
			leftClient.clientID = std::stoul(args);
			this->dataModule->closeClient(leftClient);

			break;
		}
		case EventList::ReceiveMessage:
		{
			auto decodedMessage = this->MessageDecoding(args);

			switch (decodedMessage.type) {
			case MessageType::RoomCreation:
			{
				Room newRoom;
				newRoom.name = CString::CStringT(CA2CT(decodedMessage.body.c_str()));
				this->dataModule->newRoom(newRoom);
				this->transmission->SendTo(decodedMessage.uid, "RoomCreated");
				break;
			}
			case MessageType::RoomLeave:
			{
				this->transmission->SendTo(decodedMessage.uid, "RoomLeaved");
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
				this->transmission->SendTo(decodedMessage.uid, std::string(CT2CA(message.operator LPCWSTR())));
				break;
			}
			case MessageType::RoomJoin:
			{
				Room room;
				room.roomID = std::stoi(decodedMessage.body);
				Client client;
				client.clientID = std::stoi(decodedMessage.uid);

				this->dataModule->JoinRoom(room, client);

				this->transmission->SendTo(decodedMessage.uid, "RoomJoined");
				break;
			}
			case MessageType::ClientList:
			{
				UINT roomID = 0;
				auto clientList = this->dataModule->getClientList();
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
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

				this->transmission->SendTo(decodedMessage.uid, std::string(CT2CA(msg.operator LPCWSTR())));
				break;
			}
			case MessageType::Normal:
			{
				auto temp = this->dataModule->getClientList();
				UINT roomID = -1;

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
						roomID = it->joinedRoomID;
					}
				}

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->joinedRoomID == roomID) {
						char buf[10];
						sprintf_s(buf, 10, "%04d", it->clientID);
						this->transmission->SendTo(std::string(buf), decodedMessage.body);
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
			break;
		}
		default:
		{
			break;
		}
	}
}


// Transmission Methods
std::string Processor::MessageEncoding(CustomMessage msg) {
	return msg.body;
}
CustomMessage Processor::MessageDecoding(std::string message) {
	CustomMessage decodedMessage;
	decodedMessage.uid = message.substr(0, 4);

	auto code = message.substr(4, 8);

	if (code == "rmcr") {
		decodedMessage.type = MessageType::RoomCreation;
	}
	else if (code == "rmls") {
		decodedMessage.type = MessageType::RoomList;
	}
	else if (code == "rmjn") {
		decodedMessage.type = MessageType::RoomJoin;
	}
	else if (code == "rmlv") {
		decodedMessage.type = MessageType::RoomLeave;
	}
	else if (code == "clls") {
		decodedMessage.type = MessageType::ClientList;
	}
	else {
		decodedMessage.type = MessageType::Normal;
	}
	if (decodedMessage.type == MessageType::Normal) {
		decodedMessage.body = message.substr(4);
	}
	else {
		decodedMessage.body = message.substr(8);
	}

	return decodedMessage;
}