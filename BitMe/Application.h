#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <stddef.h>
#include <time.h>

const wchar_t *GetApplicationName();
const wchar_t *GetApplicationVersion();
int GetBuildNumber();
time_t GetBuildTime();
const wchar_t *GetCopyright();
const wchar_t *GetRegistryKey();
const wchar_t *GetHelpFileName();

#endif