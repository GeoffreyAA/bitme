#include "stdafx.h"
#include "AsfInterface.h"

String AsfInterface::getName() const
{
	return (L"ASF/WMV");
}

double AsfInterface::getOverheadFull(double v, double a, double t) const
{
	return (25104.0 * t);
}

double AsfInterface::getOverheadNoAudio(double v, double t) const
{
	return (12072.0 * t);
}