#include "stdafx.h"
#include "Application.h"
#include "Library\Compiler.h"
#include "Library\Library.h"
#include "Library\ResourceString.h"

extern "C" const int build_number;
extern "C" const time_t build_time;

const wchar_t *GetApplicationName()
{
	return (L"BitMe");
}

wchar_t *GetApplicationNameFull(wchar_t *c, size_t cbSize)
{
	if (c)
	{
		swprintfs(c, cbSize, L"BitMe %s (%s %d) (%s)"

#ifdef _DEBUG
							 L" (Debug)"
#endif

							 , GetApplicationVersion()
							 , ResourceString(L"IDS_BUILD").c_str()
							 , GetBuildNumber()
							 , GetPlatform());
	}

	return (c);
}

wchar_t *GetApplicationNameFull2(wchar_t *c, size_t cbSize)
{
	if (c)
	{
		swprintfs(c, cbSize, L"BitMe\n%s %s (%s %d) (%s) (%s)"

#ifdef _DEBUG
							 L" (Debug)"
#endif

							 , ResourceString(L"IDS_VERSION").c_str()
							 , GetApplicationVersion()
							 , ResourceString(L"IDS_BUILD").c_str()
							 , GetBuildNumber()
							 , GetPlatform()
							 , GetCompilerVersion().c_str());
	}

	return (c);
}

String GetApplicationNameFull()
{
	wchar_t w[128];

	GetApplicationNameFull(w, sizeof(w) / sizeof(w[0]));

	return (w);
}

String GetApplicationNameFull2()
{
	wchar_t w[128];

	GetApplicationNameFull2(w, sizeof(w) / sizeof(w[0]));

	return (w);
}

const wchar_t *GetApplicationVersion()
{
	return (L"3.5");
}

int GetBuildNumber()
{
	return (build_number);
}

time_t GetBuildTime()
{
	return (build_time);
}

const wchar_t *GetRegistryKey()
{
	return (L"Software\\BitMe");
}

const wchar_t *GetHelpFileName()
{
	return (L"Readme.txt");
}