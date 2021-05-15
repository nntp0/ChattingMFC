#include "pch.h"

#include "Transmission.h"

/*
* Behaviors
*   This requires a Moderator (what I named CoreModule)
*   Transmission Module creates a client Socket and wait for a client to connect
* 
* Reponsibilities
*   Transmission Module is responsible to establishing connection between the server and a client.
*   Transmission Module manages SocketList (Real Connections)
*   Transmission Module owns a listenSocket and multiple acceptSockets, each socket is connected with a client.
*/
SocketTransmission::SocketTransmission(iCoreModule* pCoreModule) {
    this->pCoreModule = pCoreModule;
    
    this->listenSocket = new CListenSocket(this);
}
SocketTransmission::~SocketTransmission() {
	TRACE("Transmission Destructor");
    delete this->listenSocket;
}

void SocketTransmission::Accept() {
	TRACE(_T("Transmission.cpp Accept"));

    // shared_ptr created & set Custom deleter
    // *CAUTION*
    //  inefficiency: the custom deleter does nothing; useless.
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

    std::shared_ptr<Info_ClientConnection> eventData{ new Info_ClientConnection {PeerPort},
        [](Info_ClientConnection* eventData) {
            AfxMessageBox(_T("Discarded"));
            delete eventData;
        }
    };
    this->pCoreModule->EventController(EventList::ClientConnection, &eventData);
}
void SocketTransmission::Close(UINT socketID) {
    TRACE(_T("AcceptSocket Close"));

    for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++) {
        if ((*it)->GetSocketID() == socketID) {
            acceptSocketList.erase(it);

            std::shared_ptr<Info_ClientDisconnection> eventData{ new Info_ClientDisconnection {socketID},
                [](Info_ClientDisconnection* eventData) {
                    AfxMessageBox(_T("Discarded2"));
                    delete eventData;
                }
            };
            this->pCoreModule->EventController(EventList::ClientDisconnection, &eventData);
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

    std::shared_ptr<Info_ReceiveMessage> eventData{ new Info_ReceiveMessage {id, msg},
        [](Info_ReceiveMessage* eventData) {
            AfxMessageBox(_T("Discarded3"));
            delete eventData;
        }
    };
    this->pCoreModule->EventController(EventList::ReceiveMessage, &eventData);

    // Message 그냥 Return 합니다.
    /*for (auto it = this->acceptSocketList.begin(); it != this->acceptSocketList.end(); it++) {
        UINT socketID = (*it)->GetSocketID();
        if (socketID == id) continue;
        this->SendTo(socketID, msg);
    }*/
#ifdef _DEBUG
    AfxMessageBox(msg1);
#endif
}

// deprecated

/*void sockettransmission::receive(cstring msg) {
    trace(_t("transmission receive"));
	
    cstring msg1 = this->messagedecoding(msg);

    // message 그냥 return 합니다.
    this->send(msg1);

#ifdef _debug
    afxmessagebox(msg1);
#endif
}
void sockettransmission::send(cstring msg) {
    trace(_t("transmission send"));

    cstring msg1 = this->messageencoding(msg);

    for (auto it = this->acceptsocketlist.begin(); it != this->acceptsocketlist.end(); it++)
    {
        (*it)->sendmsg(msg1);
    }
}
sockettransmission::sockettransmission() {
    trace(_t("transmission constructor"));
    this->listensocket = new clistensocket(this);
}*/