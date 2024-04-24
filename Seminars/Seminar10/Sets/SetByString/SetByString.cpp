#include "SetByString.h"
#include <iostream>
#include <sstream>
#pragma warning (disable:4996)

void SetByString::free()
{
	delete[] str;
}

void SetByString::copyFrom(const SetByString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
}

void SetByString::moveFrom(SetByString&& other)
{
	str = other.str;
	other.str = nullptr;
}

void SetByString::extractNumbersFromString()
{
	std::stringstream ss(str);

	while (!ss.eof()) {
		unsigned curr;
		ss >> curr;
		Set::add(curr);
	}
}

SetByString::SetByString(unsigned n, const char* data) : Set(n)
{
	str = new char[strlen(data) + 1];
	strcpy(str, data);
	extractNumbersFromString();
}

SetByString::SetByString(const SetByString& other) : Set(other)
{
	copyFrom(other);
}

SetByString::SetByString(SetByString&& other) noexcept : Set(std::move(other))
{
	moveFrom(std::move(other));
}

SetByString& SetByString::operator=(const SetByString& other)
{
	if (this != &other) {
		Set::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

SetByString& SetByString::operator=(SetByString&& other) noexcept
{
	if (this != &other) {
		Set::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SetByString::~SetByString()
{
	free();
}

void SetByString::print() const
{
	Set::print();
}

void SetByString::setText(const char* newStr)
{
	if (newStr == nullptr) {
		throw std::exception("Nullptr");
	}

	delete[] str;
	str = new char[strlen(newStr) + 1];
	strcpy(str, newStr);
	Set::clear();
	extractNumbersFromString();
}

void SetByString::setAt(unsigned idx, char ch)
{
	str[idx] = ch;
	Set::clear();
	extractNumbersFromString();
}
