#include <iostream>
#include "Polymorphic_Container.hpp"

class Base {
public:
    virtual void execute() const = 0;
    virtual Base* clone() const = 0;
    virtual ~Base() = default;
};

class A : public Base {
public:
    void execute() const override {
        std::cout << "A" << std::endl;
    }
    A* clone() const override {
        return new A(*this);
    }
};

class B : public Base {
public:
    void execute() const override {
        std::cout << "B" << std::endl;
    }
    B* clone() const override {
        return new B(*this);
    }
};

int main()
{
    Polymorphic_Container<Base> container;
    container.add(new A());
    container.add(new B());

    container.execute(0, [](Base* ptr) { ptr->execute(); });
    container.execute(1, [](Base* ptr) { ptr->execute(); });

    container[0]->execute();
}