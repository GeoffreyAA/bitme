#include "stdafx.h"
#include "MxfInterface.h"

String MxfInterface::getName() const
{
	return (L"MXF");
}

double MxfInterface::getOverheadFull(double v, double a, double t) const
{
	return (43464.0 * t);
}

double MxfInterface::getOverheadNoAudio(double v, double t) const
{
	return (35616.0 * t);
}