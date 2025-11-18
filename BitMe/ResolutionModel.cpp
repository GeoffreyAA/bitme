#include "stdafx.h"
#include "ResolutionModel.h"
#include "Library\Maths.h"

ResolutionModel::ResolutionModel(double w, double ax, double ay, bool br, double rv) : Width(w), AspectX(ax), AspectY(ay), bRounding(br), r(rv)
{
}

double ResolutionModel::getWidth() const
{
	return (isRoundingEnabled() ? RoundToMultiple(Width, getRoundingValue()) : Width);
}

double ResolutionModel::getHeight() const
{
	double h = getWidth() * getAspectY() / getAspectX();

	return (isRoundingEnabled() ? RoundToMultiple(h, getRoundingValue()) : h);
}

double ResolutionModel::getAspectX() const
{
	return (AspectX);
}

double ResolutionModel::getAspectY() const
{
	return (AspectY);
}

void ResolutionModel::setWidth(double x)
{
	Width = x;
}

void ResolutionModel::setHeight(double x)
{
	setWidth(x * getAspectX() / getAspectY());
}

void ResolutionModel::setAspectX(double x)
{
	AspectX = x;
}

void ResolutionModel::setAspectY(double x)
{
	AspectY = x;
}

void ResolutionModel::enableRounding(bool b)
{
	bRounding = b;
}

void ResolutionModel::setRoundingValue(double x)
{
	r = x;
}

bool ResolutionModel::isRoundingEnabled() const
{
	return (bRounding);
}

double ResolutionModel::getRoundingValue() const
{
	return (r);
}