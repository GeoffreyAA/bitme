#ifndef __INFORMATION_H__
#define __INFORMATION_H__

#include "..\Library\Decimal.h"

class Information
{
public:
	Information(Decimal nBits = DEC_LIT(0.0));

	Decimal getBits() const;
	Decimal getBytes() const;
	Decimal getKB() const;
	Decimal getMB() const;
	Decimal getGB() const;
	Decimal getTB() const;
	Decimal getPB() const;
	Decimal getEB() const;
	Decimal getZB() const;
	Decimal getYB() const;
	Decimal getRB() const;
	Decimal getQB() const;

	void setBits(Decimal x);
	void setBytes(Decimal x);
	void setKB(Decimal x);
	void setMB(Decimal x);
	void setGB(Decimal x);
	void setTB(Decimal x);
	void setPB(Decimal x);
	void setEB(Decimal x);
	void setZB(Decimal x);
	void setYB(Decimal x);
	void setRB(Decimal x);
	void setQB(Decimal x);

private:
	Decimal bits;
};

#endif