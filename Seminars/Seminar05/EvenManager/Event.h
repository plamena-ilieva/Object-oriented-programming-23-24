#pragma once
#include "BulgarianDate.h"
#include "Time.h"

class Event {
private:
	char name[21] = "";
	BulgarianDate date;
	Time begin;
	Time end;

	void validateTimes();
	void setName(const char* name);
public:
	Event() = default;

	Event(const char* name, const BulgarianDate& date, const Time& beg, const Time& end);

	Event(
		const char* name,
		unsigned day, unsigned month, unsigned year,
		size_t begHours, size_t begMins, size_t begSeconds,
		size_t endHours, size_t endMins, size_t endSeconds);

	const char* getName() const;
	const BulgarianDate& getDate() const;
	const Time& getBegin() const;
	const Time& getEnd() const;
};
