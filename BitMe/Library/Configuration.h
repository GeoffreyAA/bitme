#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <stddef.h>

class Configuration
{
public:
	virtual bool GetInt(const wchar_t *name, int &value) const = 0;
	virtual bool GetFloat(const wchar_t *name, double &value) const = 0;
	virtual bool GetBool(const wchar_t *name, bool &value) const = 0;
	virtual bool GetString(const wchar_t *name, char *value, size_t size) const = 0;
	virtual bool GetString(const wchar_t *name, wchar_t *value, size_t size) const = 0;
	virtual bool GetBinary(const wchar_t *name, void *value, size_t bytes) const = 0;

	virtual bool SetInt(const wchar_t *name, int value) = 0;
	virtual bool SetFloat(const wchar_t *name, double value) = 0;
	virtual bool SetBool(const wchar_t *name, bool value) = 0;
	virtual bool SetString(const wchar_t *name, const char *value) = 0;
	virtual bool SetString(const wchar_t *name, const wchar_t *value) = 0;
	virtual bool SetBinary(const wchar_t *name, const void *value, size_t bytes) = 0;

	virtual bool Delete(const wchar_t *name) = 0;

	virtual ~Configuration() {}
};

#endif