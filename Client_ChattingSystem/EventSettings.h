#pragma once

#include <string>

enum class ResponseList
{
	ClientConnected,
	ClientList,

	RoomCreated,
	RoomLeaved,
	RoomJoined,
	RoomList,

	Normal,
};
struct ResponseInfo {
	std::string userName;
	std::string roomName;
	std::string extra;
};