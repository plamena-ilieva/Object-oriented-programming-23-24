#include "Set.h"
#include <iostream>

void Set::copyFrom(const Set& other)
{
	maxNum = other.maxNum;
	size = other.size;
	data = new unsigned char[(maxNum + 1) / BUCKET_SIZE + 1];
	for (size_t i = 0; i < (maxNum + 1) / BUCKET_SIZE + 1; i++)
	{
		data[i] = other.data[i];
	}
}

void Set::free()
{
	delete[] data;
	data = nullptr;
	maxNum = size = 0;
}

unsigned Set::getBucket(unsigned n) const
{
	return n / BUCKET_SIZE;
}

unsigned char Set::getMask(unsigned n) const
{
	unsigned char mask = 1;
	mask <<= (BUCKET_SIZE - 1) - (n % BUCKET_SIZE);
	return mask;
}

Set::Set() : Set(15)
{
}

Set::Set(unsigned max)
{
	maxNum = max;
	size = (maxNum + 1) / BUCKET_SIZE + 1;
	data = new unsigned char[size] {};
}

Set::Set(const Set& other)
{
	copyFrom(other);
}

Set& Set::operator=(const Set& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
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


Set intersectionOfSets(const Set& lhs, const Set& rhs)
{
	const Set& maxSet = (lhs.maxNum > rhs.maxNum ? lhs : rhs);
	const Set& minSet = (lhs.maxNum < rhs.maxNum ? lhs : rhs);
	Set res(minSet);

	unsigned minBuckets = std::min(lhs.size, rhs.size);

	for (size_t i = 0; i < minBuckets; i++)
	{
		res.data[i] &= maxSet.data[i];
	}

	return res;
}

Set unionOfSets(const Set& lhs, const Set& rhs)
{
	const Set& maxSet = (lhs.maxNum> rhs.maxNum ? lhs : rhs);
	const Set& minSet = (lhs.maxNum < rhs.maxNum ? lhs : rhs);
	Set res(maxSet);

	unsigned minBuckets = std::min(lhs.size, rhs.size);

	for (size_t i = 0; i < minBuckets; i++)
	{
		res.data[i] |= minSet.data[i];
	}

	return res;
}
