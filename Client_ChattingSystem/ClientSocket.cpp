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

	MessageForm msgBuffer;

	while (1) {
		int nbytes = this->Receive(&msgBuffer, sizeof MessageForm);
		
#ifdef _DEBUG
		wsprintf(buf, _T("%d\n"), nbytes);
		AfxMessageBox(buf);
#endif
		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			TRACE(_T("OK!"));

			this->SetMsg(msgBuffer);
			AfxMessageBox(this->GetMsg()->message);

			// �� ������ Ȯ���� ���ϰ� �־���!
			// �� �������� ���� �����Ͱ� ����� �۵����� �ʰ� �־���
			if (msgBuffer.messageLen != SIZE_OF_BUFFER) break;
		}
	}
}
void CClientSocket::SendMsg(CString msg) {
	AfxMessageBox(_T("CClientSocket SendMessage"));
	
	MessageForm* pMsgForm = new MessageForm;
	while (1) {
		if (msg.GetLength() < SIZE_OF_BUFFER) {
			pMsgForm->messageLen = msg.GetLength();

			TCHAR buf[SIZE_OF_BUFFER];
			wsprintf(buf, _T("%d"), pMsgForm->messageLen);
			AfxMessageBox(buf);

			::StringCchPrintf(pMsgForm->message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			AfxMessageBox(pMsgForm->message);

			this->Send(pMsgForm, sizeof MessageForm);
			break;
		}
		else {
			// SIZE_OF_BUFFER-1 �� ������ ���ڴ� '\0' �̱� ������ �����߽��ϴ�.
			pMsgForm->messageLen = SIZE_OF_BUFFER - 1;

			::StringCchPrintf(pMsgForm->message, SIZE_OF_BUFFER, _T("%s"), msg.GetString());
			int temp = msg.Delete(0, SIZE_OF_BUFFER - 1);

			TCHAR buf[20];
			wsprintf(buf, _T("%d"), temp);
			AfxMessageBox(buf);
			this->Send(pMsgForm, sizeof MessageForm);
		}
	}
	delete pMsgForm;
}