#include <iostream>

class SwapCounter {
	static unsigned counter;

public:
	static void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
		counter++;
	}

	static unsigned getCount() {
		return counter;
	}

	static void resetCounter() {
		counter = 0;
	}
};

unsigned SwapCounter::counter = 0;

void print(const int* arr, size_t size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void bubbleSort(int* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		bool isSwapped = false;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j + 1] < arr[j])
			{
				SwapCounter::swap(arr[j], arr[j + 1]);
				isSwapped = true;
			}
		}
		if (!isSwapped)
			return;
	}
}

void selectionSort(int* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int minElIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minElIndex])
				minElIndex = j;
		}

		if (minElIndex != i)
			SwapCounter::swap(arr[minElIndex], arr[i]);
	}
}

int main()
{
	{
		int arr[10] = { 10,9,8,7,6,5,4,3,2,1 };
		bubbleSort(arr, 10);
		std::cout << "Bubble sort swaps: " << SwapCounter::getCount() << std::endl;
	}
	{
		SwapCounter::resetCounter();
		int arr[10] = { 10,9,8,7,6,5,4,3,2,1 };
		selectionSort(arr, 10);
		std::cout << "Selection sort swaps: " << SwapCounter::getCount() << std::endl;

	}
}
