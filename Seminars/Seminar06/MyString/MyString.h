#pragma once
class MyString
{
	char* data;
	unsigned size;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	unsigned lenght() const;
	const char* c_str() const;
	MyString& concat(const MyString& other);
};

