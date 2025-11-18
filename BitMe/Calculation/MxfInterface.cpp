#include "stdafx.h"
#include "MxfInterface.h"

String MxfInterface::getName() const
{
	return (L"MXF");
}

double MxfInterface::getOverheadFull(double v, double a, double t) const
{
	return (182848.0 * t);
}

double MxfInterface::getOverheadNoAudio(double v, double t) const
{
	return (164400.0 * t);
}