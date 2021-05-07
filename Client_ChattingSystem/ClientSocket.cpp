#include "pch.h"
#include "framework.h"

#include "Transmission.h"

// Consturctor / Destructor
CClientSocket::CClientSocket(SocketTransmission *transmission) : m_msg(){
	TRACE("CClientSocket Constructor");

	SetTransmission(transmission);

	this->Create();
	this->Connect(_T("127.0.0.1"), 8000);
}
CClientSocket::~CClientSocket() {
	TRACE("CClientSocket Destructor");

	this->Close();
}

void CClientSocket::SetTransmission(SocketTransmission* transmission) {
	TRACE(_T("CClientSocket SetTransmission"));
	this->transmission = transmission;
}
void CClientSocket::OnClose(int nErrorCode) {
	TRACE(_T("CClientSocket OnClose"));
	this->transmission->Close();
}

// The Objective of OnReceive?
//	: When Socket Receives a Message, then Notify it to Transmission
void CClientSocket::OnReceive(int nErrorCode) {
	TRACE(_T("CClientSocket OnReceive"));
	this->RecvMsg();
	this->transmission->Receive();
}

void CClientSocket::SetMsg(MessageForm msg) {
	this->m_msg = msg;
}
MessageForm* CClientSocket::GetMsg() {
	return &(this->m_msg);
}

void CClientSocket::RecvMsg() {
	TCHAR buf[SIZE_OF_BUFFER];
	//TCHAR msgBuffer[sizeof MessageForm];

	int nbytes;

	MessageForm msgBuffer;

	while (1) {
		nbytes = this->Receive(&msgBuffer, sizeof MessageForm);
		wsprintf(buf, _T("%d\n"), nbytes);

		AfxMessageBox(buf);
		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			TRACE(_T("OK!"));

			//::CopyMemory(&msgBuffer, msgBuffer, sizeof MessageForm);

			this->SetMsg(msgBuffer);
			AfxMessageBox(this->GetMsg()->message);

			// 이 구문을 확인을 못하고 있었다!
			// 이 구문으로 인해 데이터가 제대로 작동하지 않고 있었음
			if (msgBuffer.messageLen != SIZE_OF_BUFFER) break;
		}
	}
	//delete msgBuffer;
}
void CClientSocket::SendMsg() {

}