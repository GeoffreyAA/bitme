#ifndef __OGG_INTERFACE_H__
#define __OGG_INTERFACE_H__

#include "ContainerInterface.h"

class OggInterface : public ContainerInterface
{
public:
	String getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif