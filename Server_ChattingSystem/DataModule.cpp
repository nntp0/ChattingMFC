#include "pch.h"
#include "DataModule.h"

DataModule::DataModule() {
	Room hall;
	hall.roomID = 0;
	hall.name = "MainHall";
	roomList.push_back(hall);
}
DataModule::~DataModule() {}

void DataModule::newRoom(Room newRoom) {
	newRoom.roomID = this->roomList.size();
	this->roomList.push_back(newRoom);
}
void DataModule::newClient(Client newClient) {
	this->clientList.push_back(newClient);
}

void DataModule::closeRoom(Room closedRoom) {
	for (auto it = this->roomList.begin(); it != this->roomList.end(); it++) {
		if (it->roomID == closedRoom.roomID) {
			this->roomList.erase(it);
			break;
		}
	}
}
void DataModule::closeClient(Client closedClient) {
	Room updatedRoom;
	for (auto it = this->clientList.begin(); it != this->clientList.end(); it++) {
		if (it->clientID == closedClient.clientID) {
			updatedRoom.roomID = it->joinedRoomID;
			this->clientList.erase(it);
			break;
		}
	}
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == updatedRoom.roomID) {
			roomIter->clientList.erase(closedClient.clientID);
			break;
		}
	}
}

void DataModule::JoinRoom(Room room, Client client) {
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == 0) {
			roomIter->clientList.erase(client.clientID);
			break;
		}
	}
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == room.roomID) {
			roomIter->clientList.insert(client.clientID);
			break;
		}
	}
	for (auto clientIter = clientList.begin(); clientIter != clientList.end(); clientIter++) {
		if (clientIter->clientID == client.clientID) {
			clientIter->joinedRoomID = room.roomID;
			break;
		}
	}
}
void DataModule::LeaveRoom(Room room, Client client) {
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == room.roomID) {
			roomIter->clientList.erase(client.clientID);
			break;
		}
	}
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == 0) {
			roomIter->clientList.insert(client.clientID);
			break;
		}
	}
	for (auto clientIter = clientList.begin(); clientIter != clientList.end(); clientIter++) {
		if (clientIter->clientID == client.clientID) {
			clientIter->joinedRoomID = 0;
			break;
		}
	}
}

std::string DataModule::GetClientName(int clientID) {
	for (auto clientIter = clientList.begin(); clientIter != clientList.end(); clientIter++) {
		if (clientIter->clientID == clientID) {
			return clientIter->name;
		}
	}
	return "";
}
std::string DataModule::GetRoomName(int roomID) {
	for (auto iter = roomList.begin(); iter != roomList.end(); iter++) {
		if (iter->roomID == roomID) {
			return iter->name;
		}
	}
	return "";
}


const std::vector<Room> DataModule::getRoomList() {
	return this->roomList;
}
const std::vector<Client> DataModule::getClientList() {
	return this->clientList;
}