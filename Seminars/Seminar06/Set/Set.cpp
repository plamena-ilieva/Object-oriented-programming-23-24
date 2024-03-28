#include "Set.h"
#include <iostream>

void Set::copyFrom(const Set& other)
{
	maxNum = other.maxNum;
	data = new unsigned char[(maxNum + 1) / 8 + 1];
	for (size_t i = 0; i < (maxNum + 1) / 8 + 1; i++)
	{
		data[i] = other.data[i];
	}
}

void Set::free()
{
	delete[] data;
	data = nullptr;
	maxNum = 0;
}

unsigned Set::getBucket(unsigned n) const
{
	return n / 8;
}

unsigned char Set::getMask(unsigned n) const
{
	unsigned char mask = 1;
	mask <<= 7 - (n % 8);
	return mask;
}

Set::Set(unsigned max)
{
	maxNum = max;
	data = new unsigned char[(maxNum + 1) / 8 + 1] {};
}

Set::~Set()
{
	free();
}

void Set::add(unsigned n)
{
	if (n > maxNum) {
		return;
	}
	
	unsigned char mask = getMask(n);
	unsigned bucket = getBucket(n);

	data[bucket] |= mask;
}

void Set::remove(unsigned n)
{
	if (n > maxNum) {
		return;
	}

	unsigned char mask = getMask(n);
	unsigned bucket = getBucket(n);

	data[bucket] &= ~mask;
}

bool Set::contains(unsigned n) const
{
	if (n > maxNum) {
		return false;
	}

	unsigned char mask = getMask(n);
	unsigned bucket = getBucket(n);

	return (data[bucket] & mask);
}

void Set::print() const
{
	for (size_t i = 0; i <= maxNum; i++)
	{
		if (contains(i)) {
			std::cout << i << ' ';
		}
	}

	std::cout << std::endl;
}
