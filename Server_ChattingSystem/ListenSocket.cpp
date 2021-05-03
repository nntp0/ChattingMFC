#include "pch.h"
#include "framework.h"

#include "Transmission.h"
//#include "ListenSocket.h"
#include <Strsafe.h>

//CListenSocket::CListenSocket() : m_msg() {
//    AfxMessageBox(_T("ListenSocketCreate"));
//
//    AfxSocketInit();
//
//    this->Create(8000);
//    this->Listen();
//}
CListenSocket::CListenSocket(Transmission *transmission) : m_msg() {
    AfxMessageBox(_T("ListenSocketCreated with Transmission"));
    this->transmission = transmission;

    AfxSocketInit();

    this->Create(8000);
    this->Listen();
}
CListenSocket::~CListenSocket() {
    this->Close();
}
void CListenSocket::Tick() {
    TRACE("Tick");
}

void CListenSocket::SetTransmission(Transmission* transmission) {
    AfxMessageBox(_T("ListenSocket SetTransmission Called"));
    this->transmission = transmission;
}
void CListenSocket::OnAccept(int nErrorCode) {
    transmission->Accept();
}

void CListenSocket::SetMsg(MessageForm msg) {
    this->m_msg = msg;
}
MessageForm CListenSocket::GetMsg() {
    return this->m_msg;
}