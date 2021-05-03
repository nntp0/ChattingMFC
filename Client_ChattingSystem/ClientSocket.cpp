#include "pch.h"
#include "framework.h"

#include "ClientSocket.h"

CClientSocket::CClientSocket() {
	TRACE("CClientSocket Constructor");
}

CClientSocket::~CClientSocket() {
	TRACE("CClientSocket Destructor");
}

void CClientSocket::OnClose(int nErrorCode) {
	AfxMessageBox(_T("CClientSocket OnClose"));
	this->Close();
}

void CClientSocket::OnReceive(int nErrorCode) {
	AfxMessageBox(_T("CClientSocket OnReceive"));

	
}