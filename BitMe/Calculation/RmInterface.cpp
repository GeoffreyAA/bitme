#include "stdafx.h"
#include "RmInterface.h"

const wchar_t *RmInterface::getName() const
{
	return (L"RM");
}

double RmInterface::getOverheadFull(double v, double a, double t) const
{
	return (7376.0 * t);
}

double RmInterface::getOverheadNoAudio(double v, double t) const
{
	return (4136.0 * t);
}