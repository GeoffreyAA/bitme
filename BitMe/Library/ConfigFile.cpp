#include "stdafx.h"
#include "ConfigFile.h"
#include <stdio.h>
#include <wchar.h>
#include "Library.h"
#include "Win32Library.h"
#include "StrW.h"
#include "Unicode.h"

ConfigFile::ConfigFile(const wchar_t *file) : write(false)
{
	ApplicationFile path(file);

	if (path.c_str())
	{
		fn = path.c_str();

		if (!StringDictionaryReader().read(path, d))
			d.clear();
	}
}

ConfigFile::~ConfigFile()
{
	if (write)
		StringDictionaryWriter().write(fn.c_str(), d);
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

int ConfigFile::getInteger(const wchar_t *name, int def) const
{
	String s;

	if (get(name, s))
	{
		if (IsNumber(s.c_str()))
			return wcstol(s.c_str(), NULL, 10);
	}

	return def;
}

double ConfigFile::getFloat(const wchar_t *name, double def) const
{
	String s;

	if (get(name, s))
	{
		if (IsNumber(s.c_str()))
			return wcstod(s.c_str(), NULL);
	}

	return def;
}

bool ConfigFile::getBool(const wchar_t *name, bool def) const
{
	String s;

	if (get(name, s))
	{
		if (!wcscmp(s.c_str(), L"true")) return true;
		if (!wcscmp(s.c_str(), L"false")) return false;
	}

	return def;
}

char *ConfigFile::getString(const wchar_t *name, char *value, size_t size) const
{
	String s;

	if (value && get(name, s))
	{
		if (ConvertUTF16To8(value, size, s.c_str()))
			return value;
	}

	return NULL;
}

wchar_t *ConfigFile::getString(const wchar_t *name, wchar_t *value, size_t size) const
{
	String s;

	if (value && get(name, s))
	{
		wcscpys(value, s.c_str(), size);

		return value;
	}

	return NULL;
}

void *ConfigFile::getBinary(const wchar_t *name, void *value, size_t bytes) const
{
	return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ConfigFile::setInteger(const wchar_t *name, int value)
{
	return put(name, std::to_wstring(value).c_str());
}

bool ConfigFile::setFloat(const wchar_t *name, double value)
{
	return put(name, std::to_wstring(value).c_str());
}

bool ConfigFile::setBool(const wchar_t *name, bool value)
{
	return put(name, value ? L"true" : L"false");
}

bool ConfigFile::setString(const wchar_t *name, const char *value)
{
	return put(name, StrW(value).c_str());
}

bool ConfigFile::setString(const wchar_t *name, const wchar_t *value)
{
	return put(name, value);
}

bool ConfigFile::setBinary(const wchar_t *name, const void *value, size_t bytes)
{
	return false;
}

bool ConfigFile::deleteValue(const wchar_t *name)
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