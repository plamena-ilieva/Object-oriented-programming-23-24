#include "EventCollection.h"

EventCollection EventCollection::eventsOnDate(const BulgarianDate& date) const {
	EventCollection res;

	for (size_t i = 0; i < size; i++) {
		if (compareBulgarianDates(date, events[i].getDate()) == 0) {
			res.addEvent(events[i]);
		}
	}

	return res;
}

int EventCollection::findEventByName(const char* name) const {
	for (size_t i = 0; i < size; i++) {
		if (strcmp(events[i].getName(), name) == 0) {
			return i;
		}
	}

	return -1;
}

bool EventCollection::addEvent(const Event& event) {
	if (size >= MAX_EVENT_SIZE) {
		return false;
	}
	events[size] = event;
	size++;
	return true;
}

EventCollection EventCollection::maxEvents(const BulgarianDate& date) const
{
	EventCollection onSameDate = eventsOnDate(date);

	//implementation -> next seminar
}

bool EventCollection::removeEvent(const char* name) {
	int idx = findEventByName(name);

	if (idx == -1) {
		return false;
	}

	events[idx] = events[size - 1];
	size--;
	return true;
}
void EventCollection::print() const {
	for (size_t i = 0; i < size; i++) {
		std::cout << events[i].getName() << std::endl;
	}
}