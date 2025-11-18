#include "stdafx.h"
#include "Library.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

wchar_t *wcscpys(wchar_t *strDestination, const wchar_t *strSource, size_t cbSize)
{
	if (strDestination && strSource && (cbSize > 0))
	{
		wcsncpy(strDestination, strSource, cbSize);
		strDestination[cbSize - 1] = L'\0';
	}

	return (strDestination);
}

int swprintfs(wchar_t *c, size_t cbSize, const wchar_t *Format, ...)
{
	if (c && (cbSize > 0))
	{
		va_list argptr;

		va_start(argptr, Format);

		int n = _vsnwprintf(c, cbSize, Format ? Format : L"", argptr);

		va_end(argptr);

		c[cbSize - 1] = L'\0';

		return (n);
	}

	return (-1);
}

wchar_t *IntToStr(int x, wchar_t *c, size_t cbSize)
{
	swprintfs(c, cbSize, L"%d", x);

	return (c);
}

wchar_t *FloatToStr(double x, wchar_t *c, size_t cbSize, const wchar_t *Format)
{
	swprintfs(c, cbSize, Format, x);

	return (c);
}

wchar_t *StringDelete(wchar_t *s, size_t i)
{
	if (s)
	{
		const size_t length = wcslen(s);

		if ((0 <= i) && (i < length))
		{
			memmove(s + i, s + i + 1, (length - i) * sizeof(wchar_t));
		}
	}

	return (s);
}

wchar_t *Trim(wchar_t *s)
{
	TrimLeft(s);
	TrimRight(s);

	return (s);
}

wchar_t *TrimLeft(wchar_t *s)
{
	if (s)
	{
		wchar_t *p = s;

		while (*p && iswspace(*p))
		{
			p++;
		}

		if (p != s)
		{
			memmove(s, p, (wcslen(p) + 1) * sizeof(wchar_t));
		}
	}

	return (s);
}

wchar_t *TrimRight(wchar_t *s)
{
	if (s)
	{
		size_t i = wcslen(s);

		while ((i--) && iswspace(s[i]))
		{
			s[i] = L'\0';
		}
	}

	return (s);
}

wchar_t *RemoveNonNbrs(wchar_t *s)
{
	if (s)
	{
		const int length = wcslen(s);

		int SgnPos = -1;
		int i = 0;

		while ((i < length) && !iswdigit(s[i]))
		{
			if ((s[i] == L'-') || (s[i] == L'+'))
			{
				SgnPos = i;
			}

			i++;
		}

		int DecPos = -1;

		wchar_t *p = wcschr(s, L'.');

		if (p && ((p - s) > SgnPos))
		{
			DecPos = p - s;
		}

		for (i = length - 1; i >= 0; i--)
		{
			if (!iswdigit(s[i]) && (i != SgnPos) && (i != DecPos))
			{
				StringDelete(s, i);
			}
		}
	}

	return (s);
}

bool ContainsText(const wchar_t *s)
{
	if (s)
	{
		while (*s)
		{
			if (!iswspace(*s))
				return true;

			s++;
		}
	}

	return false;
}

bool IsNumber(const wchar_t *s)
{
	if (s)
	{
		if ((*s == L'-') || (*s == L'+')) s++;

		bool fullstop = false;
		bool exponent = false;

		while (*s)
		{
			if (!iswdigit(*s))
			{
				if ((*s == L'.') && !fullstop && !exponent)
				{
					fullstop = true;
				}
				else if ((towlower(*s) == L'e') && !exponent)
				{
					s++;

					if ((*s == L'-') || (*s == L'+')) s++;

					if (!iswdigit(*s))
					{
						return false;
					}

					exponent = true;
				}
				else
				{
					return false;
				}
			}

			s++;
		}

		return true;
	}

	return false;
}