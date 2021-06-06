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
			newClient.name = buf;
			this->dataModule->newClient(newClient);

			
			ResponseInfo resInfo;
			resInfo.roomName = "MainHall";
			resInfo.userName = newClient.name;
			std::string encodedMsg = MessageEncoding(ResponseList::ClientConnected, resInfo);

			this->transmission->SendTo(args, encodedMsg);

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
				newRoom.name = decodedMessage.body;
				this->dataModule->newRoom(newRoom);

				ResponseInfo resInfo;
				resInfo.roomName = decodedMessage.body;
				resInfo.userName = decodedMessage.uid;
				std::string encodedMsg = MessageEncoding(ResponseList::RoomCreated, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}
			case MessageType::RoomLeave:
			{
				ResponseInfo resInfo;
				resInfo.userName = decodedMessage.uid;
				std::string encodedMsg = MessageEncoding(ResponseList::RoomLeaved, resInfo);
				
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);
				break;
			}
			case MessageType::RoomList:
			{
				auto roomList = this->dataModule->getRoomList();

				char buf[5];
				std::string message = "";

				sprintf_s(buf, 5, "%04d", roomList.size());
				message += buf;
				for (auto it = roomList.begin(); it != roomList.end(); it++) {
					sprintf_s(buf, 5, "%04d", it->roomID);
					message += buf;
					sprintf_s(buf, 5, "%02d", it->name.length());
					message += buf;
					message += it->name;
				}

				ResponseInfo resInfo;
				resInfo.extra = message;
				std::string encodedMsg = MessageEncoding(ResponseList::RoomList, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}
			case MessageType::RoomJoin:
			{
				Room room;
				room.roomID = std::stoi(decodedMessage.body);
				Client client;
				client.clientID = std::stoi(decodedMessage.uid);

				this->dataModule->JoinRoom(room, client);

				ResponseInfo resInfo;
				resInfo.roomName = this->dataModule->GetRoomName(room.roomID);
				resInfo.userName = this->dataModule->GetClientName(client.clientID);
				std::string encodedMsg = MessageEncoding(ResponseList::RoomJoined, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);
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
				
				char buf[5];
				std::string message = "";

				sprintf_s(buf, 5, "%04d", clientList.size());
				message += buf;
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->joinedRoomID == roomID) {
						sprintf_s(buf, 5, "%04d", it->clientID);
						message += buf;
						message += it->name;
					}
				}

				ResponseInfo resInfo;
				resInfo.extra = message;
				std::string encodedMsg = MessageEncoding(ResponseList::ClientList, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

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

				ResponseInfo resInfo;
				resInfo.roomName = this->dataModule->GetRoomName(roomID);
				resInfo.userName = this->dataModule->GetClientName(std::stoi(decodedMessage.uid));
				resInfo.extra = decodedMessage.body;
				std::string encodedMsg = MessageEncoding(ResponseList::Normal, resInfo);

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->joinedRoomID == roomID) {
						
						char buf[10];
						sprintf_s(buf, 10, "%04d", it->clientID);

						this->transmission->SendTo(std::string(buf), encodedMsg);
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
std::string Processor::MessageEncoding(ResponseList type, ResponseInfo info) {
	
	std::string encodedMsg = "";
	char buf[5];
	switch (type) {
		case ResponseList::ClientConnected:
		{
			encodedMsg += "clcr";

			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.roomName.length());
			encodedMsg += buf;
			encodedMsg += info.roomName;

			break;
		}
		case ResponseList::ClientList:
		{
			encodedMsg += "clls";
			encodedMsg += info.extra;

			break;
		}
		case ResponseList::RoomCreated:
		{
			encodedMsg += "rmcr";
			break;
		}
		case ResponseList::RoomLeaved:
		{
			encodedMsg += "rmlv";
			break;
		}
		case ResponseList::RoomJoined:
		{
			encodedMsg += "rmjn";
			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.roomName.length());
			encodedMsg += buf;
			encodedMsg += info.roomName;
			break;
		}
		case ResponseList::RoomList:
		{
			encodedMsg += "rmls";
			encodedMsg += info.extra;
			break;
		}
		case ResponseList::Normal:
		{
			encodedMsg += "norm";
			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.roomName.length());
			encodedMsg += buf;
			encodedMsg += info.roomName;

			encodedMsg += info.extra;
			break;
		}
		default:
		{
			break;
		}
	}

	return encodedMsg;
}
CustomMessage Processor::MessageDecoding(std::string message) {
	CustomMessage decodedMessage;
	decodedMessage.uid = message.substr(0, 4);

	auto code = message.substr(4, 4);

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
	else if (code == "norm") {
		decodedMessage.type = MessageType::Normal;
	}
	else {
		decodedMessage.type = MessageType::Normal;
		decodedMessage.body = message.substr(4);

		this->displayModule->DisplayLog(CString::CStringT(CA2CT(message.c_str())));
		return decodedMessage;
	}

	decodedMessage.body = message.substr(8);

	return decodedMessage;
}