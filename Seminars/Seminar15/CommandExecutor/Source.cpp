#include <iostream>
#include "CommandExecutor.h"

void print(const Vector<int>& v) {
	for (size_t i = 0; i < v.getSize(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	Vector<int> v;
	for (int i = 9; i >= 0; i--) {
		v.pushBack(i);
	}

	CommandExecutor& ce = CommandExecutor::getInstance();

	VectorCommand* vc1 = new SwapCommand(v, 4, 5);
	VectorCommand* vc2 = new SortCommand(v);

	ce.add(vc1);
	ce.add(vc2);
	print(v);
	ce.execute();
	print(v);
	ce.execute();
	print(v);
	ce.undo();
	print(v);
	ce.undo();
	print(v);
}