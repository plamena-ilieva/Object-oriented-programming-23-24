#include <iostream>

enum Font {
    BOLD =      1 << 0,
    ITALICS =   1 << 1,
    UNDERLINE = 1 << 2
};

int main()
{
    int myDesign = BOLD | UNDERLINE;

    //    00000001
    //  | 00000100
    //  ___________
    //    00000101

    std::cout << myDesign;

    if (myDesign & BOLD) {
        // code for italics
    }

    return 0;
}