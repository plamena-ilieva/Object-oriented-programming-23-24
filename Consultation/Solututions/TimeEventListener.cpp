#include "TimeEventListener.h"
#include <stdio.h>
#pragma warning(disable:4996)
TimeEventListener::TimeEventListener(unsigned seconds) :
    lastTime(time(NULL)),
    secondsToReact(seconds) {}

// Allocate memory please delete.
const char* TimeEventListener::check()
{
    time_t now = time(NULL);

    if (difftime(now, lastTime) >= secondsToReact)
    {
        char* message = new char[64] {};
        sprintf(message, "%d seconds have passed.", secondsToReact);
        lastTime = now;
        return message;
    }

    return nullptr;
}

EventListener* TimeEventListener::clone() const
{
    return new TimeEventListener(*this);
}
