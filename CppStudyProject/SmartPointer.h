#pragma once

#ifndef __AFXSOCK_H_INCLUDED__
#define __AFXSOCK_H_INCLUDED__
#include <afxsock.h>
#endif

class SmartPointerPractice {
	// Constructor / Destructor
public:
	SmartPointerPractice();
	~SmartPointerPractice();
	
	// Methods
public:
	void OnAccept(UINT portNum);
	void ShowList();

	void Test();
private:
	//std::vector<std::shared_ptr<CSocket>> m_SocketList;

	std::vector<std::shared_ptr<int>> m_SocketList;
	//std::vector<UINT> m_SocketList;
};