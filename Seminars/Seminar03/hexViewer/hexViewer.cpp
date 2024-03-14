#include <iostream>
#include <fstream>
#include <iomanip>

struct HexViewerFile
{
	unsigned char* data;
	size_t dataSize;
};

size_t getFileSize(std::ifstream& file)
{
	size_t currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(currentPos);
	return fileSize;
}

HexViewerFile init(const char* fileName) {
	std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
	HexViewerFile file;

	if (!inFile.is_open()) {
		file.data = nullptr;
		file.dataSize = 0;
		return file;
	}

	file.dataSize = getFileSize(inFile);
	file.data = new unsigned char[file.dataSize];
	inFile.read((char*)file.data, file.dataSize);
	inFile.close();

	return file;
}

void freeHexViewerFile(HexViewerFile& file) {
	delete[] file.data;
	file.dataSize = 0;
}

void saveHexViewerFile(const HexViewerFile& file, const char* fileName) {
	std::ofstream outFile(fileName, std::ios::out | std::ios::binary);

	if (!outFile.is_open()) {
		return;
	}

	outFile.write((const char*)file.data, file.dataSize);
	outFile.close();
}
bool isLetter(char ch) {
	return (ch >= 'A' && ch <= 'Z' ||
		ch >= 'a' && ch <= 'z');
}

void print(const HexViewerFile& file) {
	for (size_t i = 0; i < file.dataSize; i++) {
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)file.data[i] << ' ';
	}
	std::cout << std::endl;

	for (size_t i = 0; i < file.dataSize; i++)
	{
		if (isLetter(file.data[i])) {
			std::cout << file.data[i] << "  ";
		}
		else {
			std::cout << ".. ";
		}
	}
}

void modify(HexViewerFile& file, unsigned idx, char val) {
	if (idx >= file.dataSize) {
		return;
	}
	file.data[idx] = val;
}

int main()
{
	HexViewerFile myFile = init("myFile.dat");
	print(myFile);
	modify(myFile, 0, 'a');
	saveHexViewerFile(myFile, "myFile.dat");
	freeHexViewerFile(myFile);
}