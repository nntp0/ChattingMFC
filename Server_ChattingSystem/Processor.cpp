#include "pch.h"
#include "Processor.h"

Processor::Processor() {
	
}
Processor::~Processor () {}

void Processor::SetModules(
	std::shared_ptr<iTransmissionServer> transmission,
	std::shared_ptr<iDisplayModule> display,
	std::shared_ptr<iDataModule> data,
	std::shared_ptr<iCommand> command) {
	
	this->transmission = transmission;
	this->displayModule = display;
	this->dataModule = data;
	this->command = command;
}


void Processor::ProcessEvent(EventList eType, std::string args) {

	switch (eType) {
		// ���ο� Client ���� ��,
		//	1. �ش� ��� Display
		//	2. Data �� ���� (���̵� �⺻ �Ҵ�)
		//	3. ���ӵǾ��ٴ� ��� �˸�
		case EventList::ClientConnection: 
		{
			std::string log = "[SYS] [" + args + "] connected";
			this->displayModule->WriteLog(log);

			Client newClient("", std::stoi(args), 0);
			this->dataModule->newClient(newClient);

			ResponseInfo resInfo(this->dataModule->GetClient(newClient.clientID)->name, "MainHall", "");
			std::string encodedMsg = MessageEncoding(ResponseList::ClientConnected, resInfo);

			this->transmission->SendTo(args, encodedMsg);

			break;
		}

		// Client ���� ���� ��,
		//	1. �ش� ��� Display
		//	2. Data Module ���� ����
		case EventList::ClientDisconnection:
		{
			std::string log = "[SYS] [" + args + "] disconnected";
			this->displayModule->WriteLog(log);

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
				std::string log = "[REQ] [RoomCreation] [" + decodedMessage.uid + "] [RoomName] : " + decodedMessage.body;
				this->displayModule->WriteLog(log);

				Room newRoom(decodedMessage.body, -1);
				this->dataModule->newRoom(newRoom);

				ResponseInfo resInfo(decodedMessage.uid, decodedMessage.body, "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomCreated, resInfo);

				auto clientList = this->dataModule->GetClientList();
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
				std::string buf = "[REQ] [RoomLeave] [" + decodedMessage.uid + "]";
				this->displayModule->WriteLog(buf);


				Client leftClient("", stoi(decodedMessage.uid), 0);
				// ������� Notification

				Client* targetClient = this->dataModule->GetClient(leftClient.clientID);

				if (targetClient->joinedRoom) {
					char roomID[10];
					sprintf_s(roomID, 10, "%04d", targetClient->joinedRoom);

					RegisterEvent("noti" + std::string(roomID) + targetClient->name + "���� �����ϼ̽��ϴ�.");
				}
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
				std::string log = "[REQ] [RoomList] [" + decodedMessage.uid + "]";
				this->displayModule->WriteLog(log);

				auto roomList = this->dataModule->GetRoomList();

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
				std::string log = "[REQ] [RoomJoin] [" + decodedMessage.uid + "] To [" + decodedMessage.body + "]";
				this->displayModule->WriteLog(log);

				Room room("", std::stoi(decodedMessage.body));
				Client client("", std::stoi(decodedMessage.uid), -1);

				this->dataModule->JoinRoom(room, client);

				std::string roomName = this->dataModule->GetRoom(room.roomID)->name;
				std::string userName = this->dataModule->GetClient(client.clientID)->name;
				ResponseInfo resInfo(userName, roomName, "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomJoined, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				if (std::stoi(decodedMessage.body)) {
					char buf[10];
					sprintf_s(buf, 10, "%04d", std::stoi(decodedMessage.body));
					RegisterEvent("noti" + std::string(buf) + userName + "���� �����ϼ̽��ϴ�.");
				}
				break;
			}

				// ���� ���
				//	1. ���� ��� ���� ȹ��
				//	2. �ش� ���� ���� �濡 �ִ� ���� ���� ���� std::string
				//	3. ����
			case MessageType::ClientList:
			{
				std::string log = "[REQ] [ClientList] [" + decodedMessage.uid + "]";
				this->displayModule->WriteLog(log);

				int roomID = 0;
				auto clientList = this->dataModule->GetClientList();
				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
						roomID = it->joinedRoom;
					}
				}
				
				// ������(4�ڸ�) + �������̵�(4�ڸ�) + ������ ���� + ������
				std::string message = "";
				char buf[5];
				int count = 0;

				for (auto it = clientList.begin(); it != clientList.end(); it++) {
					if (it->joinedRoom == roomID) {
						sprintf_s(buf, 5, "%04d", it->clientID);
						message += buf;
						sprintf_s(buf, 5, "%02d", it->name.length());
						message += buf;
						message += it->name;
						count++;
					}
				}

				sprintf_s(buf, 5, "%04d", count);
				message = buf + message;

				AfxMessageBox(CString(message.c_str()));

				ResponseInfo resInfo("", "", message);
				std::string encodedMsg = MessageEncoding(ResponseList::ClientList, resInfo);
				
				AfxMessageBox(CString(encodedMsg.c_str()));

				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// �Ϲݸ޽���
				//	1. ������ ���� �� ȹ��
				//	2. �ش� �� �������� �޼��� ����
			case MessageType::Normal:
			{
				auto temp = this->dataModule->GetClientList();
				int roomID = -1;

				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->clientID == std::stoi(decodedMessage.uid)) {
						roomID = it->joinedRoom;
					}
				}

				std::string roomName = this->dataModule->GetRoom(roomID)->name;
				std::string userName = this->dataModule->GetClient(std::stoi(decodedMessage.uid))->name;
				ResponseInfo resInfo(userName, roomName, decodedMessage.body);
				std::string encodedMsg = MessageEncoding(ResponseList::Normal, resInfo);

				// *** �� ���� ���� ������ ***
				for (auto it = temp.begin(); it != temp.end(); it++) {
					if (it->joinedRoom == roomID) {
						
						char buf[10];
						sprintf_s(buf, 10, "%04d", it->clientID);

						this->transmission->SendTo(std::string(buf), encodedMsg);
					}
				}

				break;
			}

			case MessageType::ChangeClientInfo:
			{
				Client* changeClient = this->dataModule->GetClient(stoi(decodedMessage.uid));
				std::string oldName = changeClient->name;
				std::string log = "[REQ] [ChangeClientInfo] [" + oldName + "] to [" + decodedMessage.body + "]";
				this->displayModule->WriteLog(log);

				if (this->dataModule->ChangeClientInfo(changeClient->clientID, decodedMessage.body)) {

					ResponseInfo resInfo(changeClient->name, "", oldName);
					std::string encodedMsg = MessageEncoding(ResponseList::ChangeClientInfo, resInfo);

					//AfxMessageBox(CString(encodedMsg.c_str()));

					this->transmission->SendTo(decodedMessage.uid, encodedMsg);
				}
				else {
					std::string log = "[FAIL] [ChangeClientInfo]";
					this->displayModule->WriteLog(log);
				}

				break;
			}

			default:
				break;
			}

			break;
		}

		// �������� Ŭ���̾�Ʈ�� ������ �۽�
		// Ư�� Room �� �����ϴ� ��� Ŭ���̾�Ʈ �鿡�� �۽��Ѵ�.
		case EventList::Notification:
		{
			std::string roomID = args.substr(0, 4);
			std::string message = args.substr(4);
			
			int temp = stoi(roomID);
			std::string roomName = this->dataModule->GetRoom(temp)->name;

			auto clientList = this->dataModule->GetClientList();
			for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
				if (iter->joinedRoom == temp) {
					char buf[10];
					sprintf_s(buf, 10, "%04d", iter->clientID);
					
					char msg[100];
					sprintf_s(msg, 100, "noti00%02d%s%s", roomName.length(), roomName.c_str(), message.c_str());
					this->transmission->SendTo(std::string(buf), std::string(msg));
				}
			}

			break;
		}

		case EventList::SystemMessage:
		{
			auto decodedCommand = this->CommandParse(args);

			switch (decodedCommand.type) {
				case CommandType::ClientList:
				{
					AfxMessageBox(_T("ClientList"));
					break;
				}
				case CommandType::Error:
				{
					AfxMessageBox(_T("Error"));
					break;
				}
				default:
				{
					this->command->MessageResponse(CString(("Your command : " + args).c_str()));
				}
			}
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
		case ResponseList::ChangeClientInfo: {
			encodedMsg += "chcl";

			sprintf_s(buf, 5, "%02d", info.userName.length());
			encodedMsg += buf;
			encodedMsg += info.userName;

			sprintf_s(buf, 5, "%02d", info.extra.length());
			encodedMsg += buf;
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
	else if (code == "chcl") {
		decodedMessage.type = MessageType::ChangeClientInfo;
	}
	else {
		// �߸��� Ÿ�� ����, ���� ����

		this->displayModule->WriteLog("Message Type Error");
		this->displayModule->WriteLog(message);

		decodedMessage.type = MessageType::Error;

		return decodedMessage;
	}

	decodedMessage.body = message.substr(8);

	return decodedMessage;
}

CustomCommand Processor::CommandParse(std::string command) {
	std::string code = command.substr(0, 4);

	CustomCommand decodedCommand;
	if (code == "cllr") {
		decodedCommand.type = CommandType::ClientList;
	}
	else {
		decodedCommand.type = CommandType::Error;
	}

	return decodedCommand;
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
	else if (type == "noti") {
		ProcessEvent(EventList::Notification, msg);
	}
	else if (type == "cmnd") {
		ProcessEvent(EventList::SystemMessage, msg);
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