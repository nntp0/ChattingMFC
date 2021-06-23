#include "pch.h"
#include "Data.h"


void DataModule::UpdateRoomList(Room room) {
	this->mtxRoomList.lock();
	this->RoomList.AddTail(room);
	this->mtxRoomList.unlock();

	if (this->page == Page::RoomList) Invalidate();
}
void DataModule::UpdateMessageList(Message msg) {
	this->mtxMessageList.lock();
	this->messageList.AddHead(msg);
	this->mtxMessageList.unlock();

	if (this->page == Page::chattingRoom) Invalidate();
}
void DataModule::UpdateUserInfo(std::string userName, std::string roomName) {
	this->myName = CString(CA2CT(userName.c_str()));
	this->currRoom = CString(CA2CT(roomName.c_str()));
	if (this->page == Page::chattingRoom) Invalidate();
}
