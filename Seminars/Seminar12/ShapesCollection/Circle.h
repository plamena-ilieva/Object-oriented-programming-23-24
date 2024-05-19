#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(int x, int y, double radius);

	double getArea() const override;
	double getPer() const override; 
	bool isPointIn(int x, int y) const override;


	// Inherited via Shape
	Circle* clone() const override;


	// Inherited via Shape
	bool isIntersectedWith(Shape* shape) override;
	bool isIntersectedWithRectange(Rectangle* shape) override;
	bool isIntersectedWithTriangle(Triangle* shape) override;
	bool isIntersectedWithCircle(Circle* shape) override;

};