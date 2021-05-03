#include "pch.h"

#include "Transmission.h"
#include "ListenSocket.h"
#include "AcceptSocket.h"


Transmission::Transmission() {

}
Transmission::~Transmission() {

}
void Transmission::Accept() {

	AfxMessageBox(_T("Transmission.cpp Accept"));

	/*auto acceptSocket = std::make_shared<CAcceptSocket>();
	if (!this->listenSocket.Accept(*acceptSocket)) {
		AfxMessageBox(_T("Accept Error!"));
		return;
	}*/
}