#include "stdafx.h"
#include "Glue.h"
#include "Library\Library.h"

#ifdef _AFXDLL

bool HtmlHelp(const wchar_t *pszFile, const wchar_t *pszPage, HWND hOwner)
{
	HINSTANCE h = AfxLoadLibrary(L"hhctrl.ocx");

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