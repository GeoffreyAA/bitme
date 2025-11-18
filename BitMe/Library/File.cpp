#include "stdafx.h"
#include "File.h"
#include <string.h>
#include <ctype.h>
#include <windows.h>

bool IsPathDelimiter(wchar_t c)
{
	return ((c == L'\\') || (c == L'/') || (c == L':'));
}

bool AppendString(wchar_t *pszDestination, const wchar_t *pszSource, size_t cbSize)
{
	if (pszDestination && pszSource)
	{
		const size_t a = wcslen(pszDestination);
		const size_t b = wcslen(pszSource);

		if ((a < cbSize) && (b < (cbSize - a)))
		{
			wcscpy(pszDestination + a, pszSource);

			return true;
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////

const wchar_t *GetFileName(const wchar_t *pszPath)
{
	if (pszPath)
	{
		size_t i = wcslen(pszPath);

		while (i--)
		{
			if (IsPathDelimiter(pszPath[i]))
			{
				return (pszPath + i + 1);
			}
		}
	}

	return (pszPath);
}

const wchar_t *GetFileExt(const wchar_t *pszPath)
{
	if (pszPath)
	{
		size_t i = wcslen(pszPath);

		while ((i--) && !IsPathDelimiter(pszPath[i]))
		{
			if (pszPath[i] == L'.')
			{
				return (pszPath + i + 1);
			}
		}
	}

	return (NULL);
}

bool GetRootFromPath(wchar_t *pszBuffer, size_t cbSize, const wchar_t *pszPath)
{
	if (pszPath && pszBuffer && (cbSize >= 3))
	{
		if (iswalpha(*pszPath))
		{
			*pszBuffer++ = *pszPath++;

			if (*pszPath == L':')
			{
				*pszBuffer++ = *pszPath;
				*pszBuffer = L'\0';

				return true;
			}
		}
	}

	return false;
}

wchar_t *RemovePath(wchar_t *pszPath)
{
	const wchar_t *p = GetFileName(pszPath);

	if (p)
	{
		memmove(pszPath, p, (wcslen(p) + 1) * sizeof(wchar_t));
	}

	return (pszPath);
}

wchar_t *RemoveFileName(wchar_t *pszPath)
{
	wchar_t *p = (wchar_t *)GetFileName(pszPath);

	if (p)
	{
		*p = L'\0';
	}

	return (pszPath);
}

wchar_t *RemoveFileExt(wchar_t *pszPath)
{
	if (pszPath)
	{
		size_t i = wcslen(pszPath);

		while ((i--) && !IsPathDelimiter(pszPath[i]))
		{
			if (pszPath[i] == L'.')
			{
				pszPath[i] = L'\0';

				return (pszPath);
			}
		}
	}

	return (pszPath);
}

bool AddFileName(wchar_t *pszPath, const wchar_t *pszFileName, size_t cbSize)
{
	if (pszPath && pszFileName)
	{
		const size_t a = wcslen(pszPath);

		if ((a > 0) && !IsPathDelimiter(pszPath[a - 1]))
		{
			if (!AppendString(pszPath, L"\\", cbSize))
				return false;
		}

		return (AppendString(pszPath, pszFileName, cbSize));
	}

	return false;
}

bool AddFileExt(wchar_t *pszPath, const wchar_t *pszFileExt, size_t cbSize)
{
	return (AppendString(pszPath, L".", cbSize) &&
			AppendString(pszPath, pszFileExt, cbSize));
}


///////////////////////////////////////////////////////////////

bool GetProgramPath(wchar_t *pszBuffer, size_t cbSize)
{
	if (pszBuffer && (cbSize > 0) && GetModuleFileNameW(NULL, pszBuffer, cbSize - 1))
	{
		pszBuffer[cbSize - 1] = L'\0';

		RemoveFileName(pszBuffer);

		return true;
	}

	return false;
}