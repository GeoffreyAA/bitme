#include "stdafx.h"
#include "Registry.h"
#include "StrW.h"
#include "Unicode.h"
#include <intsafe.h>

Registry::Registry() : h(NULL)
{
}

Registry::Registry(HKEY hKey) : h(hKey)
{
}

Registry::Registry(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate) : h(NULL)
{
	Open(pszSubKey, samDesired, bCreate);
}

Registry::Registry(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate) : h(NULL)
{
	Open(hKey, pszSubKey, samDesired, bCreate);
}

Registry::~Registry()
{
	Close();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Registry::Open(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate)
{
	return Open(HKEY_CURRENT_USER, pszSubKey, samDesired, bCreate);
}

bool Registry::Open(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate)
{
	if (Close())
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

bool Registry::Close()
{
	if (h)
	{
		if (RegCloseKey(h) == ERROR_SUCCESS)
		{
			h = NULL;
		}
	}

	return h == NULL;
}

bool Registry::Attach(HKEY hKey)
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

HKEY Registry::Detach()
{
	HKEY tmp = h;

	h = NULL;

	return tmp;
}

bool Registry::IsReady() const
{
	return GetHandle() != NULL;
}

HKEY Registry::GetHandle() const
{
	return h;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Registry::GetInt(const wchar_t *name, int &value) const
{
	if (IsReady())
	{
		DWORD n, type;
		DWORD size = sizeof(n);

		if ((RegQueryValueExW(GetHandle(), name, NULL, &type, (LPBYTE)&n, &size) == ERROR_SUCCESS) && (type == REG_DWORD))
		{
			value = n;
			return true;
		}
	}

	return false;
}

bool Registry::GetFloat(const wchar_t *name, double &value) const
{
	double x;

	if (GetBinary(name, &x, sizeof(x)))
	{
		value = x;
		return true;
	}

	return false;
}

bool Registry::GetBool(const wchar_t *name, bool &value) const
{
	int n;

	if (GetInt(name, n))
	{
		value = (n != 0);
		return true;
	}

	return false;
}

bool Registry::GetString(const wchar_t *name, char *value, size_t size) const
{
	wchar_t w[256];

	if (GetString(name, w, sizeof(w) / sizeof(w[0])))
		return ConvertUTF16To8(value, size, w);

	return false;
}

bool Registry::GetString(const wchar_t *name, wchar_t *value, size_t size) const
{
	if (IsReady())
	{
		size_t st_bytes;
		DWORD bytes, type;

		if ((SizeTMult(size, sizeof(wchar_t), &st_bytes) == S_OK) &&
			(SIZETToDWord(st_bytes, &bytes) == S_OK))
		{
			if ((RegQueryValueExW(GetHandle(), name, NULL, &type, (LPBYTE)value, &bytes) == ERROR_SUCCESS) && (type == REG_SZ))
			{
				return true;
			}
		}
	}

	return false;
}

bool Registry::GetString(const wchar_t *name, String &value) const
{
	return false;
}

bool Registry::GetBinary(const wchar_t *name, void *value, size_t bytes) const
{
	if (IsReady())
	{
		DWORD dw_bytes, type;

		if (SIZETToDWord(bytes, &dw_bytes) == S_OK)
		{
			if ((RegQueryValueExW(GetHandle(), name, NULL, &type, (LPBYTE)value, &dw_bytes) == ERROR_SUCCESS) && (type == REG_BINARY))
			{
				return true;
			}
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Registry::SetInt(const wchar_t *name, int value)
{
	if (IsReady())
		return RegSetValueExW(GetHandle(), name, 0, REG_DWORD, (const BYTE *)&value, sizeof(value)) == ERROR_SUCCESS;

	return false;
}

bool Registry::SetFloat(const wchar_t *name, double value)
{
	return SetBinary(name, &value, sizeof(value));
}

bool Registry::SetBool(const wchar_t *name, bool value)
{
	return SetInt(name, value);
}

bool Registry::SetString(const wchar_t *name, const char *value)
{
	return SetString(name, StrW(value));
}

bool Registry::SetString(const wchar_t *name, const wchar_t *value)
{
	if (IsReady())
	{
		size_t st_bytes;
		DWORD dw_bytes;

		if ((SizeTMult(value ? (wcslen(value) + 1) : 0, sizeof(wchar_t), &st_bytes) == S_OK) &&
			(SIZETToDWord(st_bytes, &dw_bytes) == S_OK))
		{
			return RegSetValueExW(GetHandle(), name, 0, REG_SZ, (const BYTE *)value, dw_bytes) == ERROR_SUCCESS;
		}
	}

	return false;
}

bool Registry::SetString(const wchar_t *name, const String &value)
{
	return false;
}

bool Registry::SetBinary(const wchar_t *name, const void *value, size_t bytes)
{
	if (IsReady())
	{
		DWORD dw_bytes;

		if (SIZETToDWord(bytes, &dw_bytes) == S_OK)
		{
			return RegSetValueExW(GetHandle(), name, 0, REG_BINARY, (const BYTE *)value, dw_bytes) == ERROR_SUCCESS;
		}
	}

	return false;
}

bool Registry::Delete(const wchar_t *name)
{
	if (IsReady())
	{
		return RegDeleteValueW(GetHandle(), name) == ERROR_SUCCESS;
	}

	return false;
}