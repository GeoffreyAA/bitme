#include "stdafx.h"
#include "AviInterface.h"

String AviInterface::getName() const
{
	return (L"AVI");
}

double AviInterface::getOverheadFull(double v, double a, double t) const
{
	return (9699.0 * t);
}

double AviInterface::getOverheadNoAudio(double v, double t) const
{
	return (4897.0 * t);
}