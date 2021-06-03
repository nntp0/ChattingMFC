#pragma once

#include <string>

#define UID unsigned int
struct ConnectionInfo {
	UID uid;
	std::string messageQueueName;
	bool isOpened;

	ConnectionInfo(UID uid, std::string messageQueueName)
		: uid(uid), messageQueueName(messageQueueName), isOpened(true) {}
};