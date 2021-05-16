#include "pch.h"
#include "framework.h"
#include "Client_ChattingSystem.h"

#include <afxsock.h>
#include "locale.h"

#include "Transmission.h"

#include <Strsafe.h>

SocketTransmission::SocketTransmission(iMainFrame* mainFrame) {
	TRACE(_T("SocketTransmission Constructor"));

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
	TRACE(_T("SocketTransmission Send"));
	
	CString msg1 = this->MessageEncoding(msg);
	this->clientSocket->SendMsg(msg1);
}
void SocketTransmission::Receive(CString msg) {
	TRACE(_T("SocketTransmission Receive"));

	CString msg1 = this->MessageDecoding(msg);
	this->mainFrame->ControlMessage(msg1);
}
CString SocketTransmission::MessageEncoding(CString msg) {
	TRACE(_T("SocketTransmssion MessageEncoding"));

	/*CString temp = _T("nm");
	return temp+msg;*/

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