#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "Library\Configuration.h"
//#include "Library\String.h"

struct Settings_t
{
	Settings_t();

	//bool bUseOverhead;
	//String sContainerName;
};

bool SettingsLoad(Settings_t *pSettings, const Configuration *c);
bool SettingsExport(const Settings_t *pSettings, Configuration *c);

#endif