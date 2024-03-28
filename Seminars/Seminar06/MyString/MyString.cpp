#include "MyString.h"
#include <cstring>
#pragma warning (disable : 4996)

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	data = new char[size + 1];
	strcpy(data, other.data);
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
}

MyString::MyString() : MyString("")
{
}

MyString::MyString(const char* str)
{
	size = strlen(str);
	data = new char[size + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

unsigned MyString::lenght() const
{
	return size;
}

const char* MyString::c_str() const
{
	return data;
}

MyString& MyString::concat(const MyString& other)
{
	char* buff = new char[size + other.size + 1];
	strcpy(buff, data);
	strcat(buff, other.data);

	delete[] data;
	data = buff;
	size += other.size;
	return *this;
}
