#include "Event.h"
#pragma warning (disable : 4996)

Event::Event(const char* name, const BulgarianDate& date, const Time& beg, const Time& end)
    : date(date), begin(beg), end(end)
{
    //validations!!!
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
    //validations!!!
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