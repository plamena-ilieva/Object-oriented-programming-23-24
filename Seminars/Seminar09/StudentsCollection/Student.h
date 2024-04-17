#pragma once
#include "MyString.h"

class Student
{
	MyString name;
	unsigned age;

public:
	Student();
	Student(const MyString& name, unsigned age);

	const MyString& getName() const;
	unsigned getAge() const;
};

