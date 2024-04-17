#pragma once

struct A {
	int a;
	int b;
};

class UniquePtrOfA {
	A* ptr;

	void free();
	void moveFrom(UniquePtrOfA&& other);

public:
	UniquePtrOfA(A* ptr);

	UniquePtrOfA(UniquePtrOfA&& other) noexcept;
	UniquePtrOfA& operator=(UniquePtrOfA&& other) noexcept;

	UniquePtrOfA(const UniquePtrOfA& other) = delete;
	UniquePtrOfA& operator=(const UniquePtrOfA& other) = delete;

	~UniquePtrOfA();

	const A& operator*() const;
	A& operator*();
};

