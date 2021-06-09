#pragma once

#include "NNTPlib.h"
#include <queue>
#include <string>

#include "ChildView.h"
#include "AMQPClient.h"

class Processor : public nntp::thread
{
public:
	Processor();
	virtual ~Processor();

	void SetModules(iTransmission*, CChildView*);

protected:
	virtual bool Job();

public:
	void RegisterEvent(std::string);

	// helper method
private:
	void MessageToServer(std::string);
	void MessageFromServer(std::string);

private:
	std::queue<std::string> messageList;
	std::mutex messageListLock;

	iTransmission* transmission;
	CChildView* display;
};