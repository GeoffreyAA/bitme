#include "stdafx.h"
#include "Name.h"
#include "Application.h"
#include "Library\Compiler.h"
#include "Library\Library.h"
#include "Library\ResourceString.h"
#include "Library\Win32Library.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

wchar_t *GetApplicationNameFull(wchar_t *c, size_t cbSize)
{
	if (c)
	{
		swprintfs(c, cbSize, L"%s %s (%s %d) (%s)"

#ifdef _DEBUG
							 L" (Debug)"
#endif
							 , GetApplicationName()
							 , GetApplicationVersion()
							 , ResourceString(L"IDS_BUILD").c_str()
							 , GetBuildNumber()
							 , GetPlatform());
	}

	return c;
}

String GetApplicationNameFull()
{
	wchar_t w[128];

	GetApplicationNameFull(w, sizeof(w) / sizeof(w[0]));

	return w;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

wchar_t *GetApplicationNameEx(wchar_t *c, size_t cbSize)
{
	if (c)
	{
		// Convert time_t to local time, then format it according to Windows settings:

		wchar_t d[128];
		SYSTEMTIME st;

		if (!TimeToSystemTimeLocal(GetBuildTime(), &st) || !GetDateTimeFormatted(d, sizeof(d) / sizeof(d[0]), &st))
		{
			wcscpys(d, ResourceString(L"IDS_ERROR"), sizeof(d) / sizeof(d[0]));
		}

		// Put together name string painstakingly:

		swprintfs(c, cbSize, L"%s\n"
							 L"%s %s (%s %d) (%s) (%s)"
#ifdef _DEBUG
							 L" (Debug)"
#endif
							 L"\n%s. %s.\n\n"
							 L"%s %s\n\n"
							 L"%s",

							 GetApplicationName(),
							 ResourceString(L"IDS_VERSION").c_str(),
							 GetApplicationVersion(),
							 ResourceString(L"IDS_BUILD").c_str(),
							 GetBuildNumber(),
							 GetPlatform(),
							 GetCompilerVersion().c_str(),
							 GetCopyright(),
							 ResourceString(L"IDS_ALL_RIGHTS_RESERVED").c_str(),
							 ResourceString(L"IDS_COMPILED_ON").c_str(), d,
							 ResourceString(L"IDS_LICENCE").c_str());
	}

	return c;
}

String GetApplicationNameEx()
{
	wchar_t w[1024];

	GetApplicationNameEx(w, sizeof(w) / sizeof(w[0]));

	return w;
}