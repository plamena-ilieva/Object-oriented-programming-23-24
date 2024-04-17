#include "UniquePtrOfA.h"
#include <iostream>

void UniquePtrOfA::free()
{
	delete ptr;
}

void UniquePtrOfA::moveFrom(UniquePtrOfA&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

UniquePtrOfA::UniquePtrOfA(A* ptr) :ptr(ptr)
{
}

UniquePtrOfA::UniquePtrOfA(UniquePtrOfA&& other) noexcept
{
	moveFrom(std::move(other));
}

UniquePtrOfA& UniquePtrOfA::operator=(UniquePtrOfA&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

UniquePtrOfA::~UniquePtrOfA()
{
	free();
}

const A& UniquePtrOfA::operator*() const
{
	return *ptr;
}

A& UniquePtrOfA::operator*()
{
	return *ptr;
}
