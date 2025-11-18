#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stddef.h>

class Alloc
{
public:
	Alloc(size_t bytes);
	~Alloc();

	void *ptr();
	operator void *();

private:
	Alloc(const Alloc &);
	Alloc& operator=(const Alloc &);

private:
	void *p;
};

#endif