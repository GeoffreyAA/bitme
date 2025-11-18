#ifndef __FILE_H__
#define __FILE_H__

#include <stddef.h>

const wchar_t *GetFileName(const wchar_t *pszPath);
const wchar_t *GetFileExt(const wchar_t *pszPath);
bool GetRootFromPath(wchar_t *pszBuffer, size_t cbSize, const wchar_t *pszPath);
wchar_t *RemovePath(wchar_t *pszPath);
wchar_t *RemoveFileName(wchar_t *pszPath);
wchar_t *RemoveFileExt(wchar_t *pszPath);
bool AddFileName(wchar_t *pszPath, const wchar_t *pszFileName, size_t cbSize);
bool AddFileExt(wchar_t *pszPath, const wchar_t *pszFileExt, size_t cbSize);

bool GetProgramPath(wchar_t *pszBuffer, size_t cbSize);

#endif