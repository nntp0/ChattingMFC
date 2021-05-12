#pragma once

#include "EventSettings.h"

__interface iCoreModule {
public:
	virtual void EventController(EventList, void*);
};