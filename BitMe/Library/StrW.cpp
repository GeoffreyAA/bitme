#include "stdafx.h"
#include "StrW.h"
#include <windows.h>
#include <malloc.h>

StrW::StrW(const char *a) : w(NULL)
{
	if (a)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, a, -1, NULL, 0);

		if (size)
		{
			w = new wchar_t[size];

			if (w && !MultiByteToWideChar(CP_UTF8, 0, a, -1, w, size))
			{
				delete [] w;

				w = NULL;
			}
		}
	}
}

StrW::~StrW()
{
	if (w)
	{
		delete [] w;
	}
}

const wchar_t *StrW::c_str() const
{
	return (w);
}

StrW::operator const wchar_t *() const
{
	return (c_str());
}


///////////////////////////////////////////////////////////////

StrA::StrA(const wchar_t *w) : a(NULL)
{
	if (w)
	{
		int bytes = WideCharToMultiByte(CP_ACP, 0, w, -1, NULL, 0, NULL, NULL);

		if (bytes)
		{
			a = (char *)malloc(bytes);

			if (a && !WideCharToMultiByte(CP_ACP, 0, w, -1, a, bytes, NULL, NULL))
			{
				free(a);

				a = NULL;
			}
		}
	}
}

StrA::~StrA()
{
	if (a)
	{
		free(a);
	}
}

const char *StrA::c_str() const
{
	return (a);
}

StrA::operator const char *() const
{
	return (c_str());
}


///////////////////////////////////////////////////////////////

StrUTF8::StrUTF8(const wchar_t *w) : a(NULL)
{
	if (w)
	{
		int bytes = WideCharToMultiByte(CP_UTF8, 0, w, -1, NULL, 0, NULL, NULL);

		if (bytes)
		{
			a = (char *)malloc(bytes);

			if (a && !WideCharToMultiByte(CP_UTF8, 0, w, -1, a, bytes, NULL, NULL))
			{
				*a = 0;
			}
		}
	}
}

StrUTF8::~StrUTF8()
{
	if (a)
	{
		free(a);
	}
}

const char *StrUTF8::c_str() const
{
	return (a ? a : "");
}

StrUTF8::operator const char *() const
{
	return (c_str());
}