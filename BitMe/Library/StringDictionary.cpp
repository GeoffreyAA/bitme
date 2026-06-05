#include "stdafx.h"
#include "StringDictionary.h"
#include "Library.h"
#include "Unicode.h"
#include <stdio.h>
#include <wchar.h>

const wchar_t Newline = L'\n';
const wchar_t NewlineEncoded = L'|';

wchar_t *BreakString(wchar_t *dst, size_t size, const char *line)
{
	if (ConvertUTF8To16(dst, size, line))
	{
		Strip(dst);

		wchar_t *Separator = wcschr(dst, L'=');

		if (Separator)
		{
			*Separator = L'\0';

			wchar_t *val = Separator + 1;

			Trim(dst);
			Trim(val);
			ReplaceChars(val, NewlineEncoded, Newline);

			if (wcslen(dst) && wcslen(val))
			{
				return val;
			}
		}
	}

	return NULL;
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
				wchar_t *val = BreakString(w, sizeof(w) / sizeof(w[0]), c);

				if (val)
				{
					d.insert(StringDictionary::value_type(w, val));
				}
			}

			fclose(f);

			return true;
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MakeString(char *dst, size_t size, const wchar_t *key, const wchar_t *val)
{
	if (dst && size && key && val)
	{
		wchar_t k[1024];
		wchar_t v[3072];
		wchar_t w[4096];

		wcscpys(k, sizeof(k) / sizeof(k[0]), key);
		wcscpys(v, sizeof(v) / sizeof(v[0]), val);

		ReplaceChars(v, Newline, NewlineEncoded);
		Trim(k);
		Trim(v);

		swprintf(w, sizeof(w) / sizeof(w[0]), L"%ls=%ls", k, v);
		Strip(w);

		return ConvertUTF16To8(dst, size, w);
	}

	return false;
}

bool StringDictionaryWrite(const wchar_t *pszFile, const StringDictionary &d)
{
	if (pszFile)
	{
		FILE *f = _wfopen(pszFile, L"wb");

		if (f)
		{
			char c[4096];

			for (StringDictionary::const_iterator i = d.begin(); i != d.end(); i++)
			{
				if (MakeString(c, sizeof(c) / sizeof(c[0]), (*i).first.c_str(), (*i).second.c_str()))
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0

std::wostream& operator<<(std::wostream &wos, const StringDictionary &d)
{
	for (StringDictionary::const_iterator i = d.begin(); i != d.end(); i++)
	{
		wos << (*i).first << L" = "
			<< (*i).second << std::endl;
	}

	return wos;
}

#endif