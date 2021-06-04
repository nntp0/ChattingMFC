#pragma once

#include "DataSettings.h"
#include <vector>

#ifndef __iDataModule_H_INCLUDED__
#define __iDataModule_H_INCLUDED__
__interface iDataModule {

public:
	virtual void newRoom(Room);
	virtual void newClient(Client);

	virtual void closeRoom(Room);
	virtual void closeClient(Client);

	virtual void JoinRoom(Room, Client);
	virtual void LeaveRoom(Room, Client);

	virtual const std::vector<Room> getRoomList();
	virtual const std::vector<Client> getClientList();
};
#endif