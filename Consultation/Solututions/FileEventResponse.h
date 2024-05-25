#pragma once
#include "EventResponse.h"
#include "FilePath.h"

class FileEventResponse :
    public EventResponse
{
private:
    FilePath path;
public:
    FileEventResponse(const char* filePath);
    // Inherited via EventResponse
    void respond(const char* message) const override;
    EventResponse* clone() const override;
};

