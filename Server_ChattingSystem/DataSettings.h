#pragma once

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

#include <intsafe.h>
#include <afxstr.h>
#include <vector>
#include <set>

struct Client {
	CString name;
	UINT clientID;

	//std::vector<UINT> joinedRoomList;
	UINT joinedRoomID;

	Client() : name(), clientID() {
		//joinedRoomList.push_back(0);
		joinedRoomID = 0;
	}
};
struct Room {
	CString name;
	UINT roomID=0;

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
	MessageType type = MessageType::Normal;
	CString msg;
};

#endif