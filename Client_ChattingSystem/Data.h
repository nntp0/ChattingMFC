#pragma once
#include "DataSettings.h"
#include <mutex>
#include <vector>

class DataModule {

public:
	void INClearRoomList();
	void INClearMessageList();

private:
	std::vector<Message> messageList;
	std::vector<Room> RoomList;

	CString currRoom;
	CString myName;

private:
	std::mutex mtxMessageList;
	std::mutex mtxRoomList;


public:
	bool SetUserInfo(std::string userName, std::string roomName);
	bool UpdateRoomList(std::vector<Room> roomList);
	bool AddMessage(Message msg);

	std::vector<CString> GetRoomList();
	std::vector<Message> GetMessageList() {
		return messageList;
	}
	int GetRoomID(size_t index);
	int GetRoomListSize() {
		return RoomList.size();
	}
	CString GetCurrRoomName() {
		return currRoom;
	}
	CString GetMyName() {
		return myName;
	}
};