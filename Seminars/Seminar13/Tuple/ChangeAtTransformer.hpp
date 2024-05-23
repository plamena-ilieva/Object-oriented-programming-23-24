#include "Transformer.hpp"

#define TT template<typename T, size_t N>

TT
class ChangeAtTransformer : public Transformer<T, N>
{
private:
	T element;
	size_t index = 0;

public:
	ChangeAtTransformer(size_t index, const T& element);

	Tuple<T, N>& transform(Tuple<T, N>& tuple) const override;

	Transformer<T, N>* clone() const override;
};

TT
ChangeAtTransformer<T, N>::ChangeAtTransformer(size_t index, const T& element)
	: Transformer<T, N>(), element(element), index(index) {}

TT
Tuple<T, N>& ChangeAtTransformer<T, N>::transform(Tuple<T, N>& tuple) const
{
	if (index >= tuple.getSize()) return tuple;

	tuple[index] = element;
	return tuple;
}

TT
Transformer<T, N>* ChangeAtTransformer<T, N>::clone() const
{
	return new ChangeAtTransformer(*this);
}