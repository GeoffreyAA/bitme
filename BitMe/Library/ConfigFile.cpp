#include "stdafx.h"
#include "ConfigFile.h"
#include "Library.h"
#include "StrW.h"
#include "Unicode.h"
#include "Win32Library.h"
#include <wchar.h>

ConfigFile::ConfigFile(const wchar_t *file) : write(false)
{
	ApplicationFile path(file);

	if (path.c_str())
	{
		fn = path.c_str();

		if (!StringDictionaryRead(path, d))
			d.clear();
	}
}

ConfigFile::~ConfigFile()
{
	if (write)
		StringDictionaryWrite(fn.c_str(), d);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ConfigFile::get(const wchar_t *name, String &value) const
{
	if (name)
	{
		StringDictionary::const_iterator i = d.find(name);

		if (i != d.end())
		{
			value = (*i).second;

			return true;
		}
	}

	return false;
}

bool ConfigFile::put(const wchar_t *name, const wchar_t *value)
{
	if (name && value)
	{
		d.erase(name);
		d.insert(StringDictionary::value_type(name, value));

		write = true;

		return true;
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ConfigFile::GetInt(const wchar_t *name, int &value) const
{
	String s;

	if (get(name, s))
	{
		if (IsNumber(s.c_str()))
		{
			value = wcstol(s.c_str(), NULL, 10);
			return true;
		}
	}

	return false;
}

bool ConfigFile::GetFloat(const wchar_t *name, double &value) const
{
	String s;

	if (get(name, s))
	{
		if (IsNumber(s.c_str()))
		{
			value = wcstod(s.c_str(), NULL);
			return true;
		}
	}

	return false;
}

bool ConfigFile::GetBool(const wchar_t *name, bool &value) const
{
	String s;

	if (get(name, s))
	{
		if (!wcscmp(s.c_str(), L"true"))
		{
			value = true;
			return true;
		}

		if (!wcscmp(s.c_str(), L"false"))
		{
			value = false;
			return true;
		}
	}

	return false;
}

bool ConfigFile::GetString(const wchar_t *name, char *value, size_t size) const
{
	String s;

	if (get(name, s))
		return ConvertUTF16To8(value, size, s.c_str());

	return false;
}

bool ConfigFile::GetString(const wchar_t *name, wchar_t *value, size_t size) const
{
	String s;

	if (value && get(name, s))
	{
		wcscpys(value, size, s.c_str());
		return true;
	}

	return false;
}

bool ConfigFile::GetBinary(const wchar_t *name, void *value, size_t bytes) const
{
	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ConfigFile::SetInt(const wchar_t *name, int value)
{
	return put(name, std::to_wstring(value).c_str());
}

bool ConfigFile::SetFloat(const wchar_t *name, double value)
{
	return put(name, std::to_wstring(value).c_str());
}

bool ConfigFile::SetBool(const wchar_t *name, bool value)
{
	return put(name, value ? L"true" : L"false");
}

bool ConfigFile::SetString(const wchar_t *name, const char *value)
{
	return put(name, StrW(value).c_str());
}

bool ConfigFile::SetString(const wchar_t *name, const wchar_t *value)
{
	return put(name, value);
}

bool ConfigFile::SetBinary(const wchar_t *name, const void *value, size_t bytes)
{
	return false;
}

bool ConfigFile::Delete(const wchar_t *name)
{
	if (name)
	{
		if (d.erase(name) > 0)
		{
			write = true;

			return true;
		}
	}

	return false;
}