#include "Student.h"

Student::Student() : Student("", 18)
{
}

Student::Student(const MyString& name, unsigned age) : name(name), age(age)
{
}

const MyString& Student::getName() const
{
	return name;
}

unsigned Student::getAge() const
{
	return age;
}
