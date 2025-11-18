#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <algorithm>
#include <stddef.h>
#include <assert.h>

template <class T, int n>
class array
{
public:
	typedef T value_type;
	typedef T * iterator;
	typedef const T * const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T * pointer;
	typedef ptrdiff_t difference_type;
	typedef int size_type;

	array()
	{
	}

	array(const T &val)
	{
		std::fill(begin(), end(), val);
	}

	template <class InputIterator>
	array(InputIterator x, InputIterator y)
	{
		assert(std::distance(x, y) <= size());

		std::copy(x, y, begin());
	}

	size_type size() const
	{
		return (n);
	}

	size_type max_size() const
	{
		return (n);
	}

	iterator begin()
	{
		return (a);
	}

	const_iterator begin() const
	{
		return (a);
	}

	iterator end()
	{
		return (a + n);
	}

	const_iterator end() const
	{
		return (a + n);
	}

	reference operator[](size_type i)
	{
		assert((0 <= i) && (i < size()));

		return (a[i]);
	}

	const_reference operator[](size_type i) const
	{
		assert((0 <= i) && (i < size()));

		return (a[i]);
	}

private:
	T a[n];
};

template <class T, int n>
bool operator==(const array<T, n> &x, const array<T, n> &y)
{
	return (std::equal(x.begin(), x.end(), y.begin()));
}

template <class T, int n>
bool operator!=(const array<T, n> &x, const array<T, n> &y)
{
	return !(x == y);
}

template <class T, int n>
bool operator<(const array<T, n> &x, const array<T, n> &y)
{
	return (std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template <class T, int n>
bool operator>(const array<T, n> &x, const array<T, n> &y)
{
	return (y < x);
}

template <class T, int n>
bool operator<=(const array<T, n> &x, const array<T, n> &y)
{
	return !(y < x);
}

template <class T, int n>
bool operator>=(const array<T, n> &x, const array<T, n> &y)
{
	return !(x < y);
}

#endif