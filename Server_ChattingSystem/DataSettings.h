#pragma once

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

#include <intsafe.h>
#include <afxstr.h>
#include <vector>
#include <set>

#include "AMQPSettings.h"

struct Client {
	std::string name;
	UINT clientID;

	//std::vector<UINT> joinedRoomList;
	UINT joinedRoomID;

	Client() : name(), clientID() {
		//joinedRoomList.push_back(0);
		joinedRoomID = 0;
	}
};
struct Room {
	std::string name;
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
	UID uid;
	MessageType type = MessageType::Normal;
	std::string body;
};

#endif