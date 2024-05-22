#include <iostream>
#include "MyQueue.hpp"

int main()
{
    MyQueue<int> q;
    q.push(2);
    q.push(3);
    std::cout << q.peek() << std::endl;
    q.push(4);
    q.push(5);
    q.pop();
    q.push(6);
    q.push(7);
    std::cout << q.peek() << std::endl;
    MyQueue<int> q2(q);
    std::cout << q2.peek() << std::endl;

    q.pop();
    std::cout << q.peek() << std::endl;
    q.pop();
    std::cout << q.peek() << std::endl;
    q.pop();
    std::cout << q.peek() << std::endl;
    q.pop();
    std::cout << q.peek() << std::endl;
}
