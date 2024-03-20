#include <iostream>
#include <cmath>

class Time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

    bool isInInterval(unsigned upperBound, unsigned value) const {
        return value <= upperBound;
    }

    unsigned getUnixFromTime() const {
        return 3600 * hours + 60 * minutes + seconds;
    }

    void setTimeFromUnix(unsigned seconds) {
        setSeconds(seconds % 60);
        seconds /= 60;
        setMinutes(seconds % 60);
        seconds /= 60;
        setHours(seconds % 24);
    }

public:
    Time(unsigned h, unsigned m, unsigned s) {
        setHours(h);
        setMinutes(m);
        setSeconds(s);
    }
    Time() : Time(0, 0, 0) {}

    void setHours(unsigned h) {
        if (isInInterval(23, h)) {
            hours = h;
        }
    }

    void setMinutes(unsigned m) {
        if (isInInterval(59, m)) {
            minutes = m;
        }
    }

    void setSeconds(unsigned s) {
        if (isInInterval(59, s)) {
            seconds = s;
        }
    }

    unsigned getHours() const {
        return hours;
    }

    unsigned getMinutes() const {
        return minutes;
    }

    unsigned getSeconds() const {
        return seconds;
    }

    void increment() {
        unsigned unixSec = getUnixFromTime();
        unixSec++;
        setTimeFromUnix(unixSec);
    }

    int compare(const Time& other) const {
        unsigned unix = getUnixFromTime();
        unsigned otherUnix = other.getUnixFromTime();

        if (unix == otherUnix) {
            return 0;
        }

        return unix < otherUnix ? -1 : 1;
    }

    bool isPartyTime() const {
        Time begin(23, 0, 0);
        Time end(6, 0, 0);

        return compare(begin) > 0 || compare(end) < 0;
    }

    bool isDinnerTime() const {
        Time begin(20, 30, 0);
        Time end(22, 0, 0);

        return compare(begin) > 0 && compare(end) < 0;
    }

    Time getDiff(const Time& other) const {
        unsigned resUnix = fabs(getUnixFromTime() - other.getUnixFromTime());
        Time t;
        t.setTimeFromUnix(resUnix);

        return t;
    }

    void print() const {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
};

int main()
{
    Time t(23, 59, 57);

    t.increment();
    t.increment();
    t.increment();

    t.print();
}
