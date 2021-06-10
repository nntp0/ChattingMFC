#pragma once

#include "NNTPlib.h"

class AMQPServer;
class Receiver : public nntp::thread {

public:
	Receiver();
	virtual ~Receiver();

protected:
	virtual bool Job();

private:
	AMQPServer* mainThread = nullptr;

public:
	void SetReceiver(AMQPServer*);
};