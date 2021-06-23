#pragma once
#include "DataSettings.h"
#include <string>
#include <mutex>

// Display Module 이 담당해야하는 데이터 영역
//	1. Caret 의 위치
//	2. BackSpace 정보

struct CaretInfo {
public:
	CPoint offset;
	CArray<int, int> lineInfo;

public:
	CaretInfo() : offset(0, 0), lineInfo() {}

public:
	void Clear() {
		offset.x = 0;
		offset.y = 0;
		lineInfo.RemoveAll();
	}
};
struct BackSpaceInfo {
	bool isX;
	int size;

	BackSpaceInfo() : isX(false), size(0) {}
	BackSpaceInfo(bool isX, int size) : isX(isX), size(size) {}
};


class DataModule {

// (External)
// Data Module 에서 불러들여옴
private:
	CList<Message> messageList;
	CList<Room> RoomList;

	CString currRoom;
	CString myName;

private:
	std::mutex mtxMessageList;
	std::mutex mtxRoomList;
	std::mutex mtxCharInfo;	// Not Used


public:
	void UpdateRoomList(Room);
	void UpdateMessageList(Message);
	void UpdateUserInfo(std::string userName, std::string roomName);


	enum class Page {
		chattingRoom,
		RoomList
	};
	Page page = Page::chattingRoom;


	// (Internal)
	// Module 내에서만 사용 됨
private:
	int pointedRoom = -1;

	CString m_str;
	CArray<BackSpaceInfo, BackSpaceInfo> m_strSize;
	CaretInfo m_caretInfo;
};