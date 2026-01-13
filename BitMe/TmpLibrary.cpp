#include "stdafx.h"
#include "TmpLibrary.h"
#include "Library\Library.h"
#include "Library\Win32Library.h"

void SetWindowInt2(HWND hWnd, int x)
{
	wchar_t c[64];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%02d", x);

	SetWindowTextW(hWnd, c);
}

void SetWindowInt4(HWND hWnd, int x)
{
	wchar_t c[256];
	wchar_t Formatted[256];
	wchar_t w[16];

	IntToStr(x, c, sizeof(c) / sizeof(c[0]));

	if (GetNumberFormat(LOCALE_USER_DEFAULT, 0, c, NULL, Formatted, sizeof(Formatted) / sizeof(Formatted[0])) &&
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, w, sizeof(w) / sizeof(w[0])))
	{
		wchar_t* p = (wchar_t*)wcsstr(Formatted, w);

		if (p)
		{
			*p = 0;

			SetWindowTextW(hWnd, Formatted);

			return;
		}
	}

	SetWindowTextW(hWnd, c);
}

void SetWindowFloat2(HWND hWnd, double x, const wchar_t *pszFormat)
{
	wchar_t c[256];
	wchar_t Formatted[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), pszFormat, x);

	if (GetNumberFormat(LOCALE_USER_DEFAULT, 0, c, NULL, Formatted, sizeof(Formatted) / sizeof(Formatted[0])))
	{
		SetWindowTextW(hWnd, Formatted);
	}
	else
	{
		SetWindowTextW(hWnd, c);
	}
}

void SetWindowTextRange(HWND hWnd, int x, const wchar_t *pszString)
{
	wchar_t c[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%d %s", x, pszString ? pszString : L"");

	SetWindowTextW(hWnd, c);
}

double BitsToKilobits(double x)
{
	return (x / 1000.0);
}

double BitsToMegabits(double x)
{
	return (x / 1000.0 / 1000.0);
}

String FloatToStr2(double x)
{
	wchar_t c[256];
	wchar_t Formatted[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%.2f", x);

	if (GetNumberFormat(LOCALE_USER_DEFAULT, 0, c, NULL, Formatted, sizeof(Formatted) / sizeof(Formatted[0])))
	{
		return (Formatted);
	}
	else
	{
		return (c);
	}
}

uint32 Clamp64To32(uint64 x)
{
	return ((x > UINT_MAX) ? UINT_MAX : x);
}