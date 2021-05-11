#include "pch.h"
#include "framework.h"

#include "Transmission.h"

#include <Strsafe.h>

/*
* CListenSocket Constructor
*   
*   Transmission uses a listen socket, which is responsible to
*   wait for a connection creation request.
* 
*   Input: SocketTransmission*, a Controller of this socket
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
