#include "pch.h"
#include "Data.h"

void DataModule::INClearRoomList() {
	mtxRoomList.lock();
	RoomList.clear();
	mtxRoomList.unlock();
}
void DataModule::INClearMessageList() {
	mtxMessageList.lock();
	messageList.clear();
	mtxMessageList.unlock();
}
void DataModule::InClearClientList() {
	mtxClientList.lock();
	clientList.clear();
	mtxClientList.unlock();
}

bool DataModule::UpdateRoomList(std::vector<Room> roomList) {
	mtxRoomList.lock();
	this->RoomList.assign(roomList.begin(), roomList.end());
	mtxRoomList.unlock();

	return true;
}

bool DataModule::AddMessage(Message msg) {

	mtxMessageList.lock();
	messageList.push_back(msg);
	mtxMessageList.unlock();

	return true;
}
bool DataModule::AddClient(std::string clientName) {

	mtxClientList.lock();
	clientList.push_back(clientName);
	mtxClientList.unlock();

	return true;
}


bool DataModule::SetUserInfo(std::string userName, std::string roomName = "") {
	myName = CString(CA2CT(userName.c_str()));
	if (roomName != "") currRoom = CString(CA2CT(roomName.c_str()));

	return true;
}
int DataModule::GetRoomID(size_t index) {
	if (RoomList.size() <= index) return -2;
	return RoomList[index].roomID;
}
std::vector<CString> DataModule::GetRoomList() {
	std::vector<CString> roomNameList;
	mtxRoomList.lock();
	for (auto iter = RoomList.cbegin(); iter != RoomList.cend(); iter++) {
		roomNameList.push_back(iter->name);
	}
	mtxRoomList.unlock();

	return roomNameList;
}

std::vector<std::string> DataModule::GetClientList() {
	return clientList;
}