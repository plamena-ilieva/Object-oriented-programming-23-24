#pragma once
#include <utility>
#include <cstddef>

template <class T, class Factory>
class Container
{
private:
	T** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t newCap);
	void moveFrom(Container<T, Factory>&& other);
	void copyFrom(const Container<T, Factory>& other);
	void free();

	void add(T* elem);
public:
	Container();

	Container(const Container<T, Factory>& other);
	Container(Container<T, Factory>&& other) noexcept;

	Container<T, Factory>& operator=(const Container<T, Factory>&);
	Container<T, Factory>& operator=(Container<T, Factory>&&) noexcept;

	~Container() noexcept;
	void add(const T& elem);

	void add(typename Factory::RecordType str);

	const T* operator[](unsigned) const;
	T* operator[](unsigned);
	unsigned getSize() const;
};

template<class T, class Factory>
void Container<T, Factory>::add(typename Factory::RecordType str)
{
	T* ptr = Factory::create(str);

	if (ptr)
		add(ptr);
}

template<class T, class Factory>
Container<T, Factory>::Container(const Container<T, Factory>& other)
{
	copyFrom(other);
}

template<class T, class Factory>
Container<T, Factory>::Container(Container<T, Factory>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T, class Factory>
Container<T, Factory>& Container<T, Factory>::operator=(const Container<T, Factory>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T, class Factory>
Container<T, Factory>& Container<T, Factory>::operator=(Container<T, Factory>&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T, class Factory>
Container<T, Factory>::~Container() noexcept
{
	free();
}

template<class T, class Factory>
Container<T, Factory>::Container()
{
	capacity = 8;
	data = new T * [capacity] {nullptr};
	size = 0;
}

template<class T, class Factory>
void Container<T, Factory>::moveFrom(Container<T, Factory>&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

template<class T, class Factory>
void Container<T, Factory>::copyFrom(const Container<T, Factory>& other)
{
	data = new T * [other.capacity];

	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i]->clone();
	}

	size = other.size;
	capacity = other.capacity;
}

template<class T, class Factory>
void Container<T, Factory>::free()
{
	for (int i = 0; i < size; i++) {
		delete data[i];
	}

	delete[] data;
}

template<class T, class Factory>
void Container<T, Factory>::add(T* elem)
{
	if (size == capacity) {
		resize(capacity * 2);
	}

	data[size++] = elem;
}

template<class T, class Factory>
void Container<T, Factory>::add(const T& elem)
{
	T* cloned = elem.clone();
	add(cloned);
}

template<class T, class Factory>
void Container<T, Factory>::resize(size_t newCap)
{
	T** temp = new T * [newCap];
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
	capacity = newCap;
}

template<class T, class Factory>
unsigned Container<T, Factory>::getSize() const
{
	return size;
}

template<class T, class Factory>
const T* Container<T, Factory>::operator[](unsigned ind) const
{
	return data[ind];
}

template<class T, class Factory>
T* Container<T, Factory>::operator[](unsigned ind)
{
	return data[ind];
}