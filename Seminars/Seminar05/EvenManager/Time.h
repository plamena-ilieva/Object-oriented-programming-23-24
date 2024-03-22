#pragma once
#include <iostream>
#include <cmath>

class Time {
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    bool isInInterval(unsigned upperBound, unsigned value) const;

    unsigned getUnixFromTime() const;
    void setTimeFromUnix(unsigned seconds);

public:
    Time(unsigned h, unsigned m, unsigned s);
    Time() = default;

    void setHours(unsigned h);
    void setMinutes(unsigned m);
    void setSeconds(unsigned s);

    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;

    void increment();

    int compare(const Time& other) const;

    bool isPartyTime() const;
    bool isDinnerTime() const;

    Time getDiff(const Time& other) const;

    void print() const;
};

