#include "FileEventResponse.h"
#include <fstream>

FileEventResponse::FileEventResponse(const char* filePath) :
    path(filePath)
{
}

void FileEventResponse::respond(const char* message) const
{
    if (!message) return;

    std::ofstream outFile(path.c_str(), std::ios::app);
    if (outFile.is_open())
        outFile << message << std::endl;
}

EventResponse* FileEventResponse::clone() const
{
    return new FileEventResponse(*this);
}
