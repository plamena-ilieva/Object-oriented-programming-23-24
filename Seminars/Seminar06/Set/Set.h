#pragma once
class Set
{
	unsigned char* data;
	unsigned maxNum;

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
};

