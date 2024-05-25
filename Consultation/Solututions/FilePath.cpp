#include "FilePath.h"
#include <cstring>
#include <utility>

#pragma warning(disable:4996)

void FilePath::copyFrom(const FilePath& other)
{
	path = new char[strlen(other.path) + 1] {};
	strcpy(path, other.path);
}

void FilePath::moveFrom(FilePath&& other)
{
	path = other.path;
	other.path = nullptr;
}

void FilePath::free()
{
	delete[] path;
}

FilePath::FilePath(const char* filePath)
{
	path = new char[strlen(filePath) + 1] {};
	strcpy(path, filePath);
}

FilePath::FilePath(const FilePath& other)
{
	copyFrom(other);
}

FilePath::FilePath(FilePath&& other)
{
	moveFrom(std::move(other));
}

FilePath& FilePath::operator=(const FilePath& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


FilePath& FilePath::operator=(FilePath&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

const char* FilePath::c_str() const
{
	return path;
}

FilePath::~FilePath()
{
	free();
}


