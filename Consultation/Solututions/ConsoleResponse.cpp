#include "ConsoleResponse.h"
#include <iostream>

void ConsoleResponse::respond(const char* message) const
{
    std::cout << message << std::endl;
}

EventResponse* ConsoleResponse::clone() const
{
    return new ConsoleResponse(*this);
}
