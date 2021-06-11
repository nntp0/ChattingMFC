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
	int clientID;
	int joinedRoomID;

	Client() 
		: name(), clientID(), joinedRoomID() {}
	Client(std::string name, int clientID, int joinedRoomID) 
		: name(name), clientID(clientID), joinedRoomID(joinedRoomID) {}
};
struct Room {
	std::string name;
	int roomID=0;

	std::set<int> clientList;
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