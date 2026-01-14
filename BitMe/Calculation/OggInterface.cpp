#include "stdafx.h"
#include "OggInterface.h"

String OggInterface::getName() const
{
	return (L"OGV");
}
double OggInterface::getOverheadFull(double v, double a, double t) const
{
	return (64776.0 * t);
}

double OggInterface::getOverheadNoAudio(double v, double t) const
{
	return (98357.0 * t);
}