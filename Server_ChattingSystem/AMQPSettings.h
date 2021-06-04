#pragma once

#include <string>

#ifndef __AMQPSettings_H_INCLUDED__
#define __AMQPSettings_H_INCLUDED__
#define UID std::string
struct ConnectionInfo {
	UID uid;
	std::string messageQueueName;
	bool isOpened;

	ConnectionInfo(UID uid, std::string messageQueueName)
		: uid(uid), messageQueueName(messageQueueName), isOpened(true) {}
};
#endif