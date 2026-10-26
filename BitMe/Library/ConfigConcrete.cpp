#include "stdafx.h"
#include "ConfigConcrete.h"
#include "ConfigFile.h"
#include "Registry.h"
#include "..\Application.h"

ConfigConcrete::ConfigConcrete()
{
	if (IsApplicationPortable())
		pCfg = new ConfigFile;
	else
		pCfg = new Registry(GetRegistryKey(), KEY_READ | KEY_WRITE, true);
}

ConfigConcrete::~ConfigConcrete()
{
	delete pCfg;
}

Configuration& ConfigConcrete::Get()
{
	return *pCfg;
}