#include "stdafx.h"
#include "TestInterface.h"

String TestInterface::getName() const
{
	return (L"== Test ==");
}
double TestInterface::getOverheadFull(double v, double a, double t) const
{
	return (5824.0 * t);
}

double TestInterface::getOverheadNoAudio(double v, double t) const
{
	return (3400.0 * t);
}