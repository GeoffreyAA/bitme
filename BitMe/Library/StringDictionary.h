#ifndef __STRING_DICTIONARY_H__
#define __STRING_DICTIONARY_H__

#include <map>
#include "String.h"

typedef std::map<String, String> StringDictionary;

class StringDictionarySerialiser
{
public:
	bool read(const wchar_t *pszFile, StringDictionary &d) const;
	bool write(const wchar_t *pszFile, const StringDictionary &d) const;

protected:
	wchar_t *BreakString(wchar_t *s) const;
	void ReplaceNewlines(wchar_t *s) const;
	String TranslateNewlines(const String &s) const;
};

#endif