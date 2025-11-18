#include "stdafx.h"
#include "MpgInterface.h"

String MpgInterface::getName() const
{
	return (L"MPG");
}

double MpgInterface::getOverheadFull(double v, double a, double t) const
{
	return (10680.0 * t);
}

double MpgInterface::getOverheadNoAudio(double v, double t) const
{
	return (8856.0 * t);
}