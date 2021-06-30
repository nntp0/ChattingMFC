#pragma once

#include "iDataModule.h"
#include <iostream>
#include <fstream>

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

	virtual bool ChangeClientInfo(int, std::string);

public:

	virtual Client* GetClient(int clientID);
	virtual Room* GetRoom(int roomID);

private:
	std::vector<Client> clientList;
	std::vector<Room> roomList;

	std::vector<std::string> nameList;
	int nameListSize;
private:
	int createRoomID();
	std::string createClientName();
};
#endif