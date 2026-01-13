#include "stdafx.h"
#include "Win32Library.h"
#include "Library.h"
#include "File.h"
#include <stdlib.h>


///////////////////////////////////////////////////////////////
//
// Windows
//
///////////////////////////////////////////////////////////////

int GetWindowWidth(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? (r.right - r.left) : 0);
}

int GetWindowHeight(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? (r.bottom - r.top) : 0);
}

int GetWindowLeft(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? r.left : 0);
}

int GetWindowRight(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? r.right : 0);
}

int GetWindowTop(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? r.top : 0);
}

int GetWindowBottom(HWND hWnd)
{
	RECT r;

	return (GetWindowRect(hWnd, &r) ? r.bottom : 0);
}

int GetDesktopWidth()
{
	return (GetWindowWidth(GetDesktopWindow()));
}

int GetDesktopHeight()
{
	return (GetWindowHeight(GetDesktopWindow()));
}

void SetWindowSize(HWND hWnd, int w, int h)
{
	SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

void SetWindowPosition(HWND hWnd, int x, int y)
{
	SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CenterWindow(HWND hWnd, HWND hRel)
{
	if (hWnd)
	{
		RECT w;
		RECT r;

		if (GetWindowRect(hWnd, &w) &&
			GetWindowRect(hRel ? hRel : GetDesktopWindow(), &r))
		{
			SetWindowPosition(hWnd, r.left + ((r.right - r.left) - (w.right - w.left)) / 2,
									r.top + ((r.bottom - r.top) - (w.bottom - w.top)) / 2);
		}
	}
}

double GetWindowFloat(HWND hWnd)
{
	wchar_t c[512];

	if (GetWindowTextW(hWnd, c, sizeof(c) / sizeof(c[0])))
	{
		if (!IsNumber(c))
		{
			RemoveNonNbrs(c);
		}

		return (wcstod(c, NULL));
	}

	return (0.0);
}

void SetWindowFloat(HWND hWnd, double x, const wchar_t *pszFormat)
{
	wchar_t c[256];

	swprintfs(c, sizeof(c) / sizeof(c[0]), pszFormat, x);

	SetWindowTextW(hWnd, c);
}

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

void SetWindowInt(HWND hWnd, int x)
{
	wchar_t c[64];

	IntToStr(x, c, sizeof(c) / sizeof(c[0]));

	SetWindowTextW(hWnd, c);
}

bool GetDlgItemChecked(HWND hDlg, int nID)
{
	return (SendDlgItemMessage(hDlg, nID, BM_GETCHECK, 0, 0) == BST_CHECKED);
}

void SetDlgItemCheck(HWND hDlg, int nID, bool bCheck)
{
	SendDlgItemMessage(hDlg, nID, BM_SETCHECK, (WPARAM)(bCheck ? BST_CHECKED : BST_UNCHECKED), 0);
}

void SetWindowFont(HWND hWnd, HFONT hFont)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
}


///////////////////////////////////////////////////////////////
//
// Menu
//
///////////////////////////////////////////////////////////////

void SetMenuString(HMENU hMenu, UINT uID, const wchar_t *pszString)
{
	UINT uFlags = GetMenuState(hMenu, uID, MF_BYCOMMAND);

	if (uFlags != 0xFFFFFFFF)
	{
		ModifyMenuW(hMenu, uID, MF_BYCOMMAND | MF_STRING | uFlags, uID, pszString);
	}
}

void SetMenuStrings(HMENU hMenu, const UINT IDs[], size_t n, const StringList &s)
{
	for (size_t i = 0; i < n; i++)
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

bool GetMenuItemChecked(HMENU hMenu, UINT uID)
{
	UINT uFlags = GetMenuState(hMenu, uID, MF_BYCOMMAND);

	if (uFlags != 0xFFFFFFFF)
	{
		return ((uFlags & MF_CHECKED) != 0);
	}

	return false;
}

void SetMenuItemCheck(HMENU hMenu, UINT uID, bool bCheck)
{
	CheckMenuItem(hMenu, uID, MF_BYCOMMAND | (bCheck ? MF_CHECKED : MF_UNCHECKED));
}

bool ToggleMenuItemCheck(HMENU hMenu, UINT uID)
{
	bool b = GetMenuItemChecked(hMenu, uID);

	SetMenuItemCheck(hMenu, uID, !b);

	return (b);
}

String GetMenuItemSelected(HMENU hMenu, const UINT IDs[], size_t n)
{
	if (hMenu)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (GetMenuItemChecked(hMenu, IDs[i]))
			{
				wchar_t w[32];

				return (GetMenuStringW(hMenu, IDs[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) ? w : L"");
			}
		}
	}

	return (L"");
}

bool GetMenuItemSelected(HMENU hMenu, const UINT IDs[], size_t n, wchar_t *s, size_t cbSize)
{
	if (hMenu && s)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (GetMenuItemChecked(hMenu, IDs[i]))
			{
				return (GetMenuStringW(hMenu, IDs[i], s, cbSize, MF_BYCOMMAND) != 0);
			}
		}
	}

	return false;
}

void SelectMenuItem(HMENU hMenu, const UINT IDs[], size_t n, const wchar_t *s)
{
	if (s)
	{
		if (hMenu)
		{
			wchar_t w[32];

			for (size_t i = 0; i < n; i++)
			{
				if (GetMenuStringW(hMenu, IDs[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) && !wcscmp(s, w))
				{
					CheckMenuRadioItem(hMenu, IDs[0], IDs[n - 1], IDs[i], MF_BYCOMMAND);

					return;
				}
			}

			for (size_t j = 0; j < n; j++)
			{
				SetMenuItemCheck(hMenu, IDs[j], false);
			}
		}
	}
}

bool SelectMenuItemID(HMENU hMenu, const UINT IDs[], size_t n, UINT uID)
{
	if (hMenu)
	{
		for (size_t i = 0; i < n; i++)
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

void EnableMenuItems(HMENU hMenu, const UINT IDs[], size_t n, bool b)
{
	if (hMenu)
	{
		for (size_t i = 0; i < n; i++)
		{
			EnableMenuItem(hMenu, IDs[i], MF_BYCOMMAND | (b ? MF_ENABLED : MF_GRAYED));
		}
	}
}


///////////////////////////////////////////////////////////////
//
// Message Box
//
///////////////////////////////////////////////////////////////

int MsgBox(const wchar_t *pszMessage, const wchar_t *pszTitle, HWND hOwner, MsgType t)
{
	UINT uType = MB_OK;

	switch (t)
	{
		case MSG_INFORMATION:
			uType |= MB_ICONINFORMATION;
			break;

		case MSG_EXCLAMATION:
			uType |= MB_ICONEXCLAMATION;
			break;

		case MSG_ERROR:
			uType |= MB_ICONERROR;
			break;
	}

	return (MessageBoxW(hOwner, pszMessage, pszTitle, uType));
}


///////////////////////////////////////////////////////////////
//
// Font
//
///////////////////////////////////////////////////////////////

HFONT CreatePointFont(const wchar_t *pszName, int nPointSize, bool bBold, bool bItalic, bool bUnderline, bool bStrikeOut)
{
	wchar_t s[32] = L"";

	if (pszName)
	{
		wcscpys(s, pszName, sizeof(s) / sizeof(s[0]));
	}

	HDC hDC = GetDC(NULL);

	if (!hDC) return (NULL);

	HFONT h = CreateFontW(-MulDiv(nPointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72),
						  0,
						  0,
						  0,
						  bBold ? FW_BOLD : FW_NORMAL,
						  bItalic,
						  bUnderline,
						  bStrikeOut,
						  ANSI_CHARSET,
						  OUT_DEFAULT_PRECIS,
						  CLIP_DEFAULT_PRECIS,
						  PROOF_QUALITY,
						  DEFAULT_PITCH | FF_DONTCARE,
						  s);

	ReleaseDC(NULL, hDC);

	return (h);
}


///////////////////////////////////////////////////////////////
//
// HTML Help
//
///////////////////////////////////////////////////////////////

#ifndef _AFXDLL

bool HtmlHelp(const wchar_t *pszFile, const wchar_t *pszPage, HWND hOwner)
{
	HINSTANCE h = LoadLibrary(L"hhctrl.ocx");

	if (h)
	{
		typedef HWND (WINAPI* fnHtmlHelp)(HWND, LPCWSTR, UINT, DWORD *);

		//fnHtmlHelp pHtmlHelp = (fnHtmlHelp)GetProcAddress(h, (LPCSTR)((DWORD)((WORD)(15))));

		fnHtmlHelp pHtmlHelp = (fnHtmlHelp)GetProcAddress(h, "HtmlHelpW");

		if (pHtmlHelp)
		{
			if (pszFile && pszPage)
			{
				wchar_t w[MAX_PATH];

				swprintfs(w, sizeof(w) / sizeof(w[0]), L"%s::/%s", pszFile, pszPage);

				return (pHtmlHelp(hOwner, w, 0, NULL) != NULL);
			}

			return (pHtmlHelp(hOwner, pszFile, 0, NULL) != NULL);
		}
	}

	return false;
}

#endif


///////////////////////////////////////////////////////////////
//
// Other
//
///////////////////////////////////////////////////////////////

bool GetDateTimeFormatted(wchar_t *pszBuffer, size_t cbSize, const SYSTEMTIME *st)
{
	wchar_t d[256];
	wchar_t t[256];

	if (GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, st, NULL, d, sizeof(d) / sizeof(d[0])) &&
		GetTimeFormatW(LOCALE_USER_DEFAULT, 0, st, NULL, t, sizeof(t) / sizeof(t[0])))
	{
		swprintfs(pszBuffer, cbSize, L"%s, %s", d, t);

		return true;
	}

	return false;
}

// Reference: "Converting a time_t Value to a File Time" from the
// "Time" section in the Platform SDK documentation.

bool TimeToFileTime(time_t t, FILETIME *ft)
{
	if (ft)
	{
		LONGLONG l = 116444736000000000 + Int32x32To64(t, 10000000);

		ft->dwLowDateTime = (DWORD)l;
		ft->dwHighDateTime = (DWORD)(l >> 32);

		return true;
	}

	return false;
}

bool TimeToSystemTime(time_t t, SYSTEMTIME *st)
{
	if (st)
	{
		FILETIME ft;

		return (TimeToFileTime(t, &ft) && FileTimeToSystemTime(&ft, st));
	}

	return false;
}

bool TimeToSystemTimeLocal(time_t t, SYSTEMTIME *st)
{
	if (st)
	{
		FILETIME ft;
		FILETIME ftLocal;

		return (TimeToFileTime(t, &ft) && FileTimeToLocalFileTime(&ft, &ftLocal) && FileTimeToSystemTime(&ftLocal, st));
	}

	return false;
}

bool ShellOpen(const wchar_t *pszFile, HWND hOwner)
{
	return (ShellExecuteW(hOwner, NULL, pszFile, NULL, NULL, SW_SHOWNORMAL) > (HINSTANCE)32);
}

bool IsWindowsNT()
{
	return (GetVersion() < 0x80000000);
}

bool GetOpenFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner, const wchar_t *pszTitle, const wchar_t *pszFilter)
{
	if (pszBuffer && cbSize)
	{
		OPENFILENAMEW ofn;
		ZeroMemory(&ofn, sizeof(ofn));

		*pszBuffer = 0;

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hOwner;
		ofn.lpstrFilter = pszFilter;
		ofn.lpstrFile = pszBuffer;
		ofn.nMaxFile = cbSize;
		ofn.lpstrTitle = pszTitle;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

		return (GetOpenFileNameW(&ofn) != 0);
	}

	return false;
}

bool GetSaveFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner, const wchar_t *pszTitle, const wchar_t *pszFilter, const wchar_t *pszDefExt)
{
	if (pszBuffer && cbSize)
	{
		OPENFILENAMEW ofn;
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

		return (GetSaveFileNameW(&ofn) != 0);
	}

	return false;
}


///////////////////////////////////////////////////////////////
//
// Application File
//
///////////////////////////////////////////////////////////////

ApplicationFile::ApplicationFile(const wchar_t *pszFile)
{
	const size_t s = sizeof(Path) / sizeof(Path[0]);

	Ready = GetProgramPath(Path, s) && AddFileName(Path, GetFileName(pszFile), s);
}

const wchar_t *ApplicationFile::c_str() const
{
	return (Ready ? Path : NULL);
}

ApplicationFile::operator const wchar_t *() const
{
	return (c_str());
}