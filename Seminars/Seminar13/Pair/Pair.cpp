#include <iostream>
#include "Pair.hpp"

int main()
{
    Pair<int, int> p1(1, 2);
    Pair<int, Pair<int, int>> p2(5, p1);
    Pair<int, Pair<int, Pair<int, int>>> p3(4, p2);

    std::cout << p3;
}
