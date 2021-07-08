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
		// 새로운 Client 접속 시,
		//	1. 해당 사실 Display
		//	2. Data 로 저장 (아이디 기본 할당)
		//	3. 접속되었다는 사실 알림
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

		// Client 연결 종료 시,
		//	1. 해당 사실 Display
		//	2. Data Module 내용 갱신
		case EventList::ClientDisconnection:
		{
			std::string log = "[SYS] [" + args + "] disconnected";
			this->displayModule->WriteLog(log);

			Client leftClient("", std::stoi(args), -1);
			this->dataModule->closeClient(leftClient);

			break;
		}

		// 일반적인 Message 에 대한 Process 
		//	1. Message 를 Decoding
		//	2. Decoding 된 내용에 따라 처리
		case EventList::ReceiveMessage:
		{
			auto decodedMessage = this->MessageDecoding(args);

			switch (decodedMessage.type) {

				// 방생성
				//	1. Data Module 에 방 생성
				//	2. 방 생성되었다는 정보를 모든 Client 에 알립니다.
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

				// 방나가기
				//  1. Data Module 에 방 나갔다고 갱신
				//	2. 방에서도 해당 유저 제거
				//  2. 나간 사실 알림
			case MessageType::RoomLeave:
			{
				std::string buf = "[REQ] [RoomLeave] [" + decodedMessage.uid + "]";
				this->displayModule->WriteLog(buf);


				Client leftClient("", stoi(decodedMessage.uid), 0);
				// 여기부터 Notification

				Client* targetClient = this->dataModule->GetClient(leftClient.clientID);

				if (targetClient->joinedRoom) {
					char roomID[10];
					sprintf_s(roomID, 10, "%04d", targetClient->joinedRoom);

					RegisterEvent("noti" + std::string(roomID) + targetClient->name + "님이 퇴장하셨습니다.");
				}
				this->dataModule->LeaveRoom(leftClient);

				ResponseInfo resInfo("", "", "");
				std::string encodedMsg = MessageEncoding(ResponseList::RoomLeaved, resInfo);
				this->transmission->SendTo(decodedMessage.uid, encodedMsg);

				break;
			}

				// 방 목록 조회
				//	1. Data Module 에서 목록 조회
				//	2. 해당 데이터 string 으로 변경
				//	3. 전송
			case MessageType::RoomList:
			{
				std::string log = "[REQ] [RoomList] [" + decodedMessage.uid + "]";
				this->displayModule->WriteLog(log);

				auto roomList = this->dataModule->GetRoomList();

				std::string message = "";

				// 방 개수
				char buf[5];
				sprintf_s(buf, 5, "%04d", roomList.size());
				message += buf;

				// 방 아이디 (4자리) + 방 이름 길이 + 방 이름
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

				// 방 입장
				//	1. 방 정보와, 유저 정보를 Data Module 에 갱신
				//	2. 해당 사실 방에 속한 모든 유저에게 전송
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
					RegisterEvent("noti" + std::string(buf) + userName + "님이 입장하셨습니다.");
				}
				break;
			}

				// 유저 목록
				//	1. 유저 목록 전부 획득
				//	2. 해당 유저 속한 방에 있는 유저 정보 전부 std::string
				//	3. 전송
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
				
				// 유저수(4자리) + 유저아이디(4자리) + 유저명 길이 + 유저명
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

				// 일반메시지
				//	1. 유저가 속한 방 획득
				//	2. 해당 방 유저에게 메세지 전달
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

				// *** 더 빠른 로직 가능함 ***
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

		// 서버에서 클라이언트로 정보를 송신
		// 특정 Room 에 존재하는 모든 클라이언트 들에게 송신한다.
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

// 유저 ID (4자리) + 코드 (4자리) + 추가정보
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
		// 잘못된 타입 정보, 전송 오류

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
	// *** Error Handling 고려, 개선해야함 ***
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