#ifndef __FILE_POINTER_H__
#define __FILE_POINTER_H__

#include <stdio.h>

class FilePointer
{
public:
	FilePointer(FILE *fp);
	~FilePointer();

	FILE *ptr() const;
	FILE *detach();

	operator FILE *() const;

private:
	FilePointer(const FilePointer &);
	FilePointer& operator=(const FilePointer &);

private:
	FILE *f;
};

#endif