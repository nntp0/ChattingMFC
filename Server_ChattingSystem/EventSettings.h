#pragma once

#include <intsafe.h>
#include <afxstr.h>

enum class EventList
{
	ClientConnection,
	ClientDisconnection,
	ReceiveMessage,
	Notification,
	RoomCreate,
	RoomClose
};

struct Info_ClientConnection {
	UINT id;
};
struct Info_ClientDisconnection {
	UINT id;
};
struct Info_ReceiveMessage {
	UINT id;
	CString msg;
};
struct Info_Notification {
	CString msg;
};

enum class ModuleList
{
	iCoreModule,
	iTransmission,
	iDataModule,
	iDisplayModule
};

struct Args_CreateRoom {
	UINT id;
	CString name;
};
struct Args_CreateClient {
	UINT id;
};