#pragma once

#include <intsafe.h>
#include <afxstr.h>

struct Client {
	CString name;
	UINT id;
};

struct Room {
	CString name;
	UINT id;

	UINT currentNum;
	UINT maximumNum;
};