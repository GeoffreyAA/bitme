#include "stdafx.h"
#include "MtsInterface.h"

const wchar_t *MtsInterface::getName() const
{
	return (L"MPEG-TS");
}

double MtsInterface::getOverheadFull(double v, double a, double t) const
{
	return (76376.0 * t);
}

double MtsInterface::getOverheadNoAudio(double v, double t) const
{
	return (68800.0 * t);
}