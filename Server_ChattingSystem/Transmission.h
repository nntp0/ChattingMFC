#pragma once
#ifndef __ListenSocket_H_INCLUDED__
#define __ListenSocket_H_INCLUDED__
#include "ListenSocket.h"
#endif
#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
#include "AcceptSocket.h"
#endif
#ifndef __MEMORY_H_INCLUDED__
#define __MEMORY_H_INCLUDED__
#include <memory>
#endif
#ifndef __PROTOCOL_H_INCLUDED__
#define __PROTOCOL_H_INCLUDED__
#define SIZE_OF_BUFFER 256
struct MessageForm {
	int messageLen;
	TCHAR message[SIZE_OF_BUFFER];
};
#endif

class Transmission
{
public:
	Transmission();
	virtual ~Transmission();
public:
	void Accept();

private:
	CListenSocket listenSocket = nullptr;
	CList<std::shared_ptr<CAcceptSocket>, std::shared_ptr<CAcceptSocket>> acceptSocketList;
};

