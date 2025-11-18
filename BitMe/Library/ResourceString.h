#ifndef __RESOURCE_STRING_H__
#define __RESOURCE_STRING_H__

#include <stddef.h>
#include "String.h"

class ResourceString
{
public:
	ResourceString(const wchar_t *pszName);

	const wchar_t *c_str() const;
	operator const wchar_t *() const;

private:
	String s;
};

#endif