#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"
#include "TransmissionReceiver.h"

Transmission::Transmission() : buf(), nbytes(0) {
	AfxMessageBox(_T("Transmission ������ ȣ��"));
	_tsetlocale(LC_ALL, _T(""));
	AfxSocketInit();

	clientSocket.Create();
	clientSocket.Connect(_T("127.0.0.1"), 8000);

	//AfxBeginThread(RUNTIME_CLASS(TransmissionReceiver));
}

Transmission::~Transmission() {
	AfxMessageBox(_T("Transmission �Ҹ��� ȣ��"));
	clientSocket.Close();

	//m_receiver->PostThreadMessageW(WM_QUIT, 0, 0);
}

void Transmission::Connect() {
	for (int i = 0; i < 5; i++) {
		wsprintf(buf, _T("%d��° �׽�Ʈ �޽���\r\n"), i + 1);
		nbytes = clientSocket.Send(buf, 256);
		Sleep(1000);
	}
}

void Transmission::SendMsg(CString msg) {
	AfxMessageBox(_T("Transmission SendMsg"));
	//wsprintf(buf, _T("%s"), msg.GetString()+1);
	//AfxMessageBox(buf);
	
	CW2A str(msg, CP_UTF8);

	clientSocket.Send(str, 34);
}