#include "Transformer.hpp"

#define TT template<typename T, size_t N>

TT
class AllTransformer : public Transformer<T, N>
{
private:
	T* data = nullptr;
	size_t size = 0;

	void copyFrom(const AllTransformer& other);
	void moveFrom(AllTransformer&& other) noexcept;
	void free();

public:
	AllTransformer(const T* data, size_t size);

	AllTransformer(const AllTransformer& other);
	AllTransformer& operator=(const AllTransformer& other);

	AllTransformer(AllTransformer&& other) noexcept;
	AllTransformer& operator=(AllTransformer&& other) noexcept;

	const size_t getSize() const;

	Tuple<T, N>& transform(Tuple<T, N>& tuple) const override;

	Transformer<T, N>* clone() const override;

	~AllTransformer() noexcept;
};

TT
AllTransformer<T, N>::AllTransformer(const T* data, size_t size) : Transformer<T, N>()
{
	if (!data) return;

	this->size = size;

	this->data = new T[this->size];
	for (size_t i = 0; i < getSize(); i++)
		this->data[i] = data[i];
}

TT
AllTransformer<T, N>::AllTransformer(const AllTransformer<T, N>& other) : Transformer<T, N>(other)
{
	copyFrom(other);
}

TT
AllTransformer<T, N>& AllTransformer<T, N>::operator=(const AllTransformer<T, N>& other)
{
	if (this != &other)
	{
		Transformer<T, N>::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

TT
AllTransformer<T, N>::AllTransformer(AllTransformer<T, N>&& other) noexcept : Transformer<T, N>(std::move(other))
{
	moveFrom(std::move(other));
}

TT
AllTransformer<T, N>& AllTransformer<T, N>::operator=(AllTransformer<T, N>&& other) noexcept
{
	if (this != &other)
	{
		Transformer<T, N>::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const size_t AllTransformer<T, N>::getSize() const
{
	return this->size;
}

TT
Tuple<T, N>& AllTransformer<T, N>::transform(Tuple<T, N>& tuple) const
{
	for (size_t i = 0; i < getSize(); i++)
	{
		if (i >= tuple.getSize()) // the same as i >= N
			return tuple;

		tuple[i] = this->data[i];
	}

	return tuple;
}

TT
Transformer<T, N>* AllTransformer<T, N>::clone() const
{
	return new AllTransformer(*this);
}

TT
AllTransformer<T, N>::~AllTransformer() noexcept
{
	free();
}

TT
void AllTransformer<T, N>::copyFrom(const AllTransformer<T, N>& other)
{
	this->size = other.size;

	this->data = new T[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->data[i] = other.data[i];
}

TT
void AllTransformer<T, N>::moveFrom(AllTransformer<T, N>&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;

	other.data = nullptr;
	other.size = 0;
}

TT
void AllTransformer<T, N>::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = 0;
}
