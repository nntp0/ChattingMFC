#pragma once

#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"

#include <Strsafe.h>

SocketTransmission::SocketTransmission(iMainFrame* mainFrame) : buf() {
	AfxMessageBox(_T("SocketTransmission Constructor"));

	SetMainFrame(mainFrame);

	AfxSocketInit();

	clientSocket = new CClientSocket(this);
}

SocketTransmission::~SocketTransmission() {
	TRACE(_T("SocketTransmission Destructor"));

	clientSocket->Close();
	delete clientSocket;
}

/* 
* CString 에 담긴 Message 를 Client 에게 전송합니다.
* IN:	CString
* OUT:	void
*/
void SocketTransmission::Send(CString msg) {
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
			// SIZE_OF_BUFFER-1 은 마지막 문자는 '\0' 이기 때문에 제외했습니다.
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

void SocketTransmission::Receive() {
	AfxMessageBox(_T("SocketTransmission Receive"));
	AfxMessageBox(this->clientSocket->GetMsg()->message);

	this->mainFrame->ControlMessage(this->clientSocket->GetMsg()->message);
}

void SocketTransmission::Close() {
	AfxMessageBox(_T("Disconnected from Server!"));

	delete clientSocket;
}

void SocketTransmission::SetMainFrame(iMainFrame* mainFrame) {
	this->mainFrame = mainFrame;
}