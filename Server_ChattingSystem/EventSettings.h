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

#endif