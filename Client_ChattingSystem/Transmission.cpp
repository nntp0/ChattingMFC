#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"

#include <Strsafe.h>

#define SIZE_OF_BUFFER 256


struct MessageForm {
	int messageLen;
	TCHAR message[SIZE_OF_BUFFER];
};

Transmission::Transmission() : buf(), nbytes(0) {
	AfxMessageBox(_T("Transmission ������ ȣ��"));

	AfxSocketInit();

	clientSocket.Create();
	clientSocket.Connect(_T("127.0.0.1"), 8000);
}

Transmission::~Transmission() {
	AfxMessageBox(_T("Transmission �Ҹ��� ȣ��"));
	clientSocket.Close();
}

/* 
* CString �� ��� Message �� Client ���� �����մϴ�.
* IN:	CString
* OUT:	void
*/
void Transmission::SendMsg(CString msg) {
	AfxMessageBox(_T("Transmission SendMsg"));

	MessageForm* pMsgForm = new MessageForm;

	while (1) {
		if (msg.GetLength() < SIZE_OF_BUFFER) {
			pMsgForm->messageLen = msg.GetLength();
			::StringCchPrintf(pMsgForm->message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			clientSocket.Send(pMsgForm, sizeof MessageForm);
			break;
		}
		else {
			// SIZE_OF_BUFFER-1 �� ������ ���ڴ� '\0' �̱� ������ �����߽��ϴ�.
			pMsgForm->messageLen = SIZE_OF_BUFFER-1;

			::StringCchPrintf(pMsgForm->message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			int temp = msg.Delete(0, SIZE_OF_BUFFER-1);

			TCHAR buf[20];
			wsprintf(buf, _T("%d"), temp);
			AfxMessageBox(buf);
			clientSocket.Send(pMsgForm, sizeof MessageForm);
		}
	}
	delete pMsgForm;
}