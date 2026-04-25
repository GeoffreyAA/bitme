#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <stddef.h>
#include "String.h"

const wchar_t *GetPlatform();
const wchar_t *GetCompilerName();
String GetCompilerVersion();
String GetCompilerVersionFull();

#endif