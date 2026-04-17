#include "stdafx.h"
#include "Language.h"
#include "ConfigFile.h"
#include "File.h"
#include "Library.h"
#include <windows.h>

Language::Language()
{
}

Language::Language(const wchar_t *name, const StringDictionary &dict) : Name(name ? name : L""), Strings(dict)
{
}

String Language::getString(const wchar_t *key) const
{
	if (key)
	{
		StringDictionary::const_iterator i = Strings.find(key);

		if (i != Strings.end())
		{
			return (*i).second;
		}

		if (ContainsText(key))
		{
			wchar_t s[256];

			swprintfs(s, sizeof(s) / sizeof(s[0]), L"<%s>", key);

			return s;
		}
	}

	return L"";
}

const String& Language::getName() const
{
	return Name;
}

const StringDictionary& Language::getStrings() const
{
	return Strings;
}

void Language::setName(const wchar_t *name)
{
	Name = name ? name : L"";
}

void Language::setStrings(const StringDictionary &dict)
{
	Strings = dict;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LanguageManager LanguageManager::Instance;

const wchar_t LanguageCfg[] = L"Language";

LanguageManager::LanguageManager()
{
	wchar_t w[256];

	if (ConfigFile().getString(LanguageCfg, w, sizeof(w) / sizeof(w[0])))
	{
		setCurrentLanguage(w);
	}
	else
	{
		setCurrentLanguage(L"English");
	}
}

LanguageManager::~LanguageManager()
{
	std::lock_guard<std::mutex> lock(cs);

	ConfigFile().setString(LanguageCfg, CurrentLanguage.getName().c_str());
}

Language LanguageManager::getCurrentLanguage()
{
	std::lock_guard<std::mutex> lock(cs);

	return CurrentLanguage;
}

bool LanguageManager::setCurrentLanguage(const wchar_t *name)
{
	Language tmp;

	if (LoadLanguage(name, tmp))
	{
		std::lock_guard<std::mutex> lock(cs);

		CurrentLanguage = tmp;

		return true;
	}

	return false;
}

String LanguageManager::getCurrentLanguageName()
{
	std::lock_guard<std::mutex> lock(cs);

	return CurrentLanguage.getName();
}

String LanguageManager::getStringFromCurrentLanguage(const wchar_t *key)
{
	std::lock_guard<std::mutex> lock(cs);

	return CurrentLanguage.getString(key);
}

StringList LanguageManager::getAvailableLanguages() const
{
	StringList s;

	wchar_t w[MAX_PATH];
	const size_t size = sizeof(w) / sizeof(w[0]);

	if (GetProgramPath(w, size) && AddFileName(w, L"Languages\\*.lng", size))
	{
		WIN32_FIND_DATAW wfd;
		memset(&wfd, 0, sizeof(wfd));

		HANDLE hFile = FindFirstFileW(w, &wfd);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			do {

				RemoveFileExt(wfd.cFileName);
				s.push_back(wfd.cFileName);

			} while (FindNextFileW(hFile, &wfd));

			FindClose(hFile);
		}
	}

	return s;
}

bool LanguageManager::LoadLanguage(const wchar_t *name, Language &dst) const
{
	if (name)
	{
		wchar_t w[MAX_PATH];
		const size_t size = sizeof(w) / sizeof(w[0]);

		if (GetProgramPath(w, size) && AddFileName(w, L"Languages", size)
									&& AddFileName(w, name, size)
									&& AddFileExt(w, L"lng", size))
		{
			StringDictionary d;

			if (StringDictionarySerialiser().read(w, d))
			{
				dst.setName(name);
				dst.setStrings(d);

				return true;
			}
		}
	}

	return false;
}

LanguageManager& LanguageManager::getInstance()
{
	return Instance;
}