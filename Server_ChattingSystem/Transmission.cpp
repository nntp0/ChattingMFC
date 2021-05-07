#include "pch.h"

#include "Transmission.h"

#include <Strsafe.h>

SocketTransmission::SocketTransmission() : acceptSocket() {
    TRACE(_T("Transmission Constructor"));
    this->listenSocket = new CListenSocket(this);
}
SocketTransmission::~SocketTransmission() {
	TRACE("Transmission Destructor");

    this->listenSocket->Close();
    delete this->listenSocket;

    if (this->acceptSocket != nullptr) {
        this->acceptSocket->Close();
        delete this->acceptSocket;
    }
}
void SocketTransmission::Accept() {

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

    this->acceptSocket->SetSocketID(PeerPort);
#ifdef _DEBUG
    TCHAR buf[SIZE_OF_BUFFER];
    wsprintf(buf, _T("Login from %s/%d\n"), (LPCTSTR)PeerAddress, PeerPort);
    AfxMessageBox(buf);
#endif

    MessageForm msgBuffer;
    
    StringCchCopy(msgBuffer.message, SIZE_OF_BUFFER, _T("Hello World"));
    this->acceptSocket->Send(&msgBuffer, sizeof MessageForm);
}

void SocketTransmission::Close(UINT portNum) {
    AfxMessageBox(_T("AcceptSocket Close"));
    
    TCHAR buf[SIZE_OF_BUFFER];
    wsprintf(buf, _T("Close PortNum: %d\n"), portNum);
    AfxMessageBox(buf);

    acceptSocket->Close();
    acceptSocket = nullptr;
}
void SocketTransmission::Receive(CString msg) {
    AfxMessageBox(_T("Transmission Receive"));
	
    CString msg1 = this->MessageDecoding(msg);
    //this->mainFrame->ControlMessage(msg1);
    AfxMessageBox(msg1);
}
void SocketTransmission::Send(CString msg) {
    TRACE(_T("Transmission Send"));

    CString msg1 = this->MessageEncoding(msg);
    this->acceptSocket->SendMsg(msg1);
}
CString SocketTransmission::MessageEncoding(CString msg) {
    TRACE(_T("SocketTransmssion MessageEncoding"));
    return msg;
}
CString SocketTransmission::MessageDecoding(CString msg) {
    TRACE(_T("SocketTransmssion MessageDecoding"));
    return msg;
}