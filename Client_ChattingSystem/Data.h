#pragma once
#include "DataSettings.h"
#include <string>
#include <mutex>

// Display Module 이 담당해야하는 데이터 영역
//	1. Caret 의 위치
//	2. BackSpace 정보




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