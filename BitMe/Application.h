#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <stddef.h>
#include <time.h>
#include "Library\String.h"

const wchar_t *GetApplicationName();
const wchar_t *GetApplicationVersion();
const wchar_t *GetRegistryKey();
const wchar_t *GetHelpFileName();
String GetApplicationNameFull();
String GetApplicationNameFull2();

int GetBuildNumber();
time_t GetBuildTime();

#endif