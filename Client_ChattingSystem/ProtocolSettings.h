#pragma once

#ifndef __PROTOCOL_H_INCLUDED__
#define __PROTOCOL_H_INCLUDED__

#include <tchar.h>
#include <strsafe.h>

#define SIZE_OF_BUFFER 256

struct MessageForm {
	int messageLen;
	TCHAR message[SIZE_OF_BUFFER];

	MessageForm& operator=(const MessageForm& other) {
		StringCchCopy(this->message, SIZE_OF_BUFFER, other.message);
		this->messageLen = other.messageLen;

		return *this;
	}
};

#endif