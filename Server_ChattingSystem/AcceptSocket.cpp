#include "pch.h"
#include "framework.h"

#include "Transmission.h"
//#include "AcceptSocket.h"
#include <Strsafe.h>

CAcceptSocket::CAcceptSocket() : transmission() {
	AfxMessageBox(_T("AcceptSocket Created"));
}
CAcceptSocket::CAcceptSocket(Transmission *transmission) {
	AfxMessageBox(_T("AcceptSocket Created with Transmission"));
	this->SetTransmission(transmission);
}
CAcceptSocket::~CAcceptSocket() {
	AfxMessageBox(_T("AcceptSocket Closed"));
	this->Close();
}
void CAcceptSocket::SetTransmission(Transmission* transmission) {
	AfxMessageBox(_T("It's a terrible Day"));
	this->transmission = transmission;
}

void CAcceptSocket::OnReceive(int nErrorCode) {
	AfxMessageBox(_T("You Got Something"));

	this->transmission->Receive();
}
void CAcceptSocket::OnClose(int nErrorCode) {
	AfxMessageBox(_T("AcceptSocket Closed"));
	this->transmission->Close();
	this->Close();
}
