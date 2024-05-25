#pragma once
class FilePath
{
private:
	char* path = nullptr;

	void copyFrom(const FilePath&);
	void moveFrom(FilePath&&);
	void free();

public:
	FilePath(const char* filePath);

	FilePath(const FilePath&);
	FilePath(FilePath&&);

	FilePath& operator=(const FilePath&);
	FilePath& operator=(FilePath&&);

	const char* c_str() const;

	~FilePath();
};

