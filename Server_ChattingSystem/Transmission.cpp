#include "pch.h"

#include "Transmission.h"

#include <Strsafe.h>

SocketTransmission::SocketTransmission() {
    TRACE(_T("Transmission Constructor"));
    this->listenSocket = new CListenSocket(this);
}
SocketTransmission::~SocketTransmission() {
	TRACE("Transmission Destructor");
    delete this->listenSocket;
}

void SocketTransmission::Accept() {
	TRACE(_T("Transmission.cpp Accept"));

    // shared_ptr created
    auto temp = std::shared_ptr<CAcceptSocket>(new CAcceptSocket(this),
        [](CAcceptSocket* socket) {
            TCHAR buf[30];
            wsprintf(buf, _T("Close PortNum: %d\n"), socket->GetSocketID());
            AfxMessageBox(buf);

            delete socket;
        }
    );

    if (!this->listenSocket->Accept(*temp)) {
        AfxMessageBox(_T("Accept Error!"));
        return;
    }
    
    CString PeerAddress;
    UINT PeerPort;
    temp->GetPeerName(PeerAddress, PeerPort);
    temp->SetSocketID(PeerPort);

    this->acceptSocketList.push_back(temp);

    TCHAR buf[30];
#ifdef _DEBUG
    wsprintf(buf, _T("Login from %s/%d\n"), (LPCTSTR)PeerAddress, PeerPort);
    AfxMessageBox(buf);
#endif
    MessageForm msgBuffer;
    
    wsprintf(buf, _T("Hello %d\n"), PeerPort);
    StringCchCopy(msgBuffer.message, SIZE_OF_BUFFER, buf);
    temp->Send(&msgBuffer, sizeof MessageForm);
}
void SocketTransmission::Close(UINT portNum) {
    TRACE(_T("AcceptSocket Close"));

    for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++) {
        if ((*it)->GetSocketID() == portNum) {
            acceptSocketList.erase(it);
            break;
        }
    }
}

void SocketTransmission::SendTo(UINT id, CString msg) {
    TRACE(_T("Transmission Send"));

    for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++)
    {
        if ((*it)->GetSocketID() == id) {
            (*it)->SendMsg(msg);
            break;
        }
    }
}
void SocketTransmission::RecvFrom(UINT id, CString msg) {
    TRACE(_T("Transmission Receive"));

    // Message 그냥 Return 합니다.
    for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++) {
        UINT socketID = (*it)->GetSocketID();
        if (socketID == id) continue;
        this->SendTo(socketID, msg);
    }
#ifdef _DEBUG
    AfxMessageBox(msg1);
#endif
}

// deprecated
// 
//void SocketTransmission::Receive(CString msg) {
//    TRACE(_T("Transmission Receive"));
//	
//    CString msg1 = this->MessageDecoding(msg);
//
//    // Message 그냥 Return 합니다.
//    this->Send(msg1);
//
//#ifdef _DEBUG
//    AfxMessageBox(msg1);
//#endif
//}
//void SocketTransmission::Send(CString msg) {
//    TRACE(_T("Transmission Send"));
//
//    CString msg1 = this->MessageEncoding(msg);
//
//    for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++)
//    {
//        (*it)->SendMsg(msg1);
//    }
//}