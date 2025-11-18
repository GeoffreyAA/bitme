#include "stdafx.h"
#include "ContainerInterface.h"

ContainerInterface::~ContainerInterface()
{
}

String ContainerInterface::getName() const
{
	return (L"");
}

double ContainerInterface::getOverheadFull(double v, double a, double t) const
{
	return (0.0);
}

double ContainerInterface::getOverheadNoAudio(double v, double t) const
{
	return (0.0);
}