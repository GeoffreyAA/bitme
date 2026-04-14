#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "String.h"
#include "StringDictionary.h"
#include "StringList.h"
#include <mutex>

class Language
{
public:
	Language();
	Language(const wchar_t *name, const StringDictionary &dict);

	String getString(const wchar_t *key) const;

	const String& getName() const;
	const StringDictionary& getStrings() const;

	void setName(const wchar_t *name);
	void setStrings(const StringDictionary &dict);

private:
	String Name;
	StringDictionary Strings;
};

class LanguageManager
{
public:
	StringList getAvailableLanguages() const;

	Language getCurrentLanguage();
	bool setCurrentLanguage(const wchar_t *name);

	String getCurrentLanguageName();
	String getStringFromCurrentLanguage(const wchar_t *key);

	static LanguageManager& getInstance();

	~LanguageManager();

private:
	LanguageManager();
	bool LoadLanguage(const wchar_t *name, Language &dst) const;

private:
	Language CurrentLanguage;
	std::mutex cs;

	static LanguageManager Instance;
};

#endif