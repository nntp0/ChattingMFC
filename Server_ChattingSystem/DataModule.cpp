#include "pch.h"
#include "DataModule.h"

DataModule::DataModule() {
	Room hall("Main Hall", 0);
	roomList.push_back(hall);
}
DataModule::~DataModule() {}

bool DataModule::newRoom(Room newRoom) {

	bool isExistName = false;
	for (auto iter = roomList.begin(); iter != roomList.end(); iter++) {
		if (iter->name == newRoom.name) isExistName = true;
	}
	if (isExistName) return false;

	newRoom.roomID = createRoomID();
	this->roomList.push_back(newRoom);
	return true;
}
bool DataModule::newClient(Client newClient) {
	this->clientList.push_back(newClient);
	return true;
}

bool DataModule::closeClient(Client closedClient) {
	bool isErased = false;
	for (auto it = this->clientList.begin(); it != this->clientList.end(); it++) {
		if (it->clientID == closedClient.clientID) {
			isErased = true;
			this->clientList.erase(it);
			break;
		}
	}
	return isErased;
}

bool DataModule::JoinRoom(Room room, Client client) {
	Room* targetRoom = GetRoom(room.roomID);
	Client* targetClient = GetClient(client.clientID);

	if (targetRoom == nullptr || targetClient == nullptr) return false;

	targetRoom->clientList.insert(client.clientID);
	targetClient->joinedRoom = room.roomID;

	return true;
}
bool DataModule::LeaveRoom(Client client) {
	
	Client* targetClient = GetClient(client.clientID);
	if (targetClient == nullptr) return false;
	
	int roomID = targetClient->joinedRoom;
	for (auto roomIter = roomList.begin(); roomIter != roomList.end(); roomIter++) {
		if (roomIter->roomID == roomID) {
			roomIter->clientList.erase(client.clientID);
			break;
		}
	}

}

Client* DataModule::GetClient(int clientID) {
	auto iter = clientList.begin();

	for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
		if (iter->clientID == clientID) return iter._Ptr;
	}

	return nullptr;
}
Room* DataModule::GetRoom(int roomID) {
	auto iter = roomList.begin();

	for (auto iter = roomList.begin(); iter != roomList.end(); iter++) {
		if (iter->roomID == roomID) return iter._Ptr;
	}
	
	return nullptr;
}


const std::vector<Room>& DataModule::GetRoomList() {
	return this->roomList;
}
const std::vector<Client>& DataModule::GetClientList() {
	return this->clientList;
}

int DataModule::createRoomID() { static int id = 0; return id++; }
int DataModule::createClientID() { static int id = 0; return id++; }