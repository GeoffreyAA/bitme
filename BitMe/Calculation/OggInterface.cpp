#include "stdafx.h"
#include "OggInterface.h"

String OggInterface::getName() const
{
	return (L"OGG");
}
double OggInterface::getOverheadFull(double v, double a, double t) const
{
	return (11528.0 * t);
}

double OggInterface::getOverheadNoAudio(double v, double t) const
{
	return (11528.0 * t);
}