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
	if (size >= 30) {
		return false;
	}
	events[size] = event;
	size++;
	return true;
}

EventCollection EventCollection::maxEvents(const BulgarianDate& date) const
{
	EventCollection sameDateBuffer = eventsOnDate(date);

	for (size_t i = 0; i < size - 1; i++) {
		size_t currMinIndex = i;

		for (size_t j = i + 1; j < size; j++) {
			if (sameDateBuffer.events[currMinIndex].getEnd()
				.compare(sameDateBuffer.events[j].getEnd()) == 1) {
				currMinIndex = j;
			}
		}

		if (currMinIndex != i) {
			std::swap(sameDateBuffer.events[currMinIndex], sameDateBuffer.events[i]);
		}
	}

	EventCollection toReturn;
	toReturn.addEvent(sameDateBuffer.events[0]);

	for (size_t i = 1; i < sameDateBuffer.size; i++) {
		if (sameDateBuffer.events[i].getBegin().compare(sameDateBuffer.events[toReturn.size - 1].getEnd()) >= 0) {
			toReturn.addEvent(sameDateBuffer.events[i]);
		}
	}

	return toReturn;
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