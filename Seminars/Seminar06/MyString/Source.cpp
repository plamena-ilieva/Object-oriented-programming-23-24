#include <iostream>
#include "MyString.h"
int main()
{
    MyString str("abc");
    str.concat("ef");
    std::cout << str.c_str();
}