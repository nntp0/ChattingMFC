#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"
#include "TransmissionReceiver.h"

Transmission::Transmission() : buf(), nbytes(0) {
	AfxMessageBox(_T("Transmission 생성자 호출"));
	_tsetlocale(LC_ALL, _T(""));
	AfxSocketInit();

	clientSocket.Create();
	clientSocket.Connect(_T("127.0.0.1"), 8000);

	//AfxBeginThread(RUNTIME_CLASS(TransmissionReceiver));
}

Transmission::~Transmission() {
	AfxMessageBox(_T("Transmission 소멸자 호출"));
	clientSocket.Close();

	//m_receiver->PostThreadMessageW(WM_QUIT, 0, 0);
}

void Transmission::Connect() {
	for (int i = 0; i < 5; i++) {
		wsprintf(buf, _T("%d번째 테스트 메시지\r\n"), i + 1);
		nbytes = clientSocket.Send(buf, 256);
		Sleep(1000);
	}
}

void Transmission::SendMsg(CString msg) {
	AfxMessageBox(_T("Transmission SendMsg"));
	//wsprintf(buf, _T("%s"), msg.GetString()+1);
	//AfxMessageBox(buf);
	LPCWSTR str = msg.GetString();

	for (int i = lstrlen(str) + 8; i <= 100; i++) {
		int send = clientSocket.Send(str, i);
		Sleep(1000);
	}
	/*clientSocket.Send(str, lstrlen(str) + 6);
	Sleep(1000);
	clientSocket.Send(str, lstrlen(str) + 7);
	Sleep(1000);
	clientSocket.Send(str, 100);*/

	//wsprintf(buf, _T("%d"), send);
	//AfxMessageBox(buf);
}