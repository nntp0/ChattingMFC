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
}
void CAcceptSocket::SetTransmission(Transmission* transmission) {
	AfxMessageBox(_T("It's a terrible Day"));
	this->transmission = transmission;
}

