#include "stdafx.h"
#include "TmpLibrary.h"
#include "Library\Library.h"
#include "Library\Win32Library.h"

int GetWindowRight(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? r.right : 0);
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

void SetWindowInt4(HWND hWnd, int x)
{
	wchar_t c[256];
	wchar_t Formatted[256];
	wchar_t w[16];

	IntToStr(x, c, sizeof(c) / sizeof(c[0]));

	if (GetNumberFormat(LOCALE_USER_DEFAULT, 0, c, NULL, Formatted, sizeof(Formatted) / sizeof(Formatted[0])) &&
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, w, sizeof(w) / sizeof(w[0])))
	{
		wchar_t *p = (wchar_t *)wcsstr(Formatted, w);

		if (p)
		{
			*p = 0;

			SetWindowTextW(hWnd, Formatted);

			return;
		}
	}

	SetWindowTextW(hWnd, c);
}

void SetWindowTextRange(HWND hWnd, int x, const wchar_t *pszString)
{
	wchar_t c[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%d %s", x, pszString ? pszString : L"");

	SetWindowTextW(hWnd, c);
}

void SetWindowInt2(HWND hWnd, int x)
{
	wchar_t c[64];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%02d", x);

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




/*

uint32 Clamp64To32(uint64 x)
{
	return ((x > UINT_MAX) ? UINT_MAX : x);
}

*/

/*
bool GetSaveFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner, const wchar_t *pszTitle, const wchar_t *pszFilter, const wchar_t *pszDefExt)
{
	if (pszBuffer && cbSize)
	{
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));

		//wchar_t w[MAX_PATH] = L"BitMe.htm";

		*pszBuffer = 0;

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hOwner;
		ofn.lpstrFilter = pszFilter;
		ofn.lpstrFile = pszBuffer;
		ofn.nMaxFile = cbSize;
		ofn.lpstrTitle = pszTitle;
		ofn.Flags = OFN_HIDEREADONLY | OFN_NOREADONLYRETURN | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
		ofn.lpstrDefExt = pszDefExt;

		return (GetSaveFileName(&ofn) != 0);
	}

	return false;
}




bool GetOpenFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner, const wchar_t *pszTitle, const wchar_t *pszFilter)
{
	if (pszBuffer && cbSize)
	{
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));

		*pszBuffer = 0;

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hOwner;
		ofn.lpstrFilter = pszFilter;
		ofn.lpstrFile = pszBuffer;
		ofn.nMaxFile = cbSize;
		ofn.lpstrTitle = pszTitle;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

		return (GetOpenFileName(&ofn) != 0);
	}

	return false;
}
		

*/





/*
bool GetMenuItemChecked(HMENU hMenu, UINT uID)
{
	UINT uFlags = GetMenuState(hMenu, uID, MF_BYCOMMAND);

	if (uFlags != 0xffffffff)
	{
		return (uFlags & MF_CHECKED);
	}

	return false;
}

void SetMenuItemCheck(HMENU hMenu, UINT uID, bool bCheck)
{
	CheckMenuItem(hMenu, uID, MF_BYCOMMAND | (bCheck ? MF_CHECKED : MF_UNCHECKED));
}



void SetMenuStringByCommand(HMENU hMenu, UINT uID, const wchar_t *pszString)
{
	UINT uFlags = GetMenuState(hMenu, uID, MF_BYCOMMAND);

	if (uFlags != 0xffffffff)
	{
		ModifyMenuW(hMenu, uID, MF_BYCOMMAND | MF_STRING | uFlags, uID, pszString);
	}
}
*/



/*
String GetMenuItemSelected(HMENU hMenu, const UINT IDs[], int n)
{
	if (hMenu)
	{
		for (int i = 0; i < n; i++)
		{
			if (GetMenuItemChecked(hMenu, IDs[i]))
			{
				wchar_t w[32];

				return (GetMenuString(hMenu, IDs[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) ? w : L"");
			}
		}
	}

	return (L"");
}

void SelectMenuItem(HMENU hMenu, const UINT IDs[], int n, const wchar_t *s)
{
	if (s)
	{
		if (hMenu)
		{
			wchar_t w[32];

			for (int i = 0; i < n; i++)
			{
				if (GetMenuString(hMenu, IDs[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) && !wcscmp(s, w))
				{
					CheckMenuRadioItem(hMenu, IDs[0], IDs[n - 1], IDs[i], MF_BYCOMMAND);

					return;
				}
			}

			for (int j = 0; j < n; j++)
			{
				SetMenuItemCheck(hMenu, IDs[j], false);
			}
		}
	}
}

bool SelectMenuItemID(HMENU hMenu, const UINT IDs[], int n, UINT uID)
{
	if (hMenu)
	{
		for (int i = 0; i < n; i++)
		{
			if (IDs[i] == uID)
			{
				CheckMenuRadioItem(hMenu, IDs[0], IDs[n - 1], IDs[i], MF_BYCOMMAND);

				return true;
			}
		}
	}

	return false;
}

void EnableMenuItems(HMENU hMenu, const UINT IDs[], int n, bool b)
{
	if (hMenu)
	{
		for (int i = 0; i < n; i++)
		{
			EnableMenuItem(hMenu, IDs[i], MF_BYCOMMAND | (b ? MF_ENABLED : MF_GRAYED));
		}
	}
}



void SetMenuStrings(HMENU hMenu, const UINT IDs[], int n, const StringList &s)
{
	for (int i = 0; i < n; i++)
	{
		if (i < s.size())
		{
			SetMenuString(hMenu, IDs[i], s[i].c_str());
		}
		else
		{
			RemoveMenu(hMenu, IDs[i], MF_BYCOMMAND);
		}
	}
}
*/













/*
void SetWindowInt(HWND hWnd, int x)
{
	wchar_t c[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), L"%d", x);

	SetWindowTextW(hWnd, c);
}
*/

/*
int GetWindowInt(HWND hWnd)
{
	wchar_t c[512];

	if (GetWindowTextW(hWnd, c, sizeof(c) / sizeof(c[0])))
	{
		if (!IsNumber(c))
		{
			RemoveNonNbrs(c);
		}

		return (_wtoi(c));
	}

	return (0);
}
*/

/*
void SetWindowFont(HWND hWnd, HFONT hFont)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
}

void SetDlgItemCheck(HWND hDlg, int nID, bool bCheck)
{
	SendDlgItemMessage(hDlg, nID, BM_SETCHECK, (WPARAM)(bCheck ? BST_CHECKED : BST_UNCHECKED), 0);
}

bool GetDlgItemChecked(HWND hDlg, int nID)
{
	return (SendDlgItemMessage(hDlg, nID, BM_GETCHECK, 0, 0) == BST_CHECKED);
}
*/