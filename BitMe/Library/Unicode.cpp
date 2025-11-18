#include "stdafx.h"
#include "Unicode.h"
#include <windows.h>

bool ConvertUTF8To16(wchar_t *pszBuffer, size_t cbSize, const char *s)
{
	if (cbSize)
	{
		return (MultiByteToWideChar(CP_UTF8, 0, s, -1, pszBuffer, cbSize) != 0);
	}

	return false;
}

bool ConvertUTF16To8(char *pszBuffer, size_t cbSize, const wchar_t *s)
{
	if (cbSize)
	{
		return (WideCharToMultiByte(CP_UTF8, 0, s, -1, pszBuffer, cbSize, NULL, NULL) != 0);
	}

	return false;
}