#include "pch.h"
#include "framework.h"

#include "Transmission.h"

/*
* Behaviors
*   This belongs to a socketTransmission Module
*   a listen socket is globally opened.
*   It works as a receptionist.
* Reponsibilities
*   a client connects to this Server, notify to server the information.
*/
CListenSocket::CListenSocket(SocketTransmission *transmission) {
    TRACE(_T("ListenSocket Created with Transmission"));
    
    this->SetTransmission(transmission);

    AfxSocketInit();

    this->Create(8000);
    this->Listen();
}
CListenSocket::~CListenSocket() {
    TRACE("CListenSocket Destructor");
    this->Close();
}
void CListenSocket::SetTransmission(SocketTransmission* transmission) {
    TRACE(_T("ListenSocket SetTransmission"));
    this->transmission = transmission;
}
void CListenSocket::OnAccept(int nErrorCode) {
    transmission->Accept();
}