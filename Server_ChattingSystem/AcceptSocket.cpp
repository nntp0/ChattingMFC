#include "pch.h"
#include "framework.h"

#include "Transmission.h"

#include <Strsafe.h>

// Constructor / Destructor
CAcceptSocket::CAcceptSocket(SocketTransmission *transmission) : m_msg() {
	TRACE(_T("CAcceptSocket Constructor"));
	this->SetTransmission(transmission);
}
CAcceptSocket::~CAcceptSocket() {
	TRACE("CAcceptSocket Destructor");
	this->Close();
}

void CAcceptSocket::SetTransmission(SocketTransmission* transmission) {
	TRACE(_T("CAcceptSocket SetTransmission"));
	this->transmission = transmission;
}
void CAcceptSocket::SetSocketID(UINT id) {
	this->id = id;
}
void CAcceptSocket::OnClose(int nErrorCode) {
	TRACE(_T("AcceptSocket OnClose"));
	this->transmission->Close(this->id);
}
void CAcceptSocket::OnReceive(int nErrorCode) {
	TRACE(_T("AcceptSocket OnReceive"));

	this->RecvMsg();
	this->transmission->Receive(this->m_msg.message);
}

void CAcceptSocket::SetMsg(MessageForm msg) {
    this->m_msg = msg;
}
MessageForm* CAcceptSocket::GetMsg() {
    return &(this->m_msg);
}

void CAcceptSocket::RecvMsg() {
	MessageForm msgBuffer;

	while (1) {
		int nbytes = this->Receive(&msgBuffer, sizeof MessageForm);
		//#ifdef _DEBUG
		//		TCHAR buf[SIZE_OF_BUFFER];
		//		wsprintf(buf, _T("%d\n"), nbytes);
		//		AfxMessageBox(buf);
		//#endif
		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			this->SetMsg(msgBuffer);

			// 이 구문을 확인을 못하고 있었다!
			// 이 구문으로 인해 데이터가 제대로 작동하지 않고 있었음
			if (msgBuffer.messageLen != SIZE_OF_BUFFER) break;
		}
	}
}
void CAcceptSocket::SendMsg(CString msg) {
	TRACE(_T("CAcceptSocket SendMessage"));

	MessageForm msgForm;
	while (1) {
		if (msg.GetLength() < SIZE_OF_BUFFER) {
			msgForm.messageLen = msg.GetLength();

			::StringCchPrintf(msgForm.message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());

			this->Send(&msgForm, sizeof MessageForm);
			break;
		}
		else {
			// SIZE_OF_BUFFER-1 은 마지막 문자는 '\0' 이기 때문에 제외했습니다.
			msgForm.messageLen = SIZE_OF_BUFFER - 1;

			::StringCchPrintf(msgForm.message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			int temp = msg.Delete(0, SIZE_OF_BUFFER - 1);

			this->Send(&msgForm, sizeof MessageForm);
		}
	}
}

UINT CAcceptSocket::GetSocketID() {
	return this->id;
}