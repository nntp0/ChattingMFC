#include "pch.h"
#include "Processor.h"

Processor::Processor()
	: transmission(nullptr), display(nullptr) {}
Processor::~Processor() {}
void Processor::SetModules(iTransmission* transmission, CChildView* display) {
	this->transmission = transmission;
	this->display = display;
}
bool Processor::Job() {
	
	messageListLock.lock(); 
	
	std::string msg(messageList.front());
	messageList.pop();

	messageListLock.unlock();

	auto type = msg.substr(0, 2);
	msg = msg.substr(2);

	// cs: client to server
	// sc: server to client
	if (type == "cs") {
		MessageToServer(msg);
	}
	else if (type == "sc") {
		MessageFromServer(msg);
	}
	else {
		AfxMessageBox(_T("????"));
	}

	return true;
}
void Processor::RegisterEvent(std::string msg) {

	messageListLock.lock();
	messageList.push(msg);
	messageListLock.unlock();

	YouHaveWork();
}

void Processor::MessageFromServer(std::string msg) {
	std::string buf = msg.substr(0, 4);
	msg = msg.substr(4);

	if (buf == "clcr") {
		std::string buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int len = stoi(buf);

		std::string uName = msg.substr(0, len);
		msg = msg.substr(len);

		buf = msg.substr(0, 2);
		msg = msg.substr(2);
		len = stoi(buf);

		std::string rName = msg.substr(0, len);
		msg = msg.substr(len);

		display->UpdateUserInfo(uName, rName);
	}
	else if (buf == "clls") {
		std::string buf = "¹Ì±¸Çö";
	}
	else if (buf == "rmcr") {
		this->RegisterEvent("csrmls");
	}
	else if (buf == "rmlv") {
		this->RegisterEvent("csrmls");
	}
	else if (buf == "rmjn") {
		std::string buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int len = stoi(buf);

		std::string uName = msg.substr(0, len);
		msg = msg.substr(len);

		buf = msg.substr(0, 2);
		msg = msg.substr(2);
		len = stoi(buf);

		std::string rName = msg.substr(0, len);
		msg = msg.substr(len);

		display->UpdateUserInfo(uName, rName);
		display->ResJoinRoom();
	}
	else if (buf == "rmls") {
		
		std::vector<Room> roomList;

		std::string buf = msg.substr(0, 4);
		msg = msg.substr(4);
		int count = stoi(buf);

		for (int i = 0; i < count; i++) {
			std::string buf = msg.substr(0, 4);
			msg = msg.substr(4);
			UINT rID = stoi(buf);

			buf = msg.substr(0, 2);
			msg = msg.substr(2);
			int len = stoi(buf);

			std::string rName = msg.substr(0, len);
			msg = msg.substr(len);

			roomList.push_back(Room(CString::CStringT(CA2CT(rName.c_str())), rID));

		}
		display->UpdateRoomList(roomList);
	}
	else if (buf == "norm") {

		std::string buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int len = stoi(buf);

		std::string uName = msg.substr(0, len);
		msg = msg.substr(len);

		buf = msg.substr(0, 2);
		msg = msg.substr(2);
		len = stoi(buf);

		std::string rName = msg.substr(0, len);
		msg = msg.substr(len);

		Message recvMsg;
		recvMsg.userName = CString(CA2CT(uName.c_str()));
		recvMsg.msg = CString(CA2CT(msg.c_str()));

		display->UpdateMessageList(recvMsg);
	}
	else if (buf == "noti") {
		std::string buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int code = stoi(buf);
		
		buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int len = stoi(buf);

		std::string rName = msg.substr(0, len);
		msg = msg.substr(len);

		if (code == 0) {
			Message recvMsg;
			recvMsg.userName = CString(std::string("_system").c_str());
			recvMsg.msg = CString(CA2CT(msg.c_str()));

			display->UpdateMessageList(recvMsg);
		}
		else {
			AfxMessageBox(_T("??"));
		}
			
	}
	else if (buf == "chcl") {
		std::string buf = msg.substr(0, 2);
		msg = msg.substr(2);
		int len = stoi(buf);

		std::string newName = msg.substr(0, len);
		msg = msg.substr(len);

		buf = msg.substr(0, 2);
		msg = msg.substr(2);
		len = stoi(buf);

		std::string oldName = msg.substr(0, len);
		msg = msg.substr(len);

		display->UpdateUserInfo(newName, "");
	}
	else {
		AfxMessageBox(_T("Protocol, Critical Error"));
	}
}
void Processor::MessageToServer(std::string msg) {
	transmission->Send(msg);
}