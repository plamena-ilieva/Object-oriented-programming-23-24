#include <iostream>
#include <assert.h>

struct Rational {
	int num;
	int denom;
};

bool isValid(const Rational& rat) {
	return rat.denom != 0;
}

unsigned findGcd(unsigned a, unsigned b) {
	if (a < b) {
		std::swap(a, b);
	}

	while (b != 0) {
		unsigned temp = a % b;
		a = b;
		b = temp;
	}

	return a;
}

void simplify(Rational& rat) {
	assert(isValid(rat));

	unsigned gcd = findGcd(rat.num, rat.denom);

	rat.num /= gcd;
	rat.denom /= gcd;
}

Rational& sumEq(Rational& lhs, const Rational& rhs) {
	assert(isValid(lhs) && isValid(rhs));

	lhs.num = lhs.num * rhs.denom + rhs.num * lhs.denom;
	lhs.denom = lhs.denom * rhs.denom;
	simplify(lhs);

	return lhs;
}

Rational sum(const Rational& lhs, const Rational& rhs) {
	assert(isValid(lhs) && isValid(rhs));
	
	Rational res = lhs;
	sumEq(res, rhs);
	return res;
}

void print(const Rational& rat)
{
	std::cout << rat.num << "/" << rat.denom << std::endl;
}

int main()
{
	Rational r1{ 1,4 };
	Rational r2{ 1,3 };

	Rational r3 = sum(r1, r2);

	print(r3);

	Rational r4{ 2,3 };
	sumEq(sumEq(r3, r1), r4);

	print(r3);
}