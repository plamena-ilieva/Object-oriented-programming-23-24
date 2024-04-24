#pragma once
#include "Set.h"

class SetByCriteria : private Set
{
	bool (*pred) (unsigned n);

	void extractNumbers();

public:
	SetByCriteria(unsigned n, bool (*pred) (unsigned n));

	void add(unsigned n);
	bool contains(unsigned n) const;
	void remove(unsigned n);

	void print() const;

	void setPred(bool (*pred) (unsigned n));
};

