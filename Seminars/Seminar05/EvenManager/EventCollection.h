#pragma once
#include "Event.h"

constexpr int MAX_EVENT_SIZE = 30;

class EventCollection
{
	Event events[MAX_EVENT_SIZE];
	size_t size = 0;

	EventCollection eventsOnDate(const BulgarianDate& date) const;
	int findEventByName(const char* name) const;

public:
	bool addEvent(const Event& event);
	EventCollection maxEvents(const BulgarianDate& date) const;
	bool removeEvent(const char* name);

	void print() const;
};

