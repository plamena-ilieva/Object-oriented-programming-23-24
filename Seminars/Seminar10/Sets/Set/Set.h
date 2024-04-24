#pragma once

const unsigned BUCKET_SIZE = 8;
class Set
{
	unsigned char* data;
	unsigned maxNum;
	unsigned size;

	void copyFrom(const Set& other);
	void free();

	unsigned getBucket(unsigned n) const;
	unsigned char getMask(unsigned n) const;

public:
	Set();
	Set(unsigned max);
	Set(const Set& other);
	Set& operator=(const Set& other);
	~Set();

	void add(unsigned n);
	void remove(unsigned n);
	bool contains(unsigned n) const;
	void print() const;

	unsigned getMaxNum() const;
	void clear();

	friend Set intersectionOfSets(const Set& lhs, const Set& rhs);
	friend Set unionOfSets(const Set& lhs, const Set& rhs);
};

