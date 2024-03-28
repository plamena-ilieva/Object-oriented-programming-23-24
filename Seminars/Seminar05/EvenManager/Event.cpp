#include "Event.h"
#pragma warning (disable : 4996)

void Event::validateTimes() {
    if (begin.compare(end) == 1)
        std::swap(begin, end);
}

Event::Event(const char* name, const BulgarianDate& date, const Time& beg, const Time& end)
    : date(date), begin(beg), end(end)
{
    setName(name);
    validateTimes();
}

Event::Event(
    const char* name,
    unsigned day, unsigned month, unsigned year,
    size_t begHours, size_t begMins, size_t begSeconds,
    size_t endHours, size_t endMins, size_t endSeconds)
    : date(day, month, year), 
    begin(begHours, begMins, begSeconds), 
    end(endHours, endMins, endSeconds)
{
    setName(name);
    validateTimes();
}

const char* Event::getName() const {
    return name;
}

const BulgarianDate& Event::getDate() const {
    return date;
}

const Time& Event::getBegin() const {
    return begin;
}

const Time& Event::getEnd() const {
    return end;
}

void Event::setName(const char* argName) {
    if (strlen(argName) > 20)
        return;

    strcpy(name, argName);
}