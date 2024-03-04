#include <iostream>
#include <fstream>

enum class Error {
    OK, 
    NULLPTR,
    EMPTY_STRING,
    INVALID_CHARACTER,
    LEADING_ZEROES
};

struct ConvertResult {
    int result = 0;
    Error errCode = Error::OK;
};

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int converToInt(char ch) {
    if (isDigit(ch)) {
        return ch - '0';
    }
    return ch;
}

ConvertResult convertStringToInt(const char* str) {
    if (str == nullptr) {
        return ConvertResult{ 0, Error::NULLPTR };
    }

    if (*str == '\0') {
        return ConvertResult{ 0, Error::EMPTY_STRING };
    }

    bool isNegative = false;
    if (*str == '-') {
        isNegative = true;
        ++str;
    }

    const char* strCopy = str;
    strCopy++;
    if (*str == '0' && (*strCopy != '\0' || isNegative)) {
        return ConvertResult{ 0, Error::LEADING_ZEROES };
    }

    int result = 0;

    while (*str != '\0') {
        if (!isDigit(*str)) {
            return ConvertResult{ 0, Error::INVALID_CHARACTER };
        }

        result = result * 10 + converToInt(*str);
        ++str;
    }
    
    if (isNegative) {
        result *= -1;
    }

    return ConvertResult{ result, Error::OK };
}

void printError(Error err) {
    switch (err) {
        case Error::OK:
            std::cout << "Ok" << std::endl;
            break;
        case Error::NULLPTR:
            std::cout << "String is nullptr!" << std::endl;
            break;
        case Error::EMPTY_STRING:
            std::cout << "String is empty!" << std::endl;
            break;
        case Error::INVALID_CHARACTER:
            std::cout << "String contains non-digit characters!" << std::endl;
            break;
        case Error::LEADING_ZEROES:
            std::cout << "String contains leading zeros!" << std::endl;
            break;
        default:
            break;
    }
}

int main() {
    std::cout << convertStringToInt("-123").result << std::endl;
    std::cout << convertStringToInt("123").result << std::endl;
    std::cout << convertStringToInt("0").result << std::endl;

    printError(convertStringToInt("001").errCode);
    printError(convertStringToInt("-01").errCode);
    printError(convertStringToInt("12.3").errCode);
    printError(convertStringToInt("").errCode);
    printError(convertStringToInt(nullptr).errCode);
}