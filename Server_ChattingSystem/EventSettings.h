#pragma once

#ifndef __Event_H_INCLUDED__
#define __Event_H_INCLUDED__

#include <intsafe.h>
#include <afxstr.h>

enum class EventList
{
	ClientConnection,
	ClientDisconnection,
	ReceiveMessage,
	Notification,
};

struct Info_ClientConnection {
	UINT socketID;
};
struct Info_ClientDisconnection {
	UINT socketID;
};
struct Info_ReceiveMessage {
	UINT socketID;
	CString msg;
};
struct Info_Notification {
	CString msg;
};

#endif