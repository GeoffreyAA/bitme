#include "stdafx.h"
#include "VAlloc.h"

VAlloc::VAlloc(DWORD n) : p(NULL), dwSize(0)
{
	p = VirtualAlloc(NULL, n, MEM_COMMIT, PAGE_READWRITE);

	if (p)
	{
		dwSize = n;
	}
}

VAlloc::~VAlloc()
{
	if (p)
	{
		VirtualFree(p, dwSize, MEM_DECOMMIT);
		VirtualFree(p, 0, MEM_RELEASE);
	}
}

void *VAlloc::ptr()
{
	return (p);
}

VAlloc::operator void *()
{
	return (p);
}