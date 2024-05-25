#pragma once
#include "EventListener.h"
#include <ctime>

class TimeEventListener :
    public EventListener
{
    time_t lastTime;
    unsigned secondsToReact;

public:
    TimeEventListener(unsigned seconds);
    // Inherited via EventListener
    const char* check() override;
    EventListener* clone() const override;
};

