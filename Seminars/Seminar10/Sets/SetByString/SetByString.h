#pragma once
#include "Set.h"

class SetByString : private Set
{
	char* str;

	void free();
	void copyFrom(const SetByString& other);
	void moveFrom(SetByString&& other);

	void extractNumbersFromString();

public:
	SetByString(unsigned n, const char* data);
	SetByString(const SetByString& other);
	SetByString(SetByString&& other) noexcept;

	SetByString& operator=(const SetByString& other);
	SetByString& operator=(SetByString&& other) noexcept;

	~SetByString();

	void print() const;
	void setText(const char* newStr);
	void setAt(unsigned idx, char ch);
};

