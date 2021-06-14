#include "pch.h"
#include "AfxMt.h"
#include "Logger.h"
#include <direct.h>


Logger::Logger() {

	char curDir[1000];
	char* error = _getcwd(curDir, 1000);

	if (error == nullptr) {
		this->logFilePath = std::string("C:\\");
		AfxMessageBox(_T("Log Path Error"));
	}
	else {
		this->logFilePath = std::string(curDir);
	}
	this->logFileName = "text.txt";
}
Logger::~Logger() {}

#include <ctime>
bool Logger::WriteLogToFile(std::string log) {
	FILE* filepoint;

	std::string logPath = this->logFilePath + "\\" + this->logFileName;

	if (fopen_s(&filepoint, logPath.c_str(), "a") == 0) {

		auto now = std::chrono::system_clock::now();
		auto uS = now.time_since_epoch().count() / 10000;
		auto mS = uS % 1000;

		time_t tnow = time(0);
		tm ltm;
		localtime_s(&ltm, &tnow);
		
		fprintf(filepoint, "[%d-%02d-%02d %02d:%02d:%02d.%03lld] ", ltm.tm_year + 1900, ltm.tm_mon, ltm.tm_mday,
			ltm.tm_hour, ltm.tm_min, ltm.tm_sec, mS);
		fprintf(filepoint, "%s\n", log.c_str());

		fclose(filepoint);
	}

	return true;
}
void Logger::WriteLog(std::string log)
{
	ticket.lock();
	logList.push(log);
	ticket.unlock();
	YouHaveWork();
}
bool Logger::Job()
{
	if (logList.empty()) return false;

	ticket.lock();
	std::string log = logList.front();
	WriteLogToFile(log);
	logList.pop();
	ticket.unlock();

	return true;
}

void Logger::DisplayLog(CString msg) {

}