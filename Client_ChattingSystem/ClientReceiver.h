#pragma once

#include "NNTPlib.h"

class AMQPClient;
class Receiver : public nntp::thread {

public:
	Receiver();
	virtual ~Receiver();

protected:
	virtual bool Job();

private:
	AMQPClient* mainThread = nullptr;

public:
	void SetReceiver(AMQPClient*);
};