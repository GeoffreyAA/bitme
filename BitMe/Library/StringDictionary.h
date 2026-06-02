#ifndef __STRING_DICTIONARY_H__
#define __STRING_DICTIONARY_H__

#include <map>
#include "String.h"

typedef std::map<String, String> StringDictionary;

bool StringDictionaryRead(const wchar_t *pszFile, StringDictionary &d);
bool StringDictionaryWrite(const wchar_t *pszFile, const StringDictionary &d);

#endif