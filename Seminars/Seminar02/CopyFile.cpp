#include <iostream>
#include <fstream>

constexpr int BUFF_SIZE = 1024;

bool copyFile(const char* source, const char* dest) {
    std::ifstream sourceFile(source);
    if (!sourceFile.is_open()) {
        return false;
    }
    std::ofstream destFile(dest);
    if (!destFile.is_open()) {
        return false;
    }

    while (!sourceFile.eof()) {
        char buff[BUFF_SIZE];
        sourceFile.getline(buff, BUFF_SIZE);

        destFile << buff << std::endl;
    }

    sourceFile.close();
    destFile.close();
    return true;
}

int main()
{
    std::cout << copyFile("file.txt", "newfile.txt");
}