#include "stdafx.h"
#include "Application.h"
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
		swprintfs(c, cbSize, L"BitMe %s (%s %d) (%s)"		// Fixes ampersand not showing up in text label, owing to Windows thinking it's an accelerator

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
	wchar_t w[64];

	GetApplicationNameFull(w, sizeof(w) / sizeof(w[0]));

	return (w);
}

String GetApplicationNameFull2()
{
	wchar_t w[64];

	GetApplicationNameFull2(w, sizeof(w) / sizeof(w[0]));

	return (w);
}

const wchar_t *GetApplicationVersion()
{
	return (L"3.3");
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
	//return (L"BitMe.chm");

	return (L"Readme.txt");
}

const wchar_t *GetCompilerName()
{
	return (

#if _MSC_VER >= 1930
		L"Visual Studio 2022"

#elif _MSC_VER >= 1920
		L"Visual Studio 2019"

#elif _MSC_VER >= 1910
		L"Visual Studio 2017"

#elif _MSC_VER >= 1900
		L"Visual Studio 2015"

#elif _MSC_VER >= 1800
		L"Visual Studio 2013"

#elif _MSC_VER >= 1700
		L"Visual Studio 2012"

#elif _MSC_VER >= 1600
		L"Visual Studio 2010"

#elif _MSC_VER >= 1500
		L"Visual Studio 2008"

#elif _MSC_VER >= 1400
		L"Visual Studio 2005"

#elif _MSC_VER >= 1310
		L"Visual Studio .NET 2003"

#elif _MSC_VER >= 1300
		L"Visual Studio .NET 2002"

#elif _MSC_VER >= 1200
		L"Visual C++ 6.0"

#else
		L"N/A"

#endif

		);
}

String GetCompilerVersion()
{
	wchar_t w[64] = L"N/A";

#ifdef _MSC_VER
	swprintfs(w, sizeof(w) / sizeof(w[0]), L"MSVC %d", _MSC_VER);
#endif

	return (w);
}

String GetCompilerVersionFull()
{
	wchar_t w[64] = L"N/A";

#ifdef _MSC_VER
	swprintfs(w, sizeof(w) / sizeof(w[0]), L"MSVC %d", _MSC_FULL_VER);
#endif

	return (w);
}

const wchar_t *GetPlatform()
{
#ifdef _M_IX86
	return (L"x86");
#endif

#ifdef _M_AMD64
	return (L"x64");
#endif

#ifdef _M_ARM
	return (L"ARM");
#endif

	return (L"N/A");
}