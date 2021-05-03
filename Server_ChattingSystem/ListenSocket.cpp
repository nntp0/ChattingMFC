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
void CListenSocket::SetTransmission(Transmission* transmission) {
    AfxMessageBox(_T("ListenSocket SetTransmission Called"));
    this->transmission = transmission;
}
void CListenSocket::OnAccept(int nErrorCode) {
    CSocket serverAcceptSocket;
    if (!this->Accept(serverAcceptSocket)) {
        AfxMessageBox(_T("Accept Error!"));
        return;
    }

    CString PeerAddress;
    UINT PeerPort;
    serverAcceptSocket.GetPeerName(PeerAddress, PeerPort);

    TCHAR buf[SIZE_OF_BUFFER];
    wsprintf(buf, _T("Login from %s/%d\n"), (LPCTSTR)PeerAddress, PeerPort);
    AfxMessageBox(buf);

    TCHAR msgBuffer[sizeof MessageForm];
    int nbytes;
    while (1) {
        nbytes = serverAcceptSocket.Receive(msgBuffer, sizeof MessageForm);
        wsprintf(buf, _T("%d\n"), nbytes);

        AfxMessageBox(buf);
        if (nbytes == 0 || nbytes == SOCKET_ERROR) {
            break;
        }
        else {
            MessageForm* pMsgBuffer = new MessageForm;
            ::CopyMemory(pMsgBuffer, msgBuffer, sizeof MessageForm);

            m_msg.messageLen = pMsgBuffer->messageLen;
            ::StringCchPrintf(m_msg.message, SIZE_OF_BUFFER, pMsgBuffer->message);
            wsprintf(buf, _T("%s"), m_msg.message);
            AfxMessageBox(buf);

            delete pMsgBuffer;
        }
    }
    serverAcceptSocket.Close();
    _tprintf(_T("### 접속 종료 ###\n\n"));
}
