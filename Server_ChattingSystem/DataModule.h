#pragma once

#include "iDataModule.h"

#ifndef __DataModule_H_INCLUDED__
#define __DataModule_H_INCLUDED__
class DataModule : public iDataModule {

public:
	DataModule();
	virtual ~DataModule();

public:
	virtual bool newRoom(Room);
	virtual bool newClient(Client);

	virtual bool closeClient(Client);

	virtual bool JoinRoom(Room, Client);
	virtual bool LeaveRoom(Client);

	virtual const std::vector<Room>& GetRoomList();
	virtual const std::vector<Client>& GetClientList();

public:

	virtual Client* GetClient(int clientID);
	virtual Room* GetRoom(int roomID);

private:
	std::vector<Client> clientList;
	std::vector<Room> roomList;

private:
	int createRoomID();
	int createClientID();
};
#endif