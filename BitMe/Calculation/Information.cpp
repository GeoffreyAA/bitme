#include "stdafx.h"
#include "Information.h"

const double __2_pow_10 = 1024.0;
const double __2_pow_20 = 1048576.0;
const double __2_pow_30 = 1073741824.0;
const double __2_pow_40 = 1099511627776.0;
const double __2_pow_50 = 1125899906842624.0;
const double __2_pow_60 = 1152921504606846976.0;
const double __2_pow_70 = 1180591620717411303424.0;
const double __2_pow_80 = 1208925819614629174706176.0;


///////////////////////////////////////////////////////////////

Information::Information(double nBits) : bits(nBits)
{
}


///////////////////////////////////////////////////////////////

double Information::getBits() const
{
	return (bits);
}

double Information::getBytes() const
{
	return (getBits() / 8.0);
}

double Information::getKB() const
{
	return (getBytes() / __2_pow_10);
}

double Information::getMB() const
{
	return (getBytes() / __2_pow_20);
}

double Information::getGB() const
{
	return (getBytes() / __2_pow_30);
}

double Information::getTB() const
{
	return (getBytes() / __2_pow_40);
}

double Information::getPB() const
{
	return (getBytes() / __2_pow_50);
}

double Information::getEB() const
{
	return (getBytes() / __2_pow_60);
}

double Information::getZB() const
{
	return (getBytes() / __2_pow_70);
}

double Information::getYB() const
{
	return (getBytes() / __2_pow_80);
}


///////////////////////////////////////////////////////////////

void Information::setBits(double x)
{
	bits = x;
}

void Information::setBytes(double x)
{
	setBits(x * 8.0);
}

void Information::setKB(double x)
{
	setBytes(x * __2_pow_10);
}

void Information::setMB(double x)
{
	setBytes(x * __2_pow_20);
}

void Information::setGB(double x)
{
	setBytes(x * __2_pow_30);
}

void Information::setTB(double x)
{
	setBytes(x * __2_pow_40);
}

void Information::setPB(double x)
{
	setBytes(x * __2_pow_50);
}

void Information::setEB(double x)
{
	setBytes(x * __2_pow_60);
}

void Information::setZB(double x)
{
	setBytes(x * __2_pow_70);
}

void Information::setYB(double x)
{
	setBytes(x * __2_pow_80);
}