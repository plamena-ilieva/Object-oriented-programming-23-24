#include <iostream>

class MapOfNaturals {
	static constexpr unsigned MAX_SIZE = 100;
	int data[MAX_SIZE];
	unsigned size = 0;

public:
	MapOfNaturals() {
		for (size_t i = 0; i < MAX_SIZE; i++)
		{
			data[i] = -1;
		}
	}

	void insert(unsigned key, int value) {
		if (key >= MAX_SIZE) {
			throw std::out_of_range("Key is out of range");
		}
		data[key] = value;
		size++;
	}

	unsigned get(unsigned key) const {
		if (key >= MAX_SIZE || data[key] == -1) {
			throw std::out_of_range("Map contains no such key");
		}

		return data[key];
	}

	bool containsKey(unsigned key) const {
		if (key >= MAX_SIZE) {
			throw std::out_of_range("Key is out of range");
		}

		return data[key] != -1;
	}

	bool isEmpty() const {
		return size == 0;
	}
};

unsigned fib(unsigned n) {
	static MapOfNaturals map;

	if (map.isEmpty()) {
		map.insert(1, 1);
		map.insert(2, 1);
	}

	if (!map.containsKey(n)) {
		map.insert(n, fib(n - 1) + fib(n - 2));
	}

	return map.get(n);
}

int main() {
	std::cout << fib(55);
}