#ifndef __ASF_INTERFACE_H__
#define __ASF_INTERFACE_H__

#include "ContainerInterface.h"

class AsfInterface : public ContainerInterface
{
public:
	String getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif