#pragma once

enum class EventList
{
	ClientConnection,
	ClientDisconnection,
	ReceiveMessage,
	Notification
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