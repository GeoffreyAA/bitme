#include "stdafx.h"
#include "Font.h"
#include "Library.h"
#include "Win32Library.h"

Font::Font() : h(NULL)
{
}

Font::~Font()
{
	Delete();
}

bool Font::Create(const wchar_t *pszName, int nPointSize, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut)
{
	if (Delete())
	{
		h = CreatePointFont(pszName, nPointSize, nWeight, bItalic, bUnderline, bStrikeOut);

		return h != NULL;
	}

	return false;
}

bool Font::Create(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutputPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFace)
{
	if (Delete())
	{
		wchar_t fn[32] = L"";

		if (pszFace)
			wcscpys(fn, sizeof(fn) / sizeof(fn[0]), pszFace);

		h = CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutputPrecision, iClipPrecision, iQuality, iPitchAndFamily, fn);

		return h != NULL;
	}

	return false;
}

bool Font::Create(const LOGFONT *lpLogFont)
{
	if (Delete())
	{
		h = CreateFontIndirect(lpLogFont);

		return h != NULL;
	}

	return false;
}

bool Font::Delete()
{
	if (h)
	{
		if (DeleteObject(h))
			h = NULL;
	}

	return h == NULL;
}

bool Font::Attach(HFONT hFont)
{
	if (!h)
	{
		if (hFont)
		{
			h = hFont;

			return true;
		}
	}

	return false;
}

HFONT Font::Detach()
{
	HFONT tmp = h;

	h = NULL;

	return tmp;
}

bool Font::IsReady() const
{
	return GetFont() != NULL;
}

HFONT Font::GetFont() const
{
	return h;
}

bool Font::GetLogFont(LOGFONT *lpLogFont) const
{
	return GetObject(GetFont(), sizeof(LOGFONT), lpLogFont) != 0;
}