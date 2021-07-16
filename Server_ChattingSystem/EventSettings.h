#pragma once

#ifndef __Event_H_INCLUDED__
#define __Event_H_INCLUDED__

#include <intsafe.h>
#include <afxstr.h>
#include <string>

enum class EventList
{
	ClientConnection,
	ClientDisconnection,
	ReceiveMessage,
	Notification,
	SystemMessage,

	HeartBeat,
};

enum class ResponseList
{
	ClientConnected,
	ClientList,

	RoomCreated,
	RoomLeaved,
	RoomJoined,
	RoomList,

	ChangeClientInfo,

	Normal,

	HeartBeat,
};
struct ResponseInfo {
	std::string userName;
	std::string roomName;
	std::string extra;

	ResponseInfo(std::string userName, std::string roomName, std::string extra) 
		: userName(userName), roomName(roomName), extra(extra) {}
};

#endif