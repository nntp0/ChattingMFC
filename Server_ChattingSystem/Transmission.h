#pragma once

#ifndef __ListenSocket_H_INCLUDED__
#define __ListenSocket_H_INCLUDED__
#include "ListenSocket.h"
#endif
#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
#include "AcceptSocket.h"
#endif

class Transmission
{
public:
	Transmission();
	virtual ~Transmission();
public:
	void Accept();

private:
	CListenSocket listenSocket;
	CList<std::shared_ptr<CAcceptSocket>, std::shared_ptr<CAcceptSocket>> acceptSocketList;
};

