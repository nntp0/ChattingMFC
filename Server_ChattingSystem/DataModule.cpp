#include "pch.h"
#include "DataModule.h"

DataModule::DataModule() {}
DataModule::~DataModule() {}

void DataModule::newRoom(Room newRoom) {
	newRoom.id = this->roomList.size();
	this->roomList.push_back(newRoom);
}
void DataModule::newClient(Client newClient) {
	this->clientList.push_back(newClient);
}

void DataModule::closeRoom(Room closedRoom) {
	for (auto it = this->roomList.begin(); it != this->roomList.end(); it++) {
		if (it->id == closedRoom.id) {
			this->roomList.erase(it);
			break;
		}
	}
}
void DataModule::closeClient(Client closedClient) {
	for (auto it = this->clientList.begin(); it != this->clientList.end(); it++) {
		if (it->id == closedClient.id) {
			this->clientList.erase(it);
			break;
		}
	}
}

void DataModule::JoinRoom(Room room, Client client) {
	for (auto it = roomList.begin(); it != roomList.end(); it++) {
		if (it->id == room.id) {
			it->clientList.insert(client.id);
			break;
		}
	}
	for (auto it = clientList.begin(); it != clientList.end(); it++) {
		if (it->id == client.id) {
			it->joinedRoom = room.id;
			break;
		}
	}
}
void DataModule::LeaveRoom(Room room, Client client) {
	for (auto it = roomList.begin(); it != roomList.end(); it++) {
		if (it->id == room.id) {
			it->clientList.erase(client.id);
		}
	}
	for (auto it = clientList.begin(); it != clientList.end(); it++) {
		if (it->id == client.id) {
			it->joinedRoom = -1;
			break;
		}
	}
}

const std::vector<Room> DataModule::getRoomList() {
	return this->roomList;
}
const std::vector<Client> DataModule::getClientList() {
	return this->clientList;
}