#pragma once

#include "DataSettings.h"
#include <vector>

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