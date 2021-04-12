#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"
#include "TransmissionReceiver.h"

Transmission::Transmission() : buf(), nbytes(0) {
	AfxMessageBox(_T("������ ȣ��"));
	_tsetlocale(LC_ALL, _T(""));
	AfxSocketInit();

	clientSocket.Create();
	clientSocket.Connect(_T("127.0.0.1"), 8000);
}

Transmission::~Transmission() {
	AfxMessageBox(_T("�Ҹ��� ȣ��"));
	clientSocket.Close();

	m_receiver->PostThreadMessageW(WM_QUIT, 0, 0);
}

void Transmission::Connect() {
	for (int i = 0; i < 5; i++) {
		wsprintf(buf, _T("%d��° �׽�Ʈ �޽���\r\n"), i + 1);
		nbytes = clientSocket.Send(buf, 256);
		Sleep(1000);
	}
	
	/*int val = 600;
	AfxBeginThread(CalcIt, (LPVOID)val);*/
}