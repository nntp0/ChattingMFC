#include "pch.h"
#include "AfxMt.h"
#include "Logger.h"

Logger::Logger() {
	this->logFilePath = ".\\";
	this->logFileName = "text.txt";
}
Logger::~Logger() {}

#include <ctime>
bool Logger::WriteLogToFile(std::string log) {

	FILE* fp = std::fopen((this->logFilePath + this->logFileName).c_str(), "a");

	auto now = std::chrono::system_clock::now();
	auto uS = now.time_since_epoch().count() / 10000;
	auto mS = uS % 1000;


	time_t tnow = time(0);
	tm* ltm = localtime(&tnow);

	fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d.%03lld][CLIENT]", ltm->tm_year + 1900, ltm->tm_mon, ltm->tm_mday,
		ltm->tm_hour, ltm->tm_min, ltm->tm_sec, mS);

	fprintf(fp, "%s", log.c_str());
	std::fclose(fp);
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