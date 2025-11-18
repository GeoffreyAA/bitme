#ifndef __UNICODE_H__
#define __UNICODE_H__

#include <stddef.h>

bool ConvertUTF8To16(wchar_t *pszBuffer, size_t cbSize, const char *s);
bool ConvertUTF16To8(char *pszBuffer, size_t cbSize, const wchar_t *s);

#endif