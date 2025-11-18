#ifndef __FONT_H__
#define __FONT_H__

#include <windows.h>

class Font
{
public:
	Font();
	Font(const wchar_t *pszName, int nPointSize, bool bBold, bool bItalic, bool bUnderline, bool bStrikeOut);
	~Font();

	bool Create(const wchar_t *pszName = NULL, int nPointSize = 10, bool bBold = false, bool bItalic = false, bool bUnderline = false, bool bStrikeOut = false);
	bool Delete();

	bool Attach(HFONT hFont);
	HFONT Detach();

	bool IsReady() const;

	HFONT GetFont() const;

private:
	Font(const Font &);
	Font& operator=(const Font &);

private:
	HFONT h;
};

#endif