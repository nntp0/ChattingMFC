#pragma once
#include "DataSettings.h"
#include <string>
#include <mutex>

// Display Module �� ����ؾ��ϴ� ������ ����
//	1. Caret �� ��ġ
//	2. BackSpace ����




class DataModule {

public:
	void INClearRoomList();
	void INClearMessageList();

	friend class CChildView;
private:
	CList<Message> messageList;
	CList<Room> RoomList;

	CString currRoom;
	CString myName;

private:
	std::mutex mtxMessageList;
	std::mutex mtxRoomList;
	std::mutex mtxCharInfo;	// Not Used
};