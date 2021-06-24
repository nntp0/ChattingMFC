#include "pch.h"
#include "ChildView.h"

void DataModule::INClearRoomList() {
	this->mtxRoomList.lock();
	this->RoomList.RemoveAll();
	this->mtxRoomList.unlock();
}
void DataModule::INClearMessageList() {
	this->mtxMessageList.lock();
	this->messageList.RemoveAll();
	this->mtxMessageList.unlock();
}