#include "pch.h"

#include "Transmission.h"



Transmission::Transmission() : acceptSocketList() {
	AfxMessageBox(_T("Transmission Constructor"));
	this->listenSocket = new CListenSocket(this);
}
Transmission::~Transmission() {
	TRACE("Hello Destructor!");
	delete this->listenSocket;
}
void Transmission::Accept() {

	AfxMessageBox(_T("Transmission.cpp Accept"));

	/*auto acceptSocket = std::make_shared<CAcceptSocket>();
	if (!this->listenSocket.Accept(*acceptSocket)) {
		AfxMessageBox(_T("Accept Error!"));
		return;
	}*/
}

void Transmission::Close() {

}