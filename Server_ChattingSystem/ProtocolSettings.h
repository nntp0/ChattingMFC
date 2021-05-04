#pragma once

/*
*	통신에 이용할 데이터의 규격을 설정합니다.
*	
*	메세지의 길이와 메시지를 담습니다.
*	메세지의 최대 길이는 SIZE_OF_BUFFER 를 이용해 설정합니다.
* 
*/

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