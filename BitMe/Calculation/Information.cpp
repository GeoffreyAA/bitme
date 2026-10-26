#include "stdafx.h"
#include "Information.h"

DEC_CONST Decimal __2_pow_10  = DEC_LIT(1024.0);
DEC_CONST Decimal __2_pow_20  = DEC_LIT(1048576.0);
DEC_CONST Decimal __2_pow_30  = DEC_LIT(1073741824.0);
DEC_CONST Decimal __2_pow_40  = DEC_LIT(1099511627776.0);
DEC_CONST Decimal __2_pow_50  = DEC_LIT(1125899906842624.0);
DEC_CONST Decimal __2_pow_60  = DEC_LIT(1152921504606846976.0);
DEC_CONST Decimal __2_pow_70  = DEC_LIT(1180591620717411303424.0);
DEC_CONST Decimal __2_pow_80  = DEC_LIT(1208925819614629174706176.0);
DEC_CONST Decimal __2_pow_90  = DEC_LIT(1237940039285380274899124224.0);
DEC_CONST Decimal __2_pow_100 = DEC_LIT(1267650600228229401496703205376.0);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Information::Information(Decimal nBits) : bits(nBits)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Decimal Information::getBits() const
{
	return bits;
}

Decimal Information::getBytes() const
{
	return getBits() / DEC_LIT(8.0);
}

Decimal Information::getKB() const
{
	return getBytes() / __2_pow_10;
}

Decimal Information::getMB() const
{
	return getBytes() / __2_pow_20;
}

Decimal Information::getGB() const
{
	return getBytes() / __2_pow_30;
}

Decimal Information::getTB() const
{
	return getBytes() / __2_pow_40;
}

Decimal Information::getPB() const
{
	return getBytes() / __2_pow_50;
}

Decimal Information::getEB() const
{
	return getBytes() / __2_pow_60;
}

Decimal Information::getZB() const
{
	return getBytes() / __2_pow_70;
}

Decimal Information::getYB() const
{
	return getBytes() / __2_pow_80;
}

Decimal Information::getRB() const
{
	return getBytes() / __2_pow_90;
}

Decimal Information::getQB() const
{
	return getBytes() / __2_pow_100;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Information::setBits(Decimal x)
{
	bits = x;
}

void Information::setBytes(Decimal x)
{
	setBits(x * DEC_LIT(8.0));
}

void Information::setKB(Decimal x)
{
	setBytes(x * __2_pow_10);
}

void Information::setMB(Decimal x)
{
	setBytes(x * __2_pow_20);
}

void Information::setGB(Decimal x)
{
	setBytes(x * __2_pow_30);
}

void Information::setTB(Decimal x)
{
	setBytes(x * __2_pow_40);
}

void Information::setPB(Decimal x)
{
	setBytes(x * __2_pow_50);
}

void Information::setEB(Decimal x)
{
	setBytes(x * __2_pow_60);
}

void Information::setZB(Decimal x)
{
	setBytes(x * __2_pow_70);
}

void Information::setYB(Decimal x)
{
	setBytes(x * __2_pow_80);
}

void Information::setRB(Decimal x)
{
	setBytes(x * __2_pow_90);
}

void Information::setQB(Decimal x)
{
	setBytes(x * __2_pow_100);
}