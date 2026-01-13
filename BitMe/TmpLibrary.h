#ifndef __TMP_LIBRARY_H__
#define __TMP_LIBRARY_H__

#include <windows.h>
#include "Library\String.h"
#include "Library\Types.h"

void SetWindowInt2(HWND hWnd, int x);
void SetWindowInt4(HWND hWnd, int x);
void SetWindowFloat2(HWND hWnd, double x, const wchar_t *pszFormat);
void SetWindowTextRange(HWND hWnd, int x, const wchar_t *pszString);

double BitsToKilobits(double x);
double BitsToMegabits(double x);
String FloatToStr2(double x);
uint32 Clamp64To32(uint64 x);

#endif