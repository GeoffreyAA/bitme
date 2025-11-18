#include "stdafx.h"
#include "Mp4Interface.h"

String Mp4Interface::getName() const
{
	return (L"MP4/MOV/3GP");
}
double Mp4Interface::getOverheadFull(double v, double a, double t) const
{
	return (4864.0 * t);
}

double Mp4Interface::getOverheadNoAudio(double v, double t) const
{
	return (3400.0 * t);
}