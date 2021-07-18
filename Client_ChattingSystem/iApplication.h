#pragma once

#include <string>

#ifndef __iApplication_H_INCLUDED__
#define __iApplication_H_INCLUDED__
__interface iApplication {
public:
	virtual void Tick();
	virtual void RecvMessage(const std::string& msg);
};
#endif