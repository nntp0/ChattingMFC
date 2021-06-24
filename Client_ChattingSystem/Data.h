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
	CList<Message> messageList;
	CList<Room> RoomList;

	CString currRoom;
	CString myName;

private:
	std::mutex mtxMessageList;
	std::mutex mtxRoomList;


public:
	bool SetUserInfo(std::string userName, std::string roomName);
	bool UpdateRoomList(std::vector<Room> roomList);
	bool AddMessage(Message msg);
};