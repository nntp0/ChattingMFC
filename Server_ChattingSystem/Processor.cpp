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
		// ���ο� Client ���� ��,
		//	1. �ش� ��� Display
		//	2. Data �� ���� (���̵� �⺻ �Ҵ�)
		//	3. ���ӵǾ��ٴ� ��� �˸�
		case EventList::ClientConnection: 
		{
			std::string buf = args + " connected";
			CString cstr = CString::CStringT(CA2CT(buf.c_str()));
			this->displayModule->DisplayLog(cstr);

			Client newClient("Client" + args, std::stoi(args), 0);
			this->dataModule->newClient(newClient);

			ResponseInfo resInfo(newClient.name, "MainHall", "");
			std::string encodedMsg = MessageEncoding(ResponseList::ClientConnected, resInfo);

			this->transmission->SendTo(args, encodedMsg);

			break;
		}

		// Client ���� ���� ��,
		//	1. �ش� ��� Display
		//	2. Data Module ���� ����
		case EventList::ClientDisconnection:
		{
			std::string buf = args + " disconnected";
			CString cstr = CString::CStringT(CA2CT(buf.c_str()));
			this->displayModule->DisplayLog(cstr);

			Client leftClient("", std::stoi(args), -1);
			this->dataModule->closeClient(leftClient);

			break;
		}

		// �Ϲ����� Message �� ���� Process 
		//	1. Message �� Decoding
		//	2. Decoding �� ���뿡 ���� ó��
		case EventList::ReceiveMessage:
		{
			auto decodedMessage = this->MessageDecoding(args);

			switch (decodedMessage.type) {

				// �����
				//	1. Data Module �� �� ����
				//	2. �� �����Ǿ��ٴ� ������ ��� Client �� �˸��ϴ�.
			case MessageType::RoomCreation:
			{
				Room newRoom(decodedMessage.body, -1);
				this->dataModule->newRoom(newRoom);

				ResponseInfo resInfo(decodedMessage.uid, decodedMessage.body, "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomCreated, resInfo);

				auto clientList = this->dataModule->getClientList();
				for (auto it = clientList.cbegin(); it != clientList.cend(); it++) {
					char buf[10];
					sprintf_s(buf, 10, "%04d", it->clientID);

					this->transmission->SendTo(buf, encodedMsg);
				}

				break;
			}

				// �泪����
				//  1. Data Module �� �� �����ٰ� ����
				//	2. �濡���� �ش� ���� ����
				//  2. ���� ��� �˸�
			case MessageType::RoomLeave:
			{
				Client leftClient("", stoi(decodedMessage.uid), 0);
				this->dataModule->LeaveRoom(leftClient);

				ResponseInfo resInfo("", "", "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomLeaved, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// �� ��� ��ȸ
				//	1. Data Module ���� ��� ��ȸ
				//	2. �ش� ������ string ���� ����
				//	3. ����
			case MessageType::RoomList:
			{
				auto roomList = this->dataModule->getRoomList();

				std::string message = "";

				// �� ����
				char buf[5];
				sprintf_s(buf, 5, "%04d", roomList.size());
				message += buf;

				// �� ���̵� (4�ڸ�) + �� �̸� ���� + �� �̸�
				for (auto it = roomList.begin(); it != roomList.end(); it++) {
					sprintf_s(buf, 5, "%04d", it->roomID);
					message += buf;
					sprintf_s(buf, 5, "%02d", it->name.length());
					message += buf;
					message += it->name;
				}

				ResponseInfo resInfo("", "", message);
				std::string encodedMsg = MessageEncoding(ResponseList::RoomList, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// �� ����
				//	1. �� ������, ���� ������ Data Module �� ����
				//	2. �ش� ��� �濡 ���� ��� �������� ����
			case MessageType::RoomJoin:
			{
				Room room("", std::stoi(decodedMessage.body));
				Client client("", std::stoi(decodedMessage.uid), -1);

				this->dataModule->JoinRoom(room, client);

				std::string roomName = this->dataModule->GetRoomName(room.roomID);
				std::string userName = this->dataModule->GetClientName(client.clientID);
				ResponseInfo resInfo(userName, roomName, "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomJoined, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// ���� ���
				//	1. ���� ��� ���� ȹ��
				//	2. �ش� ���� ���� �濡 �ִ� ���� ���� ���� std::string
				//	3. ����
			case MessageType::ClientList:
			{
				int roomID = 0;
				auto clientList = this->dataModule->getClientList();
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
						roomID = it->joinedRoomID;
					}
				}
				
				// ������(4�ڸ�) + �������̵�(4�ڸ�) + ������ ���� + ������
				std::string message = "";
				char buf[5];
				sprintf_s(buf, 5, "%04d", clientList.size());
				message += buf;
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->joinedRoomID == roomID) {
						sprintf_s(buf, 5, "%04d", it->clientID);
						message += buf;
						sprintf_s(buf, 5, "%02d", it->name.length());
						message += buf;
						message += it->name;
					}
				}

				ResponseInfo resInfo("", "", message);
				std::string encodedMsg = MessageEncoding(ResponseList::ClientList, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// �Ϲݸ޽���
				//	1. ������ ���� �� ȹ��
				//	2. �ش� �� �������� �޼��� ����
			case MessageType::Normal:
			{
				auto temp = this->dataModule->getClientList();
				int roomID = -1;

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
						roomID = it->joinedRoomID;
					}
				}

				std::string roomName = this->dataModule->GetRoomName(roomID);
				std::string userName = this->dataModule->GetClientName(std::stoi(decodedMessage.uid));
				ResponseInfo resInfo(userName, roomName, decodedMessage.body);
				std::string encodedMsg = MessageEncoding(ResponseList::Normal, resInfo);

				// *** �� ���� ���� ������ ***
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

		// ���� (�̱���)
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

// Helper Methods
std::string Processor::MessageEncoding(ResponseList type, ResponseInfo info) {
	
	std::string encodedMsg = "";
	char buf[5];
	switch (type) {
		case ResponseList::ClientConnected: {
			encodedMsg += "clcr";

			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.roomName.length());
			encodedMsg += buf;
			encodedMsg += info.roomName;

			break;
		}
		case ResponseList::ClientList: {
			encodedMsg += "clls";
			encodedMsg += info.extra;

			break;
		}
		case ResponseList::RoomCreated: {
			encodedMsg += "rmcr";
			break;
		}
		case ResponseList::RoomLeaved: {
			encodedMsg += "rmlv";
			break;
		}
		case ResponseList::RoomJoined: {
			encodedMsg += "rmjn";
			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.roomName.length());
			encodedMsg += buf;
			encodedMsg += info.roomName;
			break;
		}
		case ResponseList::RoomList: {
			encodedMsg += "rmls";
			encodedMsg += info.extra;
			break;
		}
		case ResponseList::Normal: {
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
		default: {
			break;
		}
	}

	return encodedMsg;
}

// ���� ID (4�ڸ�) + �ڵ� (4�ڸ�) + �߰�����
CustomMessage Processor::MessageDecoding(std::string message) {
	CustomMessage decodedMessage;
	decodedMessage.uid = message.substr(0, 4);

	std::string code = message.substr(4, 4);
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
		// �߸��� Ÿ�� ����, ���� ����

		this->displayModule->DisplayLog(CString("Message Type Error"));
		this->displayModule->DisplayLog(CString::CStringT(CA2CT(message.c_str())));

		decodedMessage.type = MessageType::Error;

		return decodedMessage;
	}

	decodedMessage.body = message.substr(8);

	return decodedMessage;
}

bool Processor::Job() {
	messageListLock.lock(); 
	
	std::string msg(messageList.front());
	messageList.pop();

	messageListLock.unlock();

	std::string type = msg.substr(0, 4);
	msg = msg.substr(4);

	if (type == "conn") {
		ProcessEvent(EventList::ClientConnection, msg);
	}
	else if (type == "disc") {
		ProcessEvent(EventList::ClientDisconnection, msg);
	}
	// *** Error Handling ���, �����ؾ��� ***
	else {
		ProcessEvent(EventList::ReceiveMessage, msg);
	}

	return true;
}
void Processor::RegisterEvent(std::string msg) {

	messageListLock.lock();
	messageList.push(msg);
	messageListLock.unlock();

	YouHaveWork();
}