#include "stdafx.h"
#include "Language.h"
#include "ConfigConcrete.h"
#include "File.h"
#include "Library.h"
#include "Win32Library.h"
#include <stdlib.h>
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

			swprintf(s, _countof(s), L"<%ls>", key);

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

LanguageManager::LanguageManager()
{
	wchar_t w[256];

	if (ConfigConcrete().Get().GetString(L"Language", w, _countof(w)))
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

	ConfigConcrete().Get().SetString(L"Language", CurrentLanguage.getName().c_str());
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

	if (GetProgramPath(w, _countof(w)) && AddFileName(w, L"Languages\\*.lng", _countof(w)))
	{
		WIN32_FIND_DATAW wfd;
		ZeroMemory(&wfd, sizeof(wfd));

		HANDLE hFile = FindFirstFileW(w, &wfd);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			do {

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// Thanks to Raymond Chen's blog. I hadn't realised that directories would be processed.
					continue;

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

		if (GetProgramPath(w, _countof(w)) && AddFileName(w, L"Languages", _countof(w))
										   && AddFileName(w, name, _countof(w))
										   && AddFileExt(w, L"lng", _countof(w)))
		{
			StringDictionary d;

			if (StringDictionaryRead(w, d))
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