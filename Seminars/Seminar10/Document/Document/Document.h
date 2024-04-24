#pragma once
#include "MyString.h"

struct Comment {
	MyString text = "good";
	MyString author = "Pesho";

	void print() const;
};

class Document
{
	MyString content = "abcd";
	Comment comments[100];
	size_t commentsCount;

public:
	void display() const;
	void addComment(const Comment& comment);
	void setContent(const MyString& newContent);
};

