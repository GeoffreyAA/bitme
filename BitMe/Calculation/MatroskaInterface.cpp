#include "stdafx.h"
#include "MatroskaInterface.h"

String MatroskaInterface::getName() const
{
	return (L"Matroska/WebM");
}

double MatroskaInterface::getOverheadFull(double v, double a, double t) const
{
	return (2776.0 * t);
}

double MatroskaInterface::getOverheadNoAudio(double v, double t) const
{
	return (2472.0 * t);
}