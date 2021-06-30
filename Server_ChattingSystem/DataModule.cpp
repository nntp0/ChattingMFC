#include "pch.h"
#include "DataModule.h"
#include <random>

std::string UTF8toUTF16(const char* utf8) {
	int length = MultiByteToWideChar(CP_UTF8, 0, utf8, (int)strlen(utf8) + 1, NULL, NULL);
	wchar_t* pBuf = new wchar_t[length + 1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, (int)strlen(utf8) + 1, pBuf, length);
	pBuf[length] = 0;
	std::string utf16 = std::string(CT2CA(pBuf));
	delete[] pBuf;

	return utf16;
}
//https://modoocode.com/304
int GetRandomNum(int size) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, size);

	return dis(gen);
}

DataModule::DataModule() {
	Room hall("Main Hall", createRoomID());
	roomList.push_back(hall);

	std::ifstream NameList("DefaultClientNameList.txt");
	std::string line;

	while (std::getline(NameList, line)) {
		this->nameList.push_back(UTF8toUTF16(line.c_str()));
	}
	nameListSize = nameList.size();
	NameList.close();
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
	newClient.name = createClientName() + std::to_string(newClient.clientID);
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
	targetClient->joinedRoom = -1;

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

bool DataModule::ChangeClientInfo(int clientID, std::string clientName) {
	for (auto iter = clientList.begin(); iter != clientList.end(); iter++) {
		if (iter->clientID == clientID) {
			iter->name = clientName;
			return true;
		}
	}
	return false;
}




int DataModule::createRoomID() { static int id = 0; return id++; }


std::string DataModule::createClientName() {
	if (nameListSize == 0) return "DefaultName";
	
	int idx = GetRandomNum(nameListSize);
	return nameList[idx];
}