#include "MyString.h"
int main()
{
    MyString str;
    std::cin >> str;
    str += "ef";
    str += '1';
    std::cout << str;
}