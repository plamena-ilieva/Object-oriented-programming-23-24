#pragma once
#include "Event.h"

class EventCollection
{
	Event events[30];
	size_t size = 0;

	EventCollection eventsOnDate(const BulgarianDate& date) const;
	int findEventByName(const char* name) const;
	void reverse();
public:
	bool addEvent(const Event& event);
	EventCollection maxEvents(const BulgarianDate& date) const;
	bool removeEvent(const char* name);

	void print() const;
};

