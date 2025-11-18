#include "stdafx.h"
#include "Alloc.h"
#include <malloc.h>

Alloc::Alloc(size_t bytes) : p(NULL)
{
	p = malloc(bytes);
}

Alloc::~Alloc()
{
	if (p)
	{
		free(p);
	}
}

void *Alloc::ptr()
{
	return (p);
}

Alloc::operator void *()
{
	return (p);
}