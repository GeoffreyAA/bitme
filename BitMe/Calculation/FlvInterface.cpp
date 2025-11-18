#include "stdafx.h"
#include "FlvInterface.h"

String FlvInterface::getName() const
{
	return (L"FLV");
}

double FlvInterface::getOverheadFull(double v, double a, double t) const
{
	return (8256.0 * t);
}

double FlvInterface::getOverheadNoAudio(double v, double t) const
{
	return (4344.0 * t);
}