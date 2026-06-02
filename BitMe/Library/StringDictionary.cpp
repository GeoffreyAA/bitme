#include "stdafx.h"
#include "StringDictionary.h"
#include "Library.h"
#include "Unicode.h"
#include <stdio.h>
#include <wchar.h>

void ReplaceNewlines(wchar_t *s)
{
	if (s)
	{
		for (size_t i = wcslen(s); i > 0; i--)
		{
			if ((s[i] == L'n') && (s[i - 1] == L'\\'))
			{
				s[i] = L'\n';

				StringDelete(s, i - 1);
			}
		}
	}
}

wchar_t *BreakString(wchar_t *s)
{
	if (s)
	{
		wchar_t *Separator = wcschr(s, L'=');

		if (Separator)
		{
			*Separator = L'\0';

			wchar_t *b = Separator + 1;

			Trim(s);
			Trim(b);

			ReplaceNewlines(b);

			if (wcslen(s) && wcslen(b))
			{
				return (b);
			}
		}
	}

	return (NULL);
}

bool StringDictionaryRead(const wchar_t *pszFile, StringDictionary &d)
{
	if (pszFile)
	{
		FILE *f = _wfopen(pszFile, L"rb");

		if (f)
		{
			d.clear();

			char c[4096];
			wchar_t w[4096];

			while (fgets(c, sizeof(c) / sizeof(c[0]), f) != NULL)
			{
				if (ConvertUTF8To16(w, sizeof(w) / sizeof(w[0]), c))
				{
					wchar_t *b = BreakString(w);

					if (b)
					{
						d.insert(StringDictionary::value_type(w, b));
					}
				}
			}

			fclose(f);

			return true;
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String TranslateNewlines(const String &s)
{
	String a;
	a.reserve(s.size());

	for (String::const_iterator i = s.begin(); i != s.end(); i++)
	{
		if ((*i) == L'\n')
		{
			a.append(L"\\n");
		}
		else
		{
			a.append(1, *i);
		}
	}

	return (a);
}

bool StringDictionaryWrite(const wchar_t *pszFile, const StringDictionary &d)
{
	if (pszFile)
	{
		FILE *f = _wfopen(pszFile, L"wb");

		if (f)
		{
			char c[4096];
			wchar_t w[4096];

			for (StringDictionary::const_iterator i = d.begin(); i != d.end(); i++)
			{
				swprintf(w, sizeof(w) / sizeof(w[0]), L"%s=%s", (*i).first.c_str(), TranslateNewlines((*i).second).c_str());

				if (ConvertUTF16To8(c, sizeof(c) / sizeof(c[0]), w))
				{
					fprintf(f, "%s\r\n", c);
				}
			}

			fclose(f);

			return true;
		}
	}

	return false;
}