#include "ShapeCollection.h"
#include <stdexcept>      // std::out_of_range
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		delete shapes[i];
	}

	delete[] shapes;
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.capacity];

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
	
	shapesCount = other.shapesCount;
	capacity = other.capacity;
}

void ShapeCollection::moveFrom(ShapeCollection&& other)
{
	shapes = other.shapes;
	other.shapes = nullptr;

	shapesCount = other.shapesCount;
	capacity = other.capacity;
}

void ShapeCollection::resize()
{
	Shape** temp = new Shape*[2 * capacity];

	for (size_t i = 0; i < shapesCount; i++)
	{
		temp[i] = shapes[i];
	}

	capacity *= 2;
	delete[] shapes;
	shapes = temp;
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount == capacity) {
		resize();
	}

	shapes[shapesCount++] = shape;
}

ShapeCollection::ShapeCollection()
{
	shapesCount = 0;
	capacity = 8;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}

ShapeCollection::ShapeCollection(ShapeCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addRectangle(int x1, int y1, int x3, int y3)
{
	Rectangle* rec = new Rectangle(x1, y1, x3, y3);
	addShape(rec);
}

void ShapeCollection::addCircle(int x1, int y1, int r)
{
	Circle* cir = new Circle(x1, y1, r);
	addShape(cir);
}

void ShapeCollection::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	Triangle* tr = new Triangle(x1, y1, x2, y2, x3, y3);
	addShape(tr);
}

double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount) {
		throw std::out_of_range("Index out of range!");
	}

	return shapes[ind]->getPer();
}

double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount) {
		throw std::out_of_range("Index out of range!");
	}

	return shapes[ind]->getArea();
}

bool ShapeCollection::getIfPointInShapeByIndex(size_t ind, int x, int y) const
{
	if (ind >= shapesCount) {
		throw std::out_of_range("Index out of range!");
	}

	return shapes[ind]->isPointIn(x, y);
}
