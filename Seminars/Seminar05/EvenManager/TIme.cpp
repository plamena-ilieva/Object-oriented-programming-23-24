#include <iostream>
#include <cmath>
#include "Time.h"

bool Time::isInInterval(unsigned upperBound, unsigned value) const {
    return value <= upperBound;
}

unsigned Time::getUnixFromTime() const {
    return 3600 * hours + 60 * minutes + seconds;
}

void Time::setTimeFromUnix(unsigned seconds) {
    setSeconds(seconds % 60);
    seconds /= 60;
    setMinutes(seconds % 60);
    seconds /= 60;
    setHours(seconds % 24);
}

Time::Time(unsigned h, unsigned m, unsigned s) {
    setHours(h);
    setMinutes(m);
    setSeconds(s);
}

void Time::setHours(unsigned h) {
    if (isInInterval(23, h)) {
        hours = h;
    }
}

void Time::setMinutes(unsigned m) {
    if (isInInterval(59, m)) {
        minutes = m;
    }
}

void Time::setSeconds(unsigned s) {
    if (isInInterval(59, s)) {
        seconds = s;
    }
}

unsigned Time::getHours() const {
    return hours;
}

unsigned Time::getMinutes() const {
    return minutes;
}

unsigned Time::getSeconds() const {
    return seconds;
}

void Time::increment() {
    unsigned unixSec = getUnixFromTime();
    unixSec++;
    setTimeFromUnix(unixSec);
}

int Time::compare(const Time& other) const {
    unsigned unix = getUnixFromTime();
    unsigned otherUnix = other.getUnixFromTime();

    if (unix == otherUnix) {
        return 0;
    }

    return unix < otherUnix ? -1 : 1;
}

bool Time::isPartyTime() const {
    Time begin(23, 0, 0);
    Time end(6, 0, 0);

    return compare(begin) > 0 || compare(end) < 0;
}

bool Time::isDinnerTime() const {
    Time begin(20, 30, 0);
    Time end(22, 0, 0);

    return compare(begin) > 0 && compare(end) < 0;
}

Time Time::getDiff(const Time& other) const {
    unsigned resUnix = fabs(getUnixFromTime() - other.getUnixFromTime());
    Time t;
    t.setTimeFromUnix(resUnix);

    return t;
}

void Time::print() const {
    std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
}