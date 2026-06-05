#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <stddef.h>

wchar_t *wcscpys(wchar_t *dst, size_t size, const wchar_t *src);

wchar_t *IntToStr(int x, wchar_t *c, size_t cbSize);
wchar_t *FloatToStr(double x, wchar_t *c, size_t cbSize, const wchar_t *Format = L"%.16g");

wchar_t *StringDelete(wchar_t *s, size_t i);
wchar_t *Trim(wchar_t *s);
wchar_t *TrimLeft(wchar_t *s);
wchar_t *TrimRight(wchar_t *s);
wchar_t *Strip(wchar_t *s);
wchar_t *ReplaceChars(wchar_t *s, wchar_t from, wchar_t to);
wchar_t *RemoveNonNbrs(wchar_t *s);

bool ContainsText(const wchar_t *s);
bool IsNumber(const wchar_t *s);

#endif