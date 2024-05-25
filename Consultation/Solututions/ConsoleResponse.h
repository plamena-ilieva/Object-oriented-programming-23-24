#pragma once
#include "EventResponse.h"
class ConsoleResponse :
    public EventResponse
{
public:
    // Inherited via EventResponse
    void respond(const char* message) const override;
    EventResponse* clone() const override;
};

