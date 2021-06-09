#pragma once

#include "NNTPlib.h"
#include <queue>
#include <string>

class Processor : public nntp::thread
{
public:
	Processor();
	virtual ~Processor();

protected:
	virtual bool Job();

public:
	void RegisterEvent(std::string);

private:
	std::queue<std::string> messageList;
	std::mutex messageListLock;
};