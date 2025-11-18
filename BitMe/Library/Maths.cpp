#include "stdafx.h"
#include "Maths.h"

// The logic for this function (or its idea) is essentially
// from the VirtualDub source code. There are VDRoundToInt
// and some others.

int Round(double x)
{
	return (int)(x + 0.5);
}

double RoundToMultiple(double x, double m)
{
	return (m * Round(x / m));
}

int DigitCount(int x)
{
	if (!x)
		return (1);

	int n = 0;

	while (x > 0)
	{
		n++;
		x /= 10;
	}

	return (n);
}

int DigitCountU(unsigned int x)
{
	if (!x)
		return (1);

	int n = 0;

	while (x > 0)
	{
		n++;
		x /= 10;
	}

	return (n);
}