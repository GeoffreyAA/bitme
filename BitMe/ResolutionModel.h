#ifndef __RESOLUTION_MODEL_H__
#define __RESOLUTION_MODEL_H__

class ResolutionModel
{
public:
	ResolutionModel(double w = 1920.0, double ax = 16.0, double ay = 9.0, bool br = false, double rv = 16.0);

	double getWidth() const;
	double getHeight() const;
	double getAspectX() const;
	double getAspectY() const;

	void setWidth(double x);
	void setHeight(double x);
	void setAspectX(double x);
	void setAspectY(double x);

	void enableRounding(bool b);
	void setRoundingValue(double x);
	bool isRoundingEnabled() const;
	double getRoundingValue() const;

private:
	double Width;
	double AspectX;
	double AspectY;
	bool bRounding;
	double r;
};

#endif