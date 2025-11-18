#include "stdafx.h"
#include "FilePointer.h"

FilePointer::FilePointer(FILE *fp) : f(fp)
{
}

FilePointer::~FilePointer()
{
	if (f)
	{
		fclose(f);
	}
}

FILE *FilePointer::ptr() const
{
	return (f);
}

FILE *FilePointer::detach()
{
	FILE *tmp = f;

	f = NULL;

	return (tmp);
}

FilePointer::operator FILE *() const
{
	return (ptr());
}