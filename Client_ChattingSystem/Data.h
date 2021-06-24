#pragma once
#include "DataSettings.h"
#include <mutex>
#include <vector>

class DataModule {
	friend class CChildView;
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

	std::vector<CString> GetRoomList() {
		std::vector<CString> roomNameList;
		mtxRoomList.lock();
		for (auto iter = RoomList.cbegin(); iter != RoomList.cend(); iter++) {
			roomNameList.push_back(iter->name);
		}
		mtxRoomList.unlock();

		return roomNameList;
	}
	std::vector<Message> GetMessageList() {
		return messageList;
	}
	int GetRoomID(size_t index) {
		if (RoomList.size() > index) return -2;
		return RoomList[index].roomID;
	}
	int GetRoomListSize() {
		return RoomList.size();
	}
};