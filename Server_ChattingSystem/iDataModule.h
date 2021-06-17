#pragma once

#include "DataSettings.h"
#include <vector>

#ifndef __iDataModule_H_INCLUDED__
#define __iDataModule_H_INCLUDED__
__interface iDataModule {

public:
	virtual bool newRoom(Room);
	virtual bool newClient(Client);

	virtual bool closeClient(Client);

	virtual bool JoinRoom(Room, Client);
	virtual bool LeaveRoom(Client);

	virtual const std::vector<Room>& GetRoomList();
	virtual const std::vector<Client>& GetClientList();

	virtual Client* GetClient(int clientID);
	virtual Room* GetRoom(int roomID);
};
#endif