#include "pch.h"
#include "framework.h"

#include "Transmission.h"

CClientSocket::CClientSocket(Transmission *transmission) : m_msg(){
	TRACE("CClientSocket Constructor");

	SetTransmission(transmission);

	this->Create();
	this->Connect(_T("127.0.0.1"), 8000);
}

CClientSocket::~CClientSocket() {
	TRACE("CClientSocket Destructor");

	this->Close();
}

void CClientSocket::SetTransmission(Transmission* transmission) {
	TRACE(_T("CClientSocket SetTransmission"));
	this->transmission = transmission;
}

void CClientSocket::OnClose(int nErrorCode) {
	TRACE(_T("CClientSocket OnClose"));
	this->transmission->Close();
}

void CClientSocket::OnReceive(int nErrorCode) {
	TRACE(_T("CClientSocket OnReceive"));
	this->transmission->Receive();
}

void CClientSocket::SetMsg(MessageForm msg) {
	this->m_msg = msg;
}

MessageForm* CClientSocket::GetMsg() {
	return &(this->m_msg);
}