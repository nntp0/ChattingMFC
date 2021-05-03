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
	AfxMessageBox(_T("Close"));
	this->Close();
}