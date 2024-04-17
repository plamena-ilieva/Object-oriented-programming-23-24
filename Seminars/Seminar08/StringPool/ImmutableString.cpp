#include "ImmutableString.h"

#include "String.h"
#pragma warning (disable:4996)
#include <cstring>
#include <cassert>

StringPool ImmutableString::pool;

ImmutableString::ImmutableString() : ImmutableString("") {}

ImmutableString::ImmutableString(const char* text)
{
	data = pool.add(text);
	size = strlen(text);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
	data = pool.add(other.c_str());
	size = other.size;
}

char ImmutableString::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("String::operator[] out of range!");

	return data[index];
}

ImmutableString& ImmutableString::operator=(const ImmutableString& other)
{
	if (this != &other)
	{
		pool.remove(data);
		data = pool.add(other.c_str());
		size = other.size;
	}

	return *this;
}

const char* ImmutableString::c_str() const
{
	return data;
}

size_t ImmutableString::length() const
{
	return size;
}

bool ImmutableString::empty() const
{
	return (size == 0);
}

ImmutableString::~ImmutableString()
{
	pool.remove(data);
}

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
{
	// if you make it friend you can directly compare the data pointers
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str)
{
	return os << str.c_str();
}