#include "stdafx.h"
#include "ResourceString.h"
#include "Language.h"

ResourceString::ResourceString(const wchar_t *pszName)
{
	if (pszName)
	{
		LanguageManager::getInstance().getStringFromCurrentLanguage(pszName, s);
	}
}

const wchar_t *ResourceString::c_str() const
{
	return (s.c_str());
}

ResourceString::operator const wchar_t *() const
{
	return (c_str());
}