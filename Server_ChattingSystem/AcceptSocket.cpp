#include "pch.h"
#include "framework.h"

#include "Transmission.h"

/*
* Behaviors
*	This belongs to a socketTransmission Module
*	An accept Socket is connected to one client, and Communicate with it
* Reponsibilities
*	Send Message To the connected client.
*	Notify to socketTransmission Module about;
		- Receive a message from the client
		- Closed Connection
*/
// Constructor / Destructor
CAcceptSocket::CAcceptSocket(SocketTransmission *transmission) : m_msg() {
	TRACE(_T("CAcceptSocket Constructor"));
	this->SetTransmission(transmission);
}
CAcceptSocket::~CAcceptSocket() {
	TRACE("CAcceptSocket Destructor");
	this->Close();
}

// Methods
void CAcceptSocket::OnClose(int nErrorCode) {
	TRACE(_T("AcceptSocket OnClose"));
	this->transmission->Close(this->id);
}
void CAcceptSocket::OnReceive(int nErrorCode) {
	TRACE(_T("AcceptSocket OnReceive"));

	this->RecvMsg();
	this->transmission->RecvFrom(this->id, this->m_msg.message);
}
void CAcceptSocket::RecvMsg() {
	MessageForm msgBuffer;

	while (1) {
		int nbytes = this->Receive(&msgBuffer, sizeof MessageForm);

		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			this->SetMsg(msgBuffer);

			// �� ������ Ȯ���� ���ϰ� �־���!
			// �� �������� ���� �����Ͱ� ����� �۵����� �ʰ� �־���
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
			// SIZE_OF_BUFFER-1 �� ������ ���ڴ� '\0' �̱� ������ �����߽��ϴ�.
			msgForm.messageLen = SIZE_OF_BUFFER - 1;

			::StringCchPrintf(msgForm.message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			int temp = msg.Delete(0, SIZE_OF_BUFFER - 1);

			this->Send(&msgForm, sizeof MessageForm);
		}
	}
}

// Getter / Setter
void CAcceptSocket::SetSocketID(UINT id) {
	this->id = id;
}
UINT CAcceptSocket::GetSocketID() {
	return this->id;
}
void CAcceptSocket::SetMsg(MessageForm msg) {
	this->m_msg = msg;
}
MessageForm* CAcceptSocket::GetMsg() {
	return &(this->m_msg);
}
void CAcceptSocket::SetTransmission(SocketTransmission* transmission) {
	TRACE(_T("CAcceptSocket SetTransmission"));
	this->transmission = transmission;
}