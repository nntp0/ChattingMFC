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

// Transmission 모듈 자체도 Packaging 을 해줘야합니다.
// Encoding 과 Decoding 에서 해당 내용을 진행해주세요.
void SocketTransmission::Send(CString msg) {
	AfxMessageBox(_T("SocketTransmission Send"));
	
	CString msg1 = this->MessageEncoding(msg);
	this->clientSocket->SendMsg(msg1);
}
void SocketTransmission::Receive() {
	AfxMessageBox(_T("SocketTransmission Receive"));

	CString msg = this->MessageDecoding(this->clientSocket->GetMsg()->message);
	this->mainFrame->ControlMessage(msg);
}
CString SocketTransmission::MessageEncoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageEncoding"));
	return msg;
}
CString SocketTransmission::MessageDecoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageDecoding"));
	return msg;
}



void SocketTransmission::Close() {
	AfxMessageBox(_T("Disconnected from Server!"));

	delete clientSocket;
}
void SocketTransmission::SetMainFrame(iMainFrame* mainFrame) {
	this->mainFrame = mainFrame;
}