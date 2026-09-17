#ifndef __TEST_INTERFACE_H__
#define __TEST_INTERFACE_H__

#include "ContainerInterface.h"

class TestInterface : public ContainerInterface
{
public:
	const wchar_t *getName() const;
	double getOverheadFull(double v, double a, double t) const;
	double getOverheadNoAudio(double v, double t) const;
};

#endif