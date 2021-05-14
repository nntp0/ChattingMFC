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
	this->transmission->Receive(this->m_msg.message);
}

// Setter / Getter
// ������ �ܼ� ����������, ���Ŀ� � msg ���� ���������� �α׸� ����� �Լ��� ������ ����
void CClientSocket::SetMsg(MessageForm msg) {
	this->m_msg = msg;
}
MessageForm* CClientSocket::GetMsg() {
	return &(this->m_msg);
}

void CClientSocket::RecvMsg() {
	MessageForm msgBuffer;

	while (1) {
		int nbytes = this->Receive(&msgBuffer, sizeof MessageForm);
//#ifdef _DEBUG
//		TCHAR buf[10];
//		wsprintf(buf, _T("%d\n"), nbytes);
//		AfxMessageBox(buf);
//#endif
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
void CClientSocket::SendMsg(CString msg) {
	TRACE(_T("CClientSocket SendMessage"));
	
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