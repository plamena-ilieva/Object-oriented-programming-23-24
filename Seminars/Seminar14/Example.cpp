#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base()\n";
    }
    Base(int a) {
        std::cout << "Base(int)\n";
    }
    ~Base() {
        std::cout << "~Base()\n";
    }
};

class A : virtual public Base {
public:
    A() : Base (1) {
        std::cout << "A()\n";
    }
    virtual ~A() {
        std::cout << "~A()\n";
    }
};

class B : virtual public Base {
public:
    B() {
        std::cout << "B()\n";
    }
    B(int) {
        std::cout << "B(int)\n";
    }
    virtual ~B() {
        std::cout << "~B()\n";
    }
};

class C : public A, public B{
public:
    C() : B(7), A(), Base(8) {
        std::cout << "C()\n";
    }
    ~C() {
        std::cout << "~C()\n";
    }
};

class D : public C {
public:
    D() : Base(19) {
        std::cout << "D()\n";
    }
    ~D() {
        std::cout << "~D()\n";
    }
};

int main() {
    D obj;
};