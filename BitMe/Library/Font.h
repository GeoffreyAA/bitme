#ifndef __FONT_H__
#define __FONT_H__

#include <windows.h>

class Font
{
public:
	Font();
	~Font();

	bool Create(const wchar_t *pszName = NULL, int nPointSize = 10, int nWeight = FW_NORMAL, bool bItalic = false, bool bUnderline = false, bool bStrikeOut = false);
	bool Create(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutputPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFace);
	bool Create(const LOGFONT *lpLogFont);
	bool Delete();

	bool Attach(HFONT hFont);
	HFONT Detach();
	bool IsReady() const;
	HFONT GetFont() const;

	bool GetLogFont(LOGFONT *lpLogFont) const;

private:
	Font(const Font &);
	Font& operator=(const Font &);

private:
	HFONT h;
};

#endif