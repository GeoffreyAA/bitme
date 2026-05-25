#include "stdafx.h"
#include "Unicode.h"
#include <intsafe.h>
#include <windows.h>

bool ConvertUTF8To16(wchar_t *pszBuffer, size_t cbSize, const char *s)
{
	int size;

	if ((UIntPtrToInt(cbSize, &size) == S_OK) && (size > 0))
	{
		return MultiByteToWideChar(CP_UTF8, 0, s, -1, pszBuffer, size) != 0;
	}

	return false;
}

bool ConvertUTF16To8(char *pszBuffer, size_t cbSize, const wchar_t *s)
{
	int size;

	if ((UIntPtrToInt(cbSize, &size) == S_OK) && (size > 0))
	{
		return WideCharToMultiByte(CP_UTF8, 0, s, -1, pszBuffer, size, NULL, NULL) != 0;
	}

	return false;
}