#pragma once

#include <string>

#define UID std::string
struct ConnectionInfo {
	UID uid;
	std::string messageQueueName;
	bool isOpened;

	ConnectionInfo(UID uid, std::string messageQueueName)
		: uid(uid), messageQueueName(messageQueueName), isOpened(true) {}
};