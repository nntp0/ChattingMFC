#pragma once



#ifndef __PROTOCOL_H_INCLUDED__
#define __PROTOCOL_H_INCLUDED__

#include <tchar.h>

#define SIZE_OF_BUFFER 256

struct MessageForm {
	int messageLen;
	TCHAR message[SIZE_OF_BUFFER];
};
#endif