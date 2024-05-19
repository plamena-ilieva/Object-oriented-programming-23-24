#include <iostream>
#include "ShapeCollection.h"
#include "Circle.h"
#include "Triangle.h"

class B;

class A {
public:
   

    virtual void f(const B* b) const {
        std::cout << "A::B" << std::endl;
    }
};

class B : public A {
public:
    void f(const A* a) const override {
        std::cout << "B::A" << std::endl;
    }
    void f(const B* b) const override {
        std::cout << "B::B" << std::endl;
    }
};


int main()
{
    /*A* b = new B();
    A* a = new A();
    a->f(a);
    a->f(b);
    b->f(a);
    b->f(b);
    */
    /*
    ShapeCollection s;

	s.addCircle(3, 4, 1);
	s.addTriangle(1, 2, 9, 4, 0, 0);
	s.addRectangle(1, 1, 9, 9);

	std::cout << s.getIfPointInShapeByIndex(0, 3, 4.5)<< std::endl;
	std::cout << s.getAreaOfFigureByIndex(2) << std::endl;
    
    Shape* t = new Triangle(1, 2, 9, 4, 0, 0);
    Shape* c = new Circle(3, 4, 1);
    t.intersectWith(c);
    */
}