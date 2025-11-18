#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <stddef.h>

class Configuration
{
public:
	virtual int getInteger(const wchar_t *pszName, int nDefault = -1) const = 0;
	virtual double getFloat(const wchar_t *pszName, double fDefault = -1.0) const = 0;
	virtual bool getBool(const wchar_t *pszName, bool bDefault = false) const = 0;
	virtual char *getString(const wchar_t *pszName, char *pszBuffer, size_t cbSize) const = 0;
	virtual wchar_t *getString(const wchar_t *pszName, wchar_t *pszBuffer, size_t cbSize) const = 0;
	virtual void *getBinary(const wchar_t *pszName, void *pBuffer, size_t nBytes) const = 0;

	virtual bool setInteger(const wchar_t *pszName, int nValue) = 0;
	virtual bool setFloat(const wchar_t *pszName, double fValue) = 0;
	virtual bool setBool(const wchar_t *pszName, bool bValue) = 0;
	virtual bool setString(const wchar_t *pszName, const char *pszString) = 0;
	virtual bool setString(const wchar_t *pszName, const wchar_t *pszString) = 0;
	virtual bool setBinary(const wchar_t *pszName, const void *pData, size_t nBytes) = 0;

	virtual bool deleteValue(const wchar_t *pszName) = 0;

	virtual ~Configuration() {}
};

#endif