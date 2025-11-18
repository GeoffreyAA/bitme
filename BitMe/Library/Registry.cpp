#include "stdafx.h"
#include "Registry.h"
#include "StrW.h"

Registry::Registry() : h(NULL)
{
}

Registry::Registry(HKEY hKey) : h(hKey)
{
}

Registry::Registry(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate) : h(NULL)
{
	open(pszSubKey, samDesired, bCreate);
}

Registry::Registry(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate) : h(NULL)
{
	open(hKey, pszSubKey, samDesired, bCreate);
}

Registry::~Registry()
{
	close();
}

bool Registry::open(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate)
{
	return (open(HKEY_CURRENT_USER, pszSubKey, samDesired, bCreate));
}

bool Registry::open(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate)
{
	if (close())
	{
		HKEY tmp;
		LONG lResult = bCreate ? RegCreateKeyExW(hKey, pszSubKey, 0, REG_NONE, REG_OPTION_NON_VOLATILE, samDesired, NULL, &tmp, NULL) :
								 RegOpenKeyExW(hKey, pszSubKey, 0, samDesired, &tmp);

		if (lResult == ERROR_SUCCESS)
		{
			h = tmp;

			return true;
		}
	}

	return false;
}

bool Registry::close()
{
	if (h)
	{
		if (RegCloseKey(h) == ERROR_SUCCESS)
		{
			h = NULL;
		}
	}

	return (h == NULL);
}

bool Registry::attach(HKEY hKey)
{
	if (!h)
	{
		if (hKey)
		{
			h = hKey;

			return true;
		}
	}

	return false;
}

HKEY Registry::detach()
{
	HKEY tmp = h;

	h = NULL;

	return (tmp);
}

int Registry::getInteger(const wchar_t *pszName, int nDefault) const
{
	if (isReady())
	{
		DWORD n;
		DWORD type;
		size_t size = sizeof(n);

		if ((RegQueryValueExW(getHandle(), pszName, NULL, &type, (LPBYTE)&n, (LPDWORD)&size) == ERROR_SUCCESS) && (type == REG_DWORD))
		{
			return (n);
		}
	}

	return (nDefault);
}

double Registry::getFloat(const wchar_t *pszName, double fDefault) const
{
	double x;

	return (getBinary(pszName, &x, sizeof(x)) ? x : fDefault);
}

bool Registry::getBool(const wchar_t *pszName, bool bDefault) const
{
	return (getInteger(pszName, bDefault) != 0);
}

char *Registry::getString(const wchar_t *pszName, char *pszBuffer, size_t cbSize) const
{
	wchar_t w[256];

	if (getString(pszName, w, sizeof(w) / sizeof(w[0])))
	{
		if (WideCharToMultiByte(CP_ACP, 0, w, -1, pszBuffer, cbSize * sizeof(char), NULL, NULL))
		{
			return (pszBuffer);
		}
	}

	return (NULL);
}

wchar_t *Registry::getString(const wchar_t *pszName, wchar_t *pszBuffer, size_t cbSize) const
{
	if (isReady())
	{
		DWORD type;
		size_t size = cbSize * sizeof(wchar_t);

		if ((RegQueryValueExW(getHandle(), pszName, NULL, &type, (LPBYTE)pszBuffer, (LPDWORD)&size) == ERROR_SUCCESS) && (type == REG_SZ))
		{
			return (pszBuffer);
		}
	}

	return (NULL);
}

void *Registry::getBinary(const wchar_t *pszName, void *pBuffer, size_t nBytes) const
{
	if (isReady())
	{
		DWORD type;

		if ((RegQueryValueExW(getHandle(), pszName, NULL, &type, (LPBYTE)pBuffer, (LPDWORD)&nBytes) == ERROR_SUCCESS) && (type == REG_BINARY))
		{
			return (pBuffer);
		}
	}

	return (NULL);
}

bool Registry::setInteger(const wchar_t *pszName, int nValue)
{
	if (isReady())
	{
		return (RegSetValueExW(getHandle(), pszName, 0, REG_DWORD, (const BYTE *)(&nValue), sizeof(nValue)) == ERROR_SUCCESS);
	}

	return false;
}

bool Registry::setFloat(const wchar_t *pszName, double fValue)
{
	return (setBinary(pszName, &fValue, sizeof(fValue)));
}

bool Registry::setBool(const wchar_t *pszName, bool bValue)
{
	return (setInteger(pszName, bValue));
}

bool Registry::setString(const wchar_t *pszName, const char *pszString)
{
	return (setString(pszName, StrW(pszString)));
}

bool Registry::setString(const wchar_t *pszName, const wchar_t *pszString)
{
	if (isReady())
	{
		return (RegSetValueExW(getHandle(), pszName, 0, REG_SZ, (const BYTE *)pszString, pszString ? ((wcslen(pszString) + 1) * sizeof(wchar_t)) : 0) == ERROR_SUCCESS);
	}

	return false;
}

bool Registry::setBinary(const wchar_t *pszName, const void *pData, size_t nBytes)
{
	if (isReady())
	{
		return (RegSetValueExW(getHandle(), pszName, 0, REG_BINARY, (const BYTE *)pData, nBytes) == ERROR_SUCCESS);
	}

	return false;
}

bool Registry::deleteValue(const wchar_t *pszName)
{
	if (isReady())
	{
		return (RegDeleteValueW(getHandle(), pszName) == ERROR_SUCCESS);
	}

	return false;
}

bool Registry::isReady() const
{
	return (getHandle() != NULL);
}

HKEY Registry::getHandle() const
{
	return (h);
}