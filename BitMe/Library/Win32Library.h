#ifndef __WIN32_LIBRARY_H__
#define __WIN32_LIBRARY_H__

#include <windows.h>
#include "String.h"
#include "StringList.h"

// Windows
int GetWindowWidth(HWND hWnd);
int GetWindowHeight(HWND hWnd);
int GetWindowLeft(HWND hWnd);
int GetWindowRight(HWND hWnd);
int GetWindowTop(HWND hWnd);
int GetWindowBottom(HWND hWnd);
int GetDesktopWidth();
int GetDesktopHeight();
void SetWindowSize(HWND hWnd, int w, int h);
void SetWindowPosition(HWND hWnd, int x, int y);
void CenterWindow(HWND hWnd, HWND hRel = NULL);
double GetWindowFloat(HWND hWnd);
void SetWindowFloat(HWND hWnd, double x, const wchar_t *pszFormat = L"%.16g");
int GetWindowInt(HWND hWnd);
void SetWindowInt(HWND hWnd, int x);
bool GetDlgItemChecked(HWND hDlg, int nID);
void SetDlgItemCheck(HWND hDlg, int nID, bool bCheck);
void SetWindowFont(HWND hWnd, HFONT hFont);

// Menu
void SetMenuString(HMENU hMenu, UINT uID, const wchar_t *pszString);
void SetMenuStrings(HMENU hMenu, const UINT IDs[], size_t n, const StringList &s);
bool GetMenuItemChecked(HMENU hMenu, UINT uID);
void SetMenuItemCheck(HMENU hMenu, UINT uID, bool bCheck);
bool ToggleMenuItemCheck(HMENU hMenu, UINT uID);
String GetMenuItemSelected(HMENU hMenu, const UINT IDs[], size_t n);
bool GetMenuItemSelected(HMENU hMenu, const UINT IDs[], size_t n, wchar_t *s, size_t cbSize);
void SelectMenuItem(HMENU hMenu, const UINT IDs[], size_t n, const wchar_t *s);
bool SelectMenuItemID(HMENU hMenu, const UINT IDs[], size_t n, UINT uID);
void EnableMenuItems(HMENU hMenu, const UINT IDs[], size_t n, bool b);

// Message Box
enum MsgType { MSG_INFORMATION, MSG_EXCLAMATION, MSG_ERROR };
int MsgBox(const wchar_t *pszMessage = NULL, const wchar_t *pszTitle = NULL, HWND hOwner = NULL, MsgType t = MSG_INFORMATION);

// Font
HFONT CreatePointFont(const wchar_t *pszName = NULL, int nPointSize = 10, bool bBold = false, bool bItalic = false, bool bUnderline = false, bool bStrikeOut = false);

// HTML Help
#ifndef _AFXDLL
bool HtmlHelp(const wchar_t *pszFile = NULL, const wchar_t *pszPage = NULL, HWND hOwner = NULL);
#endif

// Other
bool GetDateTimeFormatted(wchar_t *pszBuffer, size_t cbSize, const SYSTEMTIME *st = NULL);
bool TimeToFileTime(time_t t, FILETIME *ft);
bool TimeToSystemTime(time_t t, SYSTEMTIME *st);
bool TimeToSystemTimeLocal(time_t t, SYSTEMTIME *st);
bool ShellOpen(const wchar_t *pszFile, HWND hOwner);
bool IsWindowsNT();
bool GetOpenFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner = NULL, const wchar_t *pszTitle = NULL, const wchar_t *pszFilter = NULL);
bool GetSaveFileNameDlg(wchar_t *pszBuffer, size_t cbSize, HWND hOwner = NULL, const wchar_t *pszTitle = NULL, const wchar_t *pszFilter = NULL, const wchar_t *pszDefExt = NULL);

class ApplicationFile
{
public:
	ApplicationFile(const wchar_t *pszFile);

	const wchar_t *c_str() const;
	operator const wchar_t *() const;

private:
	wchar_t Path[MAX_PATH];
	bool Ready;
};

#endif