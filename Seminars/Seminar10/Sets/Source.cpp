#include <iostream>
#include "SetByCriteria.h"
#include "SetByString.h"

int main()
{
    SetByCriteria sc(20, [](unsigned n) { return n % 2 == 0 && n % 3 != 0; });
    sc.print();

    sc.setPred([](unsigned n) { return n % 7 != 0; });
    sc.print();

    SetByString ss(20, "12 3 4 6 7");
    ss.print();

    ss.setAt(1, '1');
    ss.print();
}
