#ifndef __TEMPLATES_H__
#define __TEMPLATES_H__

template <class InputIterator>
void DeleteAll(InputIterator a, InputIterator b)
{
	while (a != b)
	{
		if (*a)
		{
			delete *a;
		}

		a++;
	}
}

template <class T>
bool InRange(const T &Min, const T &Max, const T &Value)
{
	return ((Min <= Value) && (Value <= Max));
}

template <class T>
const T& ClampMin(const T &Min, const T &Value)
{
	return ((Value < Min) ? Min : Value);
}

template <class T>
const T& ClampMax(const T &Max, const T &Value)
{
	return ((Value > Max) ? Max : Value);
}

template <class T>
const T& Clamp(const T &Min, const T &Max, const T &Value)
{
	return ((Value < Min) ? Min : ((Value > Max) ? Max : Value));
}

// I first learned how to convert an integer to a bool from
// VirtualDub's source code.

template <class T>
bool ToBool(const T &x)
{
	return (x != 0);
}

template <class T>
const T& Min(const T &x, const T &y)
{
	return ((x < y) ? x : y);
}

template <class T>
const T& Max(const T &x, const T &y)
{
	return ((x > y) ? x : y);
}

#endif