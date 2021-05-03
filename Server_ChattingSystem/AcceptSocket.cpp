#include "pch.h"
#include "framework.h"

#include "Transmission.h"

#include <Strsafe.h>

CAcceptSocket::CAcceptSocket(Transmission *transmission) {
	AfxMessageBox(_T("AcceptSocket Created with Transmission"));
	this->SetTransmission(transmission);
}
CAcceptSocket::~CAcceptSocket() {
	TRACE("CAcceptSocket Destructor");
	this->Close();
}
void CAcceptSocket::SetTransmission(Transmission* transmission) {
	AfxMessageBox(_T("Set AcceptSocket Transmission"));
	this->transmission = transmission;
}
void CAcceptSocket::OnReceive(int nErrorCode) {
	AfxMessageBox(_T("AcceptSocket OnReceive"));

	this->transmission->Receive();
}
void CAcceptSocket::OnClose(int nErrorCode) {
	AfxMessageBox(_T("AcceptSocket OnClose"));

	this->transmission->Close();
}
