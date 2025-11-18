#ifndef __MXF_INTERFACE_H__
#define __MXF_INTERFACE_H__

#include "ContainerInterface.h"

class MxfInterface : public ContainerInterface
{
public:
	String getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif