#include "stdafx.h"
#include "M2tsInterface.h"

String M2tsInterface::getName() const
{
	return (L"M2TS");
}

double M2tsInterface::getOverheadFull(double v, double a, double t) const
{
	return (100144.0 * t);
}

double M2tsInterface::getOverheadNoAudio(double v, double t) const
{
	return (88872.0 * t);
}