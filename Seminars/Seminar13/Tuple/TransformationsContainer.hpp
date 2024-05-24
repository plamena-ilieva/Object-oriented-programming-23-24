#include "Transformer.hpp"

#define TT template<typename T, size_t N>

TT
class Transformations
{
private:
	Transformer<T, N>** container = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Transformations(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const Transformations& other);
	void moveFrom(Transformations&& other) noexcept;
	void free();

public:
	Transformations();

	Transformations(const Transformations& other);
	Transformations& operator=(const Transformations& other);

	Transformations(Transformations&& other) noexcept;
	Transformations& operator=(Transformations&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addTransformer(Transformer<T, N>* transformer);
	void addTransformer(const Transformer<T, N>& transformer);

	const Transformer<T, N>& operator[](size_t index) const;
	Transformer<T, N>& operator[](size_t index);

	Tuple<T, N>& transformAll(Tuple<T, N>& tuple) const;

	~Transformations() noexcept;
};

TT
Transformations<T, N>::Transformations() : Transformations(4) {}

TT
Transformations<T, N>::Transformations(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->container = new Transformer<T, N>* [this->capacity];
}

TT
Transformations<T, N>::Transformations(const Transformations<T, N>& other)
{
	copyFrom(other);
}

TT
Transformations<T, N>& Transformations<T, N>::operator=(const Transformations<T, N>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
Transformations<T, N>::Transformations(Transformations<T, N>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
Transformations<T, N>& Transformations<T, N>::operator=(Transformations<T, N>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const size_t Transformations<T, N>::getSize() const
{
	return this->size;
}

TT
const size_t Transformations<T, N>::getCapacity() const
{
	return this->capacity;
}

TT
void Transformations<T, N>::addTransformer(const Transformer<T, N>& transformer)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = transformer.clone();
}

TT
void Transformations<T, N>::addTransformer(Transformer<T, N>* transformer)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = transformer;
	transformer = nullptr;
}

TT
const Transformer<T, N>& Transformations<T, N>::operator[](size_t index) const
{
	return this->container[index];
}

TT
Transformer<T, N>& Transformations<T, N>::operator[](size_t index)
{
	return this->container[index];
}

TT
Tuple<T, N>& Transformations<T, N>::transformAll(Tuple<T, N>& tuple) const
{
	for (size_t i = 0; i < getSize(); i++)
		tuple = this->container[i]->transform(tuple);

	return tuple;
}

TT
Transformations<T, N>::~Transformations() noexcept
{
	free();
}

TT
const unsigned int Transformations<T, N>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

TT
const unsigned int Transformations<T, N>::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

TT
void Transformations<T, N>::resize(size_t newCapacity)
{
	Transformer<T, N>** newTransformers = new Transformer<T, N>* [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newTransformers[i] = this->container[i];

	delete[] this->container;
	this->container = newTransformers;
	this->capacity = newCapacity;
}

TT
void Transformations<T, N>::copyFrom(const Transformations<T, N>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->container = new Transformer<T, N> * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->container[i] = other.container[i]->clone();
}

TT
void Transformations<T, N>::moveFrom(Transformations<T, N>&& other) noexcept
{
	this->container = other.container;
	this->size = other.size;
	this->capacity = other.capacity;

	other.container = nullptr;
	other.size = other.capacity = 0;
}

TT
void Transformations<T, N>::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->container[i];

	delete[] this->container;
	this->container = nullptr;
	this->size = this->capacity = 0;
}