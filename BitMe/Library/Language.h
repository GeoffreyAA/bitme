#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "String.h"
#include "StringDictionary.h"
#include "StringList.h"
#include <windows.h>

class Language
{
public:
	Language(const wchar_t *pszName, const StringDictionary &s);

	const String& getName() const;
	String getString(const wchar_t *pszName) const;

private:
	const String Name;
	const StringDictionary Strings;
};

class LanguageManager
{
public:
	StringList getAvailableLanguages() const;

	Language getCurrentLanguage();
	bool setCurrentLanguage(const wchar_t *pszName);

	void getCurrentLanguageName(String &s);
	void getStringFromCurrentLanguage(const wchar_t *pszName, String &s);

	static LanguageManager& getInstance();

	~LanguageManager();

private:
	LanguageManager();
	Language *LoadLanguage(const wchar_t *pszName) const;

private:
	const Language *pLanguage;
	const Language DefaultLanguage;

	CRITICAL_SECTION cs;

	static LanguageManager Instance;
};

#endif