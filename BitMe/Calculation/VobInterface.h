#ifndef __VOB_INTERFACE_H__
#define __VOB_INTERFACE_H__

#include "ContainerInterface.h"

class VobInterface : public ContainerInterface
{
public:
	String getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif