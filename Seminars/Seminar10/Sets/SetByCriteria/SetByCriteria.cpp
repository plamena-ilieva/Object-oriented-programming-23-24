#include "SetByCriteria.h"
#include <iostream>

void SetByCriteria::extractNumbers()
{
	for (size_t i = 0; i <= getMaxNum(); i++)
	{
		if (pred(i)) {
			Set::add(i);
		}
	}
}

SetByCriteria::SetByCriteria(unsigned n, bool(*pred)(unsigned n)) : Set(n), pred(pred)
{
	extractNumbers();
}

void SetByCriteria::add(unsigned n)
{
	if (pred(n)) {
		Set::add(n);
	}
	else {
		throw std::invalid_argument("Number does not meet the criteria");
	}
}

bool SetByCriteria::contains(unsigned n) const
{
	return Set::contains(n);
}

void SetByCriteria::remove(unsigned n)
{
	Set::remove(n);
}

void SetByCriteria::print() const
{
	Set::print();
}

void SetByCriteria::setPred(bool(*pred)(unsigned n))
{
	this->pred = pred;
	Set::clear();
	extractNumbers();
}
