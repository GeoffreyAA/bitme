#ifndef __INFORMATION_H__
#define __INFORMATION_H__

class Information
{
public:
	Information(double nBits = 0.0);

	double getBits() const;
	double getBytes() const;
	double getKB() const;
	double getMB() const;
	double getGB() const;
	double getTB() const;
	double getPB() const;
	double getEB() const;
	double getZB() const;
	double getYB() const;

	void setBits(double x);
	void setBytes(double x);
	void setKB(double x);
	void setMB(double x);
	void setGB(double x);
	void setTB(double x);
	void setPB(double x);
	void setEB(double x);
	void setZB(double x);
	void setYB(double x);

private:
	double bits;
};

#endif