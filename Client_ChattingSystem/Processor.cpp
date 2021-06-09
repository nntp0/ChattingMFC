#include "pch.h"

#include "Processor.h"

Processor::Processor() {}
Processor::~Processor() {}

bool Processor::Job() {
	

	messageListLock.lock(); 
	
	std::string msg(messageList.front());
	messageList.pop();

	messageListLock.unlock();
	
	AfxMessageBox(CString(msg.c_str()));
	return true;
}

void Processor::RegisterEvent(std::string msg) {

	messageListLock.lock();
	messageList.push(msg);
	messageListLock.unlock();

	YouHaveWork();
}