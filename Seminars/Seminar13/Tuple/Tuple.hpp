#include <iostream>

#define TT template<typename T, size_t N>

TT
class Tuple
{
private:
	T data[N];

public:
	const size_t getSize() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	void print() const;
};

TT
const size_t Tuple<T, N>::getSize() const
{
	return N; // Not needed as getter function, because the length is given in template
}

TT
const T& Tuple<T, N>::operator[](size_t index) const
{
	return this->data[index];
}

TT
T& Tuple<T, N>::operator[](size_t index)
{
	return this->data[index];
}

TT
void Tuple<T, N>::print() const
{
	std::cout << "[ ";
	for (size_t i = 0; i < N; i++)
		std::cout << this->data[i] << ' ';
	std::cout << "]";
}