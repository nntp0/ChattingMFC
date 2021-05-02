#include "pch.h"
#include "framework.h"

#ifndef __Transmission_H_INCLUDED__
#define __Transmission_H_INCLUDED__
#include "Transmission.h"
#endif
#ifndef __AcceptSocket_H_INCLUDED__
#define __AcceptSocket_H_INCLUDED__
#include "AcceptSocket.h"
#endif
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

