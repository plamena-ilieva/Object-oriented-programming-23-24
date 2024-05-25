#pragma once
#include "EventListener.h"
#include "FilePath.h"
#include <fstream>

class FileEventListener :
    public EventListener
{
private:
    FilePath path;
    int lastFileSize = 0;

    static unsigned getFileSize(std::ifstream& ifs);

public:
    FileEventListener(const char* filePath);

    const char* check() override;
    EventListener* clone() const override;
};

