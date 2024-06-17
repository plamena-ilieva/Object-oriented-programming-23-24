#include <iostream>
#include <exception>

template <typename T>
class MyQueue
{
	T* data;
	size_t capacity;
	size_t size;

	size_t get;
	size_t put;

	void resize();

	void moveFrom(MyQueue<T>&& other);
	void copyFrom(const MyQueue<T>& other);
	void free();
public:
	MyQueue();

	MyQueue(const MyQueue<T>& other);
	MyQueue<T>& operator=(const MyQueue<T>& other);

	MyQueue(MyQueue<T>&& other) noexcept;
	MyQueue<T>& operator=(MyQueue<T>&& other) noexcept;

	void push(const T& obj);
	void push(T&& obj);
	void pop();

	const T& peek() const;
	bool isEmpty() const;

	~MyQueue();

};

template<typename T>
void MyQueue<T>::resize()
{
	T* temp = new T[capacity * 2];
	int i = 0;

	while (i != size)
	{
		temp[i++] = data[get];
		(++get) %= capacity;
	}
	delete[] data;
	data = temp;
	get = 0;
	put = size;
	capacity *= 2;
}

template<typename T>
void MyQueue<T>::moveFrom(MyQueue<T>&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	get = other.get;
	put = other.put;
}

template<typename T>
void MyQueue<T>::copyFrom(const MyQueue<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	get = other.get;
	put = other.put;

	data = new T[other.capacity];
	int i = get;

	do {
		data[i] = other.data[i];
		(++i) %= capacity;
	} while (i != put);
}

template<typename T>
void MyQueue<T>::free()
{
	delete[] data;
}

template<typename T>
MyQueue<T>::MyQueue()
{
	capacity = 4;
	size = get = put = 0;
	data = new T[capacity];
}

template<typename T>
inline MyQueue<T>::MyQueue(const MyQueue<T>& other)
{
	copyFrom(other);
}

template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
MyQueue<T>::MyQueue(MyQueue<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
void MyQueue<T>::push(const T& obj)
{
	if (size == capacity) {
		resize();
	}

	data[put] = obj;
	(++put) %= capacity;
	size++;
}

template<typename T>
void MyQueue<T>::push(T&& obj)
{
	if (size == capacity) {
		resize();
	}

	data[put] = std::move(obj);
	(++put) %= capacity;
	size++;
}

template<typename T>
inline void MyQueue<T>::pop()
{
	if (isEmpty()) {
		throw std::exception("Empty queue!");
	}

	size--;
	(++get) %= capacity;
}

template<typename T>
const T& MyQueue<T>::peek() const
{
	if (isEmpty()) {
		throw std::exception("Empty queue!");
	}

	const T& temp = data[get];
	return temp;
}

template<typename T>
bool MyQueue<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
inline MyQueue<T>::~MyQueue()
{
	free();
}