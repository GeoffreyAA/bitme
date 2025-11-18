#ifndef __TMP_LIBRARY_H__
#define __TMP_LIBRARY_H__

#include <windows.h>
#include "Library\String.h"

int GetWindowRight(HWND hWnd);
void SetWindowFloat2(HWND hWnd, double x, const wchar_t *pszFormat);
//void SetWindowInt3(HWND hWnd, int x);
void SetWindowTextRange(HWND hWnd, int x, const wchar_t *pszString);
//void SetWindowInt(HWND hWnd, int x);
void SetWindowInt2(HWND hWnd, int x);
//int GetWindowInt(HWND hWnd);
//void SetWindowFont(HWND hWnd, HFONT hFont);
//void SetDlgItemCheck(HWND hDlg, int nID, bool bCheck);
//bool GetDlgItemChecked(HWND hDlg, int nID);

void SetWindowInt4(HWND hWnd, int x);

double BitsToKilobits(double x);
double BitsToMegabits(double x);

String FloatToStr2(double x);

//bool GetMenuItemChecked(HMENU hMenu, UINT uID);
//void SetMenuItemCheck(HMENU hMenu, UINT uID, bool bCheck);
//void SetMenuStringByCommand(HMENU hMnu, UINT uID, const wchar_t *pszString);

//String GetMenuItemSelected(HMENU hMenu, const UINT IDs[], int n);
//void SelectMenuItem(HMENU hMenu, const UINT IDs[], int n, const wchar_t *s);
//bool SelectMenuItemID(HMENU hMenu, const UINT IDs[], int n, UINT uID);
//void EnableMenuItems(HMENU hMenu, const UINT IDs[], int n, bool b);
//void SetMenuStrings(HMENU hMenu, const UINT IDs[], int n, const StringList &s);

/*
template <class T>
inline bool ToBool(const T &val)
{
	return (val != 0);
}
*/


#endif