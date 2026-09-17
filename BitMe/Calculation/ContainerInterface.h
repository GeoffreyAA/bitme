#ifndef __CONTAINER_INTERFACE_H__
#define __CONTAINER_INTERFACE_H__

#include <stddef.h>

class ContainerInterface
{
public:
	virtual ~ContainerInterface();

	virtual const wchar_t *getName() const;
	virtual double getOverheadFull(double v, double a, double t) const;
	virtual double getOverheadNoAudio(double v, double t) const;
};

#endif