#include "stdafx.h"
#include "Library.h"

#include <wchar.h>
#include <wctype.h>
#include <string.h>

wchar_t *wcscpys(wchar_t *dst, size_t size, const wchar_t *src)
{
	if (dst && src && (size > 0))
	{
		const size_t length = wcslen(src);

		memcpy(dst, src, ((length < size) ? (length + 1) : (size - 1)) * sizeof(wchar_t));

		dst[size - 1] = L'\0';
	}

	return dst;
}

#if 0

/*
May 27, 2026:

Decided to retire this function, which I wrote in 2011.
It works well, but using str/wcsncpy is considered bad practice.
*/

wchar_t *wcscpys(wchar_t *strDestination, const wchar_t *strSource, size_t cbSize)
{
	if (strDestination && strSource && (cbSize > 0))
	{
		wcsncpy(strDestination, strSource, cbSize);
		strDestination[cbSize - 1] = L'\0';
	}

	return (strDestination);
}

/*
May 27, 2026:

Retired custom swprintfs in favour of C99's swprintf. Back when I programmed these things, using VC++ 6.0,
the available swprintf (_swprintf today) did not take the buffer size. So, I wrapped _vsnwprintf,
properly terminating with a NULL, and named it swprintfs, the "s" standing for "safe." As luck would have it,
the signature I used matches the C99 version, meaning that only the "s" needed to be removed from calls to this function.

Farewell! You've served WM and BitMe well for over a decade.
*/

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

#endif

wchar_t *IntToStr(int x, wchar_t *c, size_t cbSize)
{
	swprintf(c, cbSize, L"%d", x);

	return (c);
}

wchar_t *FloatToStr(double x, wchar_t *c, size_t cbSize, const wchar_t *Format)
{
	swprintf(c, cbSize, Format, x);

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
		wchar_t *p = s;
		wchar_t *sgn = NULL;

		while (*p && !iswdigit(*p))
		{
			if ((*p == L'-') || (*p == L'+'))
			{
				sgn = p;
			}

			p++;
		}

		wchar_t *dec = wcschr(s, L'.');

		if (dec && (dec < sgn))
		{
			dec = NULL;
		}

		size_t i = wcslen(s);

		while (i--)
		{
			if (!iswdigit(s[i]) && ((s + i) != sgn) &&
								   ((s + i) != dec))
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