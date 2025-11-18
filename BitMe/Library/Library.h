#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <stddef.h>

wchar_t *wcscpys(wchar_t *strDestination, const wchar_t *strSource, size_t cbSize);
int swprintfs(wchar_t *c, size_t cbSize, const wchar_t *Format, ...);

wchar_t *IntToStr(int x, wchar_t *c, size_t cbSize);
wchar_t *FloatToStr(double x, wchar_t *c, size_t cbSize, const wchar_t *Format = L"%.16g");

wchar_t *StringDelete(wchar_t *s, size_t i);
wchar_t *Trim(wchar_t *s);
wchar_t *TrimLeft(wchar_t *s);
wchar_t *TrimRight(wchar_t *s);
wchar_t *RemoveNonNbrs(wchar_t *s);

bool ContainsText(const wchar_t *s);
bool IsNumber(const wchar_t *s);

#endif