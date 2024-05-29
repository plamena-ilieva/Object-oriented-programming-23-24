#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>
#include <utility>


template <typename T>
class Vector
{
    T* data;
    size_t size;
    size_t capacity;

    void free();
    void copyFrom(const Vector<T>& other);
    void moveFrom(Vector<T>&& other);
    void resize(size_t newCapacity);

public:
    Vector();
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);

    Vector<T> operator=(const Vector<T>& other);
    Vector<T> operator=(Vector<T>&& other);

    void pushBack(const T& element);
    void pushBack(T&& element);

    void popBack();

    void insert(const T& element, size_t index);
    void insert(T&& element, size_t index);

    void erase(size_t index);

    void clear();

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    bool isEmpty() const;
    size_t getSize() const;

    ~Vector();
};

template <typename T>
void Vector<T>::free()
{
    delete[] data;
    data = nullptr;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < size; i++)
    {
        data = other.data;
    }
}

template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.data = nullptr;
}

template <typename T>
void Vector<T>::resize(size_t newCapacity)
{
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = std::move(data[i]);
    }

    delete[] data;
    data = newData;
}

template <typename T>
Vector<T>::Vector()
{
    capacity = 8;
    size = 0;

    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other)
{
    moveFrom(std::move(other));
}

template <typename T>
Vector<T> Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator=(Vector<T>&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template <typename T>
void Vector<T>::pushBack(const T& element)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }

    data[size++] = element;
}

template <typename T>
void Vector<T>::pushBack(T&& element)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }

    data[size++] = std::move(element);
}

template <typename T>
void Vector<T>::popBack()
{
    if (isEmpty())
    {
        throw std::runtime_error("Cannot remove element from empty vector!");
    }

    if (size * 4 == capacity)
    {
        resize(capacity / 2);
    }

    size--;
}

template <typename T>
void Vector<T>::insert(const T& element, size_t index)
{
    if (index >= size)
    {
        throw std::runtime_error("Cannot insert element at non-existing index!");
    }

    if (size == capacity)
    {
        resize(2 * capacity);
    }

    for (size_t i = size; i > index; i--)
    {
        data[i] = std::move(data[i - 1]);
    }

    data[index] = element;
    size++;
}

template <typename T>
void Vector<T>::insert(T&& element, size_t index)
{
    if (index >= size)
    {
        throw std::runtime_error("Cannot insert element at non-existing index!");
    }

    if (size == capacity)
    {
        resize(2 * capacity);
    }

    for (size_t i = size; i > index; i--)
    {
        data[i] = std::move(data[i - 1]);
    }

    data[index] = std::move(element);
    size++;
}


template <typename T>
void Vector<T>::erase(size_t index)
{
    if (index >= size)
    {
        throw std::runtime_error("Cannot erase element at non-existing index!");
    }

    if (size * 4 == capacity)
    {
        resize(capacity / 2);
    }

    size--;

    for (size_t i = index; i < size; i++)
    {
        data[i] = std::move(data[i + 1]);
    }
}

template <typename T>
void Vector<T>::clear()
{
    free();
    size = 0;
    capacity = 8;
    data = new T[capacity];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
Vector<T>::~Vector()
{
    free();
}

template <typename T>
bool Vector<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
size_t Vector<T>::getSize() const
{
    return size;
}