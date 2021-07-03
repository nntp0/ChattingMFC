#pragma once
#include "DataSettings.h"
#include <mutex>
#include <vector>

class DataModule {

public:
	void INClearRoomList();
	void INClearMessageList();
	void InClearClientList();

private:
	std::vector<Message> messageList;
	std::vector<Room> RoomList;

	CString currRoom;
	CString myName;

	std::vector<std::string> clientList;

private:
	std::mutex mtxMessageList;
	std::mutex mtxRoomList;
	std::mutex mtxClientList;


public:
	bool SetUserInfo(std::string userName, std::string roomName);
	bool AddClient(std::string clientName);
	bool UpdateRoomList(std::vector<Room> roomList);
	bool AddMessage(Message msg);

	std::vector<CString> GetRoomList();
	std::vector<Message> GetMessageList() {
		return messageList;
	}
	std::vector<std::string> GetClientList();

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