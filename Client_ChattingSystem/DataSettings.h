#pragma once

#include <set>

#ifndef __Data_H_INCLUDED__
#define __Data_H_INCLUDED__

struct Room {
	CString name;
	UINT roomID = 0;
};
struct Message {
	CString userName;
	CString msg;
};

#endif