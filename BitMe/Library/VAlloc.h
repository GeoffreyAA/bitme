#ifndef __V_ALLOC_H__
#define __V_ALLOC_H__

#include <windows.h>

class VAlloc
{
public:
	VAlloc(DWORD n);
	~VAlloc();

	void *ptr();
	operator void *();

private:
	VAlloc(const VAlloc &);
	VAlloc& operator=(const VAlloc &);

private:
	void *p;
	DWORD dwSize;
};

#endif