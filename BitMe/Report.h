#ifndef __REPORT_H__
#define __REPORT_H__

#include <stddef.h>
#include "Calculation\BitrateModel.h"

bool SaveReport(const wchar_t *pszFile, const BitrateModel &m);

#endif