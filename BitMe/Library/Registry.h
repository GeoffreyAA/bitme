#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include "Configuration.h"
#include <windows.h>

class Registry : public Configuration
{
public:
	Registry();
	Registry(HKEY hKey);
	Registry(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate);
	Registry(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate);
	~Registry();

	bool Open(const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate);
	bool Open(HKEY hKey, const wchar_t *pszSubKey, REGSAM samDesired, bool bCreate);
	bool Close();
	bool Attach(HKEY hKey);
	HKEY Detach();
	bool IsReady() const;
	HKEY GetHandle() const;

	bool GetInt(const wchar_t *name, int &value) const;
	bool GetFloat(const wchar_t *name, double &value) const;
	bool GetBool(const wchar_t *name, bool &value) const;
	bool GetString(const wchar_t *name, char *value, size_t size) const;
	bool GetString(const wchar_t *name, wchar_t *value, size_t size) const;
	bool GetString(const wchar_t *name, String &value) const;
	bool GetBinary(const wchar_t *name, void *value, size_t bytes) const;

	bool SetInt(const wchar_t *name, int value);
	bool SetFloat(const wchar_t *name, double value);
	bool SetBool(const wchar_t *name, bool value);
	bool SetString(const wchar_t *name, const char *value);
	bool SetString(const wchar_t *name, const wchar_t *value);
	bool SetString(const wchar_t *name, const String &value);
	bool SetBinary(const wchar_t *name, const void *value, size_t bytes);

	bool Delete(const wchar_t *name);

private:
	Registry(const Registry &);
	Registry& operator=(const Registry &);

private:
	HKEY h;
};

#endif