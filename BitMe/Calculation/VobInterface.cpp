#include "stdafx.h"
#include "VobInterface.h"

String VobInterface::getName() const
{
	return (L"VOB");
}

double VobInterface::getOverheadFull(double v, double a, double t) const
{
	return (25816.0 * t);
}

double VobInterface::getOverheadNoAudio(double v, double t) const
{
	return (22856.0 * t);
}