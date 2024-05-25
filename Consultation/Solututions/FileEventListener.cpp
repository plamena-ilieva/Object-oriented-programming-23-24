#include "FileEventListener.h"
#pragma warning(disable:4996)
unsigned FileEventListener::getFileSize(std::ifstream& ifs)
{
    size_t currentIndex = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(currentIndex);
    return size;
}

FileEventListener::FileEventListener(const char* filePath) :
    path(filePath)
{
    std::ifstream ifs(path.c_str());
    if (ifs.is_open())
        lastFileSize = getFileSize(ifs);
}

// Allocates memory please delete :)
const char* FileEventListener::check()
{
    std::ifstream ifs(path.c_str());
    if (!ifs.is_open())
        return nullptr;

    int size = getFileSize(ifs);

    if (size != lastFileSize)
    {
        char* message = new char[128] {};
        sprintf(message, 
            "The file %s was changed by %d nytes", path.c_str(), 
            (lastFileSize - size));
        lastFileSize = size;
        return message;
    }

    return nullptr;
}

EventListener* FileEventListener::clone() const
{
    return new FileEventListener(*this);
}
