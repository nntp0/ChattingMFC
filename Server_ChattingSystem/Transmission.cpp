#include "pch.h"

#include "Transmission.h"

#include <Strsafe.h>

Transmission::Transmission() : acceptSocket() {
    AfxMessageBox(_T("Transmission Constructor"));
    this->listenSocket = new CListenSocket(this);
}

Transmission::~Transmission() {
	TRACE("Hello Destructor!");
}
void Transmission::Accept() {

	AfxMessageBox(_T("Transmission.cpp Accept"));

	/*auto acceptSocket = std::make_shared<CAcceptSocket>();
	if (!this->listenSocket.Accept(*acceptSocket)) {
		AfxMessageBox(_T("Accept Error!"));
		return;
	}*/

    this->acceptSocket = new CAcceptSocket(this);
    if (!this->listenSocket->Accept(*this->acceptSocket)) {
        AfxMessageBox(_T("Accept Error!"));
        return;
    }

    CString PeerAddress;
    UINT PeerPort;
    this->acceptSocket->GetPeerName(PeerAddress, PeerPort);

    TCHAR buf[SIZE_OF_BUFFER];
    wsprintf(buf, _T("Login from %s/%d\n"), (LPCTSTR)PeerAddress, PeerPort);
    AfxMessageBox(buf);

    this->acceptSocket->Send("Hello Client", 100);
}

void Transmission::Close() {
    AfxMessageBox(_T("AcceptSocket Close"));

    this->acceptSocket->Close();
    this->listenSocket->Close();
    delete this->listenSocket;
    delete this->acceptSocket;
}

void Transmission::Receive() {
    AfxMessageBox(_T("Received Message"));
    TCHAR buf[SIZE_OF_BUFFER];

    TCHAR msgBuffer[sizeof MessageForm];
    int nbytes;
    while (1) {
        nbytes = this->acceptSocket->Receive(msgBuffer, sizeof MessageForm);
        wsprintf(buf, _T("%d\n"), nbytes);

        AfxMessageBox(buf);
        if (nbytes == 0 || nbytes == SOCKET_ERROR) {
            break;
        }
        else {
            MessageForm* pMsgBuffer = new MessageForm;


            ::CopyMemory(pMsgBuffer, msgBuffer, sizeof MessageForm);
            if (pMsgBuffer->messageLen != SIZE_OF_BUFFER) break;

            this->listenSocket->SetMsg(*pMsgBuffer);
            //::StringCchPrintf(m_msg.message, SIZE_OF_BUFFER, pMsgBuffer->message);
            wsprintf(buf, _T("%s"), this->listenSocket->GetMsg().message);
            AfxMessageBox(buf);

            delete pMsgBuffer;
        }
    }
}