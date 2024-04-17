#pragma once
#include "Student.h"

class StudentsCollection {
	Student** students;
	size_t count = 0;
	size_t capacity;

	size_t size = 0;
	size_t firstFreeIndex = 0;

	void copyFrom(const StudentsCollection& other);
	void moveFrom(StudentsCollection&& other);
	void free();
	void resize(size_t newCap);

	void goToNextFreeIndex();
	size_t getLastFreeIndex() const;

public:
	StudentsCollection();

	StudentsCollection(const StudentsCollection& other);
	StudentsCollection& operator=(const StudentsCollection& other);

	StudentsCollection(StudentsCollection&& other) noexcept;
	StudentsCollection& operator=(StudentsCollection&& other) noexcept;

	~StudentsCollection();

	void addAtFirstFree(const Student& student);
	void addAtFirstFree(Student&& student);

	void setAtIdx(const Student& student, size_t idx);
	void setAtIdx(Student&& student, size_t idx);

	void removeAtIdx(size_t idx);

	bool containsAt(size_t idx) const;
	size_t getNumberInClass(const MyString& name) const;
};
