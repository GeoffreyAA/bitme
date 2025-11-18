#ifndef __STR_W_H__
#define __STR_W_H__

#include <stddef.h>

// Converts an Ansi or UTF-8 string to UTF-16
//
// If the source string is NULL, or if there is an error, the
// resulting string is NULL. The c_str() function returns a
// pointer to the resulting string, and the const wchar_t *
// operator is equivalent to c_str(). Memory is allocated
// dynamically.

class StrW
{
public:
	StrW(const char *a);
	~StrW();

	const wchar_t *c_str() const;
	operator const wchar_t *() const;

private:
	StrW(const StrW &);
	StrW& operator=(const StrW &);

private:
	wchar_t *w;
};

// Converts a UTF-16 string to Ansi
//
// If the source string is NULL, or if there is an error, the
// resulting string is NULL. The c_str() function returns a
// pointer to the resulting string, and the const char *
// operator is equivalent to c_str(). Memory is allocated
// dynamically.

class StrA
{
public:
	StrA(const wchar_t *w);
	~StrA();

	const char *c_str() const;
	operator const char *() const;

private:
	StrA(const StrA &);
	StrA& operator=(const StrA &);

private:
	char *a;
};

// Converts a UTF-16 string to UTF-8
//
// If the source string is NULL, or if there is an error, the
// resulting string is an empty but valid string. The c_str()
// function returns a pointer to the resulting string, and
// the const char * operator is equivalent to c_str().
// Memory is allocated dynamically.

class StrUTF8
{
public:
	StrUTF8(const wchar_t *w);
	~StrUTF8();

	const char *c_str() const;
	operator const char *() const;

private:
	StrUTF8(const StrUTF8 &);
	StrUTF8& operator=(const StrUTF8 &);

private:
	char *a;
};

#endif