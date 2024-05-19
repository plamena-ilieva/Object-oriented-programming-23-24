#pragma once
#include "Shape.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void moveFrom(ShapeCollection&& other);
	void resize();

	void addShape(Shape* shape);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection(ShapeCollection&& other) noexcept;
	ShapeCollection& operator=(const ShapeCollection& other);
	ShapeCollection& operator=(ShapeCollection&& other) noexcept;
	~ShapeCollection();

	void addRectangle(int x1, int y1, int x3, int y3);
	void addCircle(int x1, int y1, int r);
	void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

	double getPerOfFigureByIndex(size_t ind) const;
	double getAreaOfFigureByIndex(size_t ind) const;
	bool getIfPointInShapeByIndex(size_t ind, int x, int y) const;
};