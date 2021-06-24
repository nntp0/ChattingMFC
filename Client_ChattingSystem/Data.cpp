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
bool DataModule::SetUserInfo(std::string userName, std::string roomName) {
	myName = CString(CA2CT(userName.c_str()));
	currRoom = CString(CA2CT(roomName.c_str()));

	return true;
}