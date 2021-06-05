#pragma once

#include <set>

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

struct Room {
	CString name;
	UINT roomID = 0;

	std::set<UINT> clientList;
};

#endif