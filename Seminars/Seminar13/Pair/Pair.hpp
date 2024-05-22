#include <iostream>

template <class T, class D>
class Pair {
	T lhs;
	D rhs;
public:
	Pair() = default;
	Pair(const T& lhs, const D& rhs);

	const T& getLhs() const;
	const D& getRhs() const;

	void setLhs(const T& lhs);
	void setRhs(const D& rhs);

};

template<class T, class D>
Pair<T, D>::Pair<T, D>(const T& lhs, const D& rhs) : lhs(lhs), rhs(rhs)
{
	
}

template<class T, class D>
const T& Pair<T, D>::getLhs() const {
	return lhs;
}

template<class T, class D>
const D& Pair<T, D>::getRhs() const {
	return rhs;
}

template<class T, class D>
void Pair<T, D>::setLhs(const T& lhs)
{
	this->lhs = lhs;
}

template<class T, class D>
void Pair<T, D>::setRhs(const D& rhs)
{
	this->rhs = rhs;
}

template<class T, class D>
std::ostream& operator<<(std::ostream& os, const Pair<T, D>& pair) {
	os << pair.getLhs() << ' ' << pair.getRhs() << std::endl;
	return os;
}