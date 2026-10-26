#ifndef __CONFIG_CONCRETE_H__
#define __CONFIG_CONCRETE_H__

#include "Configuration.h"

class ConfigConcrete
{
public:
	ConfigConcrete();
	~ConfigConcrete();

	Configuration& Get();

private:
	ConfigConcrete(const ConfigConcrete &);
	ConfigConcrete& operator=(const ConfigConcrete &);

private:
	Configuration *pCfg;
};

#endif