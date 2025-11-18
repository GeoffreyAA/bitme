#include "stdafx.h"
#include "Settings.h"

Settings_t::Settings_t()// : bUseOverhead(true), sContainerName(L"AVI")
{
}

bool SettingsLoad(Settings_t *pSettings, const Configuration *c)
{
	if (pSettings && c)
	{
		//wchar_t w[32];
		Settings_t d;

		//pSettings->bUseOverhead = c->getBool(L"bUseOverhead", d.bUseOverhead);
		//pSettings->sContainerName = c->getString(L"sContainerName", w, sizeof(w) / sizeof(w[0])) ? w : d.sContainerName;

		return true;
	}

	return false;
}

bool SettingsExport(const Settings_t *pSettings, Configuration *c)
{
	if (pSettings && c)
	{
		bool b;

		//b = c->setBool(L"bUseOverhead", pSettings->bUseOverhead);
		//b = c->setString(L"sContainerName", pSettings->sContainerName.c_str());

		return (b);
	}

	return false;
}