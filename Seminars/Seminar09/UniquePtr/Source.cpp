#include <iostream>
#include "UniquePtrOfA.h"

int main()
{
    UniquePtrOfA ptr(new A{2, 3});
    UniquePtrOfA ptr2 = std::move(ptr);

    (*ptr2).a = 9;

    std::cout << (*ptr2).a; //9
    //std::cout << (*ptr).a; грешка!
}