#include "stdafx.h"
#include "Compiler.h"
#include "Library.h"

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

const wchar_t *GetCompilerName()
{
	return (

#if _MSC_VER >= 9999
		L"Visual Studio 2026"

#elif _MSC_VER >= 1930
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

#ifdef _MSC_FULL_VER
	swprintfs(w, sizeof(w) / sizeof(w[0]), L"MSVC %d", _MSC_FULL_VER);
#endif

	return (w);
}