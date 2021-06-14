#pragma once
#include <afxstr.h>
#include <string>

#ifndef __iDisplayModule_H_INCLUDED__
#define __iDisplayModule_H_INCLUDED__
__interface iDisplayModule {

public:
	virtual void DisplayLog(CString msg);
	virtual void WriteLog(std::string);
};
#endif