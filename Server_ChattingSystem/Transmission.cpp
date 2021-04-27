#include "pch.h"
#include "Transmission.h"

Transmission::Transmission() : listenSocket(), acceptSocket(this) {

}
Transmission::~Transmission() {

}