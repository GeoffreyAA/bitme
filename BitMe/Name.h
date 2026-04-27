#ifndef __NAME_H__
#define __NAME_H__

#include <stddef.h>
#include "Library\String.h"

//  General Relativity 5.1 (Build 2600) (x86)

wchar_t *GetApplicationNameFull(wchar_t *c, size_t cbSize);
String GetApplicationNameFull();


//  General Relativity
//  Version 5.1 (Build 2600) (x86) (MSVC 1200)
//  (C) Albert Einstein, 1916. All rights reserved.
//
//  Compiled on <Date>
//
//  Licence: <Name or summary of licence>

wchar_t *GetApplicationNameEx(wchar_t *c, size_t cbSize);
String GetApplicationNameEx();

#endif