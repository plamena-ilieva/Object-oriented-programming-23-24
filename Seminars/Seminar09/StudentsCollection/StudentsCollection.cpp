#include "StudentsCollection.h"

void StudentsCollection::copyFrom(const StudentsCollection& other)
{
	size = other.size;
	capacity = other.capacity;
	count = other.count;
	firstFreeIndex = other.firstFreeIndex;

	students = new Student * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		if (other.students[i] == nullptr) {
			students[i] = nullptr;
		}
		else {
			students[i] = new Student(*other.students[i]);
		}
	}
}

void StudentsCollection::moveFrom(StudentsCollection&& other)
{
	size = other.size;
	capacity = other.capacity;
	count = other.count;
	firstFreeIndex = other.firstFreeIndex;
	students = other.students;

	other.students = nullptr;
	other.size = other.capacity = other.count = other.firstFreeIndex = 0;
}

void StudentsCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete students[i];
	}
	delete[] students;
	count = capacity = size = firstFreeIndex = 0;
}

void StudentsCollection::resize(size_t newCap)
{
	capacity = newCap;
	Student** temp = new Student * [capacity];

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = students[i];
	}

	delete[] students;
	students = temp;
}

void StudentsCollection::goToNextFreeIndex()
{
	for (size_t i = firstFreeIndex + 1; i < capacity; i++)
	{
		if (students[i] == nullptr) {
			firstFreeIndex = i;
			return;
		}
	}
	firstFreeIndex = capacity;
}

size_t StudentsCollection::getLastFreeIndex() const
{
	for (int i = size - 1; i >= 0; i--)
	{
		if (students[i] != nullptr) {
			return i + 1;
		}
	}
	return 0;
}

StudentsCollection::StudentsCollection()
{
	capacity = 16;
	students = new Student * [capacity] {nullptr};
}

StudentsCollection::StudentsCollection(const StudentsCollection& other)
{
	copyFrom(other);
}

StudentsCollection& StudentsCollection::operator=(const StudentsCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StudentsCollection::StudentsCollection(StudentsCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentsCollection& StudentsCollection::operator=(StudentsCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

StudentsCollection::~StudentsCollection()
{
	free();
}

void StudentsCollection::addAtFirstFree(const Student& student)
{
	if (count == capacity) {
		resize(capacity * 2);
	}

	students[firstFreeIndex] = new Student(student);
	goToNextFreeIndex();
	count++;

	if (firstFreeIndex >= size) {
		size++;
	}
}

void StudentsCollection::addAtFirstFree(Student&& student)
{
	if (count == capacity) {
		resize(capacity * 2);
	}

	students[firstFreeIndex] = new Student(std::move(student));
	goToNextFreeIndex();
	count++;

	if (firstFreeIndex >= size) {
		size++;
	}
}

void StudentsCollection::setAtIdx(const Student& student, size_t idx)
{
	if (idx >= capacity) {
		resize(capacity * 2);
	}

	if (students[idx] == nullptr) {
		students[idx] = new Student(student);
		count++;

		if (idx == firstFreeIndex) {
			goToNextFreeIndex();
		}
	}
	else {
		*students[idx] = student;
	}
	
	if (idx >= size) {
		size = idx + 1;
	}
}

void StudentsCollection::setAtIdx(Student&& student, size_t idx)
{
	if (idx >= capacity) {
		resize(capacity * 2);
	}

	if (students[idx] == nullptr) {
		students[idx] = new Student(std::move(student));
		count++;

		if (idx == firstFreeIndex) {
			goToNextFreeIndex();
		}
	}
	else {
		*students[idx] = std::move(student);
	}

	if (idx >= size) {
		size = idx + 1;
	}
}

void StudentsCollection::removeAtIdx(size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("Out of range");
	}

	if (students[idx] != nullptr) {
		count--;
	}
	delete students[idx];
	students[idx] = nullptr;

	if (idx < firstFreeIndex) {
		firstFreeIndex = idx;
	}
	
	size = getLastFreeIndex();
}

bool StudentsCollection::containsAt(size_t idx) const
{
	return idx <= capacity && students[idx] != nullptr;
}

size_t StudentsCollection::getNumberInClass(const MyString& name) const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (students[i] != nullptr && name == students[i]->getName()) {
			return i + 1;
		}
	}

	throw std::invalid_argument("No such student!");
}
