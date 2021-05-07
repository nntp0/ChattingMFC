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
	AfxMessageBox(_T("SocketTransmission Send"));
	
	CString msg1 = this->MessageEncoding(msg);
	this->clientSocket->SendMsg(msg1);
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


CString SocketTransmission::MessageEncoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageEncoding"));
	return msg;
}
CString SocketTransmission::MessageDecoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageDecoding"));
	return msg;
}