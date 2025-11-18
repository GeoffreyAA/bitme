#ifndef __M2TS_INTERFACE_H__
#define __M2TS_INTERFACE_H__

#include "ContainerInterface.h"

class M2tsInterface : public ContainerInterface
{
public:
	String getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif