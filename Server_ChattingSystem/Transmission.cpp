#include "pch.h"

#include "Transmission.h"

#include <Strsafe.h>

Transmission::Transmission() : acceptSocket() {
    AfxMessageBox(_T("Transmission Constructor"));
    this->listenSocket = new CListenSocket(this);
}

Transmission::~Transmission() {
	TRACE("Hello Destructor!");
    this->listenSocket->Close();
    delete this->listenSocket;
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

    MessageForm msgBuffer;
    
    StringCchCopy(msgBuffer.message, SIZE_OF_BUFFER, _T("Hello World"));
    this->acceptSocket->Send(&msgBuffer, sizeof MessageForm);
}

void Transmission::Close() {
    AfxMessageBox(_T("AcceptSocket Close"));

    this->acceptSocket->Close();
    delete this->acceptSocket;
}

void Transmission::Receive() {
    AfxMessageBox(_T("Transmission Receive"));
	TCHAR buf[SIZE_OF_BUFFER];

	TCHAR msgBuffer[sizeof MessageForm];
	int nbytes;

	MessageForm* pMsgBuffer = new MessageForm;

	while (1) {
		nbytes = this->acceptSocket->Receive(msgBuffer, sizeof MessageForm);
		wsprintf(buf, _T("%d\n"), nbytes);

		AfxMessageBox(buf);
		if (nbytes == 0 || nbytes == SOCKET_ERROR) {
			AfxMessageBox(_T("Error!"));
			break;
		}
		else {
			AfxMessageBox(_T("OK!"));

			::CopyMemory(pMsgBuffer, msgBuffer, sizeof MessageForm);

			wsprintf(buf, _T("%d\n"), pMsgBuffer->messageLen);
			AfxMessageBox(buf);

			this->acceptSocket->SetMsg(*pMsgBuffer);
			AfxMessageBox(this->acceptSocket->GetMsg()->message);

			wsprintf(buf, _T("%d\n"), this->acceptSocket->GetMsg()->messageLen);
			AfxMessageBox(buf);

			// 이 구문을 확인을 못하고 있었다!
			// 이 구문으로 인해 데이터가 제대로 작동하지 않고 있었음
			if (pMsgBuffer->messageLen != SIZE_OF_BUFFER) break;
		}
	}

	delete pMsgBuffer;
}