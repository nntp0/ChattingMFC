#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"

#include <Strsafe.h>

Transmission::Transmission(iMainFrame* mainFrame) : buf() {
	AfxMessageBox(_T("Transmission Constructor"));

	SetMainFrame(mainFrame);
	this->mainFrame->Tick();

	AfxSocketInit();

	clientSocket = new CClientSocket(this);
}

Transmission::~Transmission() {
	TRACE(_T("Transmission Destructor"));

	clientSocket->Close();
	delete clientSocket;
}

/* 
* CString �� ��� Message �� Client ���� �����մϴ�.
* IN:	CString
* OUT:	void
*/
void Transmission::Send(CString msg) {
	AfxMessageBox(_T("Transmission Send"));

	MessageForm* pMsgForm = new MessageForm;
	
	while (1) {
		if (msg.GetLength() < SIZE_OF_BUFFER) {
			pMsgForm->messageLen = msg.GetLength();
			wsprintf(buf, _T("%d"), pMsgForm->messageLen);
			AfxMessageBox(buf);

			::StringCchPrintf(pMsgForm->message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			AfxMessageBox(pMsgForm->message);

			
			clientSocket->Send(pMsgForm, sizeof MessageForm);
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
			clientSocket->Send(pMsgForm, sizeof MessageForm);
		}
	}
	delete pMsgForm;
}

void Transmission::Receive() {
	AfxMessageBox(_T("Received Message"));
	TCHAR buf[SIZE_OF_BUFFER];

	TCHAR msgBuffer[sizeof MessageForm];
	int nbytes;

	MessageForm* pMsgBuffer = new MessageForm;

	while (1) {
		nbytes = this->clientSocket->Receive(msgBuffer, sizeof MessageForm);
		wsprintf(buf, _T("%d\n"), nbytes);

		AfxMessageBox(buf);
		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			AfxMessageBox(_T("OK!"));

			::CopyMemory(pMsgBuffer, msgBuffer, sizeof MessageForm);

			this->clientSocket->SetMsg(*pMsgBuffer);
			AfxMessageBox(this->clientSocket->GetMsg()->message);

			// �� ������ Ȯ���� ���ϰ� �־���!
			// �� �������� ���� �����Ͱ� ����� �۵����� �ʰ� �־���
			if (pMsgBuffer->messageLen != SIZE_OF_BUFFER) break;
		}
	}

	delete pMsgBuffer;
}

void Transmission::Close() {
	AfxMessageBox(_T("Disconnected from Server!"));

	delete clientSocket;
}

void Transmission::SetMainFrame(iMainFrame* mainFrame) {
	this->mainFrame = mainFrame;
}