#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <wchar.h>
#include "String.h"

const wchar_t *GetPlatform();
const wchar_t *GetCompilerName();
String GetCompilerVersion();
String GetCompilerVersionFull();

#endif