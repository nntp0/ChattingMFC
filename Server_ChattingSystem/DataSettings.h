#pragma once

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

#include <intsafe.h>
#include <afxstr.h>
#include <vector>
#include <set>

struct Client {
	CString name;
	UINT id;

	//std::vector<UINT> joinedRoomList;
	UINT joinedRoom;

	Client() : name(), id() {
		//joinedRoomList.push_back(0);
		joinedRoom = -1;
	}
};

struct Room {
	CString name;
	UINT id;

	UINT currentNum;
	UINT maximumNum;

	std::set<UINT> clientList;
};
enum class MessageType {
	RoomCreation,
	RoomList,
	RoomJoin,
	RoomLeave,
	ClientList,
	Normal,
	Argent,
};
struct CustomMessage {
	MessageType type;
	CString msg;
};

#endif