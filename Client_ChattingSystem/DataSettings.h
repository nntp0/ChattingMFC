#pragma once

#include <set>

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

struct Room {
	CString name;
	int roomID = 0;

public:
	Room() {}
	Room(CString name, UINT id) : name(name), roomID(id) {}
};
struct Message {
	CString userName;
	CString msg;
	enum class Type {
		System,
		Me,
		Others
	};
	Type type;
};

#endif