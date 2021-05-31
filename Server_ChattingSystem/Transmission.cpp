#include "pch.h"

#include "AMQPTransmission.h"

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
AMQPTransmission::AMQPTransmission(iCoreModule* pCoreModule) {
    this->pCoreModule = pCoreModule;

    
}
AMQPTransmission::~AMQPTransmission() {
    TRACE("Transmission Destructor");
}

void AMQPTransmission::Accept() {
    TRACE(_T("SocketTransmission.cpp Accept"));
}
void AMQPTransmission::Close(UINT socketID) {
    TRACE(_T("AcceptSocket Close"));
}

void AMQPTransmission::SendTo(UINT id, CString msg) {
    TRACE(_T("Transmission Send"));
}
void AMQPTransmission::RecvFrom(UINT id, CString msg) {
    TRACE(_T("Transmission Receive"));
}

