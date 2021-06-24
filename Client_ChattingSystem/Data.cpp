#include "pch.h"
#include "Data.h"

void DataModule::INClearRoomList() {
	mtxRoomList.lock();
	RoomList.RemoveAll();
	mtxRoomList.unlock();
}
void DataModule::INClearMessageList() {
	mtxMessageList.lock();
	messageList.RemoveAll();
	mtxMessageList.unlock();
}

bool DataModule::UpdateRoomList(std::vector<Room> roomList) {
	mtxRoomList.lock();
	RoomList.RemoveAll();
	for (auto iter = roomList.begin(); iter != roomList.end(); iter++) {
		RoomList.AddTail(*iter);
	}
	mtxRoomList.unlock();

	return true;
}

bool DataModule::AddMessage(Message msg) {
	mtxMessageList.lock();
	messageList.AddHead(msg);
	mtxMessageList.unlock();

	return true;
}
bool DataModule::SetUserInfo(std::string userName, std::string roomName) {
	myName = CString(CA2CT(userName.c_str()));
	currRoom = CString(CA2CT(roomName.c_str()));

	return true;
}