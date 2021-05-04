#include "pch.h"
#include "framework.h"

#include "Transmission.h"

#include <Strsafe.h>

CListenSocket::CListenSocket(Transmission *transmission) {
    AfxMessageBox(_T("ListenSocket Created with Transmission"));
    
    this->SetTransmission(transmission);

    AfxSocketInit();

    this->Create(8000);
    this->Listen();
}
CListenSocket::~CListenSocket() {
    TRACE("CListenSocket Destructor");
    this->Close();
}
void CListenSocket::SetTransmission(Transmission* transmission) {
    AfxMessageBox(_T("ListenSocket SetTransmission"));
    this->transmission = transmission;
}
void CListenSocket::OnAccept(int nErrorCode) {
    transmission->Accept();
}
