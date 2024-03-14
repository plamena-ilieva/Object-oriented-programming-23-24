#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& inFile) {
    size_t currPos = inFile.tellg();
    inFile.seekg(0, std::ios::end);
    size_t res = inFile.tellg();
    inFile.seekg(currPos);

    return res;
}

int* fillArray(std::ifstream& inFile, size_t& size) {
    size = getFileSize(inFile) / sizeof(int);
    int* res = new int[size];
    inFile.read((char*)res, size * sizeof(int));
    return res;
}

size_t countOfEvenNumbers(const int* numbers, size_t numbersSize) {
    int res = 0;
    for (size_t i = 0; i < numbersSize; i++) {
        if (numbers[i] % 2 == 0) {
            res++;
        }
    }
    return res;
}

void splitArray(const int* numbers, size_t numbersSize, int* odd, int* even) {
    for (size_t i = 0; i < numbersSize; i++)
    {
        if (numbers[i] % 2 != 0) {
            *odd = numbers[i];
            ++odd;
        }
        else {
            *even = numbers[i];
            ++even;
        }
    }
}

bool saveArrayToFile(const char* fileName, const int* arr, size_t size) {
    std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
    if (!outFile.is_open()) {
        return false;
    }

    outFile.write((const char*)arr, size * sizeof(int));
    outFile.close();

    return true;
}

bool splitArrays(const char* originFileName, const char* oddFileName, const char* evenFileName) {
    std::ifstream inFile(originFileName, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        return false;
    }

    size_t size;
    int* numbers = fillArray(inFile, size);
    inFile.close();

    size_t evenSize = countOfEvenNumbers(numbers, size);
    size_t oddSize = size - evenSize;

    int* evenNumbers = new int[evenSize];
    int* oddNumbers = new int[oddSize];

    splitArray(numbers, size, oddNumbers, evenNumbers);
    bool res = saveArrayToFile(oddFileName, oddNumbers, oddSize) &&
        saveArrayToFile(evenFileName, evenNumbers, evenSize);

    delete[] oddNumbers;
    delete[] evenNumbers;
    delete[] numbers;

    return res;
}

int main()
{
    splitArrays("numbers.dat", "odd.dat", "even.dat");
    return 0;
}
