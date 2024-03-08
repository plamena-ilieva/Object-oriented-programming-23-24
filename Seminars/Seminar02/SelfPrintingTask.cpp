#include <iostream>
#include <fstream>
constexpr int BUFF_SIZE = 1024;

void printFile(const char* fileName) {
	std::ifstream inFile(fileName);

	if (!inFile.is_open()) {
		return;
	}
	
	while (!inFile.eof()) {
		char buff[BUFF_SIZE];
		inFile.getline(buff, BUFF_SIZE);

		std::cout << buff << std::endl;
	}

	inFile.close();
}

int main()
{
	printFile("SelfPrintingTask.cpp");
}
