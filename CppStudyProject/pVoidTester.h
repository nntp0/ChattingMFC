#pragma once

#include <string>
#include <iostream>

enum class EventList {
	A = 0x00,
	B = 0x01,
	C = 0x02,
	D = 0x03
};
struct Info_EventA {
	int id;
};
struct Info_EventB {
	std::string msg;
};
struct Info_EventC {
public:
	Info_EventC(int id, std::string msg) {
		this->id = id;
		this->msg = msg;
	}

	int id;
	std::string msg;
};
struct Info_EventD {
public:

	Info_EventD(int id, double num) {
		this->id = id; this->num = num;
	}

	int id;
	double num;
};


class pVoidTester {
public:
	pVoidTester() = default;
	virtual ~pVoidTester() = default;

	// properties
private:

	// methods
public:
	void EventControl(EventList, void*);

	void Test();
};