#pragma once

#include "NNTPlib.h"
#include "iDisplayModule.h"
#include <vector>
#include <queue>
#include <string>

class Logger : public nntp::thread, public iDisplayModule {
public:
	Logger();
	virtual ~Logger();

protected:
	virtual bool Job();


public:
	virtual void WriteLog(std::string);
	virtual void DisplayLog(CString msg);


private:
	std::string logFilePath;
	std::string logFileName;

	std::mutex ticket;
	std::queue<std::string> logList;

	// helper method
private:
	bool WriteLogToFile(std::string);
};