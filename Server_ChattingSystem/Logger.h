#pragma once

#include "NNTPlib.h"
#include <vector>
#include <queue>
#include <string>

class Logger : public nntp::thread {
public:
	Logger();
	virtual ~Logger();

protected:
	virtual bool Job();


public:
	void WriteLog(std::string);


private:
	std::string logFilePath;
	std::string logFileName;

	std::mutex ticket;
	std::queue<std::string> logList;

	// helper method
private:
	bool WriteLogToFile(std::string);
};