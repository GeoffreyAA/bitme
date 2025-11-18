#include "stdafx.h"
#include "Font.h"
#include "Win32Library.h"

Font::Font() : h(NULL)
{
}

Font::Font(const wchar_t *pszName, int nPointSize, bool bBold, bool bItalic, bool bUnderline, bool bStrikeOut) : h(NULL)
{
	Create(pszName, nPointSize, bBold, bItalic, bUnderline, bStrikeOut);
}

Font::~Font()
{
	Delete();
}

bool Font::Create(const wchar_t *pszName, int nPointSize, bool bBold, bool bItalic, bool bUnderline, bool bStrikeOut)
{
	if (Delete())
	{
		h = CreatePointFont(pszName, nPointSize, bBold, bItalic, bUnderline, bStrikeOut);

		return (h != NULL);
	}

	return false;
}

bool Font::Delete()
{
	if (h)
	{
		if (DeleteObject(h))
		{
			h = NULL;
		}
	}

	return (h == NULL);
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

	return (tmp);
}

bool Font::IsReady() const
{
	return (GetFont() != NULL);
}

HFONT Font::GetFont() const
{
	return (h);
}