#include "pch.h"

#include "Transmission.h"



Transmission::Transmission() : listenSocket(this), acceptSocketList(){

}
Transmission::~Transmission() {

}
void Transmission::Accept() {
	auto acceptSocket = std::make_shared<CAcceptSocket>();
	if (!this->listenSocket.Accept(*acceptSocket)) {
		AfxMessageBox(_T("Accept Error!"));
		return;
	}
}