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
	this->transmission->Receive(this->m_msg);
}

// Setter / Getter
// 지금은 단순 대입하지만, 추후에 어떤 msg 들이 오고갔는지 로그를 남기는 함수로 변경할 예정
void CClientSocket::SetMsg(CString msg) {
	this->m_msg = msg;
}
CString* CClientSocket::GetMsg() {
	return &(this->m_msg);
}

void CClientSocket::RecvMsg() {
	CString msg = _T("");
	MessageForm msgBuffer;

	while (1) {
		int nbytes = this->Receive(&msgBuffer, sizeof MessageForm);

		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			msg += msgBuffer.message;
			if (msgBuffer.messageLeftLength == 0) {
				this->SetMsg(msg);
				break;
			}
		}
	}
}
void CClientSocket::SendMsg(CString msg) {
	TRACE(_T("CClientSocket SendMessage"));
	
	MessageForm msgForm;
	while (1) {
		if (msg.GetLength() < SIZE_OF_BUFFER) {
			msgForm.messageLen = msg.GetLength();
			msgForm.messageLeftLength = 0;

			::StringCchPrintf(msgForm.message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());

			this->Send(&msgForm, sizeof MessageForm);
			break;
		}
		else {
			// SIZE_OF_BUFFER-1 은 마지막 문자는 '\0' 이기 때문에 제외했습니다.
			msgForm.messageLen = SIZE_OF_BUFFER - 1;
			msgForm.messageLeftLength = msg.GetLength() - SIZE_OF_BUFFER + 1;

			::StringCchPrintf(msgForm.message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			int temp = msg.Delete(0, SIZE_OF_BUFFER - 1);

			this->Send(&msgForm, sizeof MessageForm);
		}
	}
}