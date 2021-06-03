#pragma once

#include <string>

__interface iApplication {
public:
	virtual void Tick();
	virtual void RecvMessage(std::string msg);
};