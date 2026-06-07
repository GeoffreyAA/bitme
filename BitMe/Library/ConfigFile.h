#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__

#include "Configuration.h"
#include "StringDictionary.h"
#include "String.h"

class ConfigFile : public Configuration
{
public:
	ConfigFile(const wchar_t *file = L"Settings.cfg");
	~ConfigFile();

	bool GetInt(const wchar_t *name, int &value) const;
	bool GetFloat(const wchar_t *name, double &value) const;
	bool GetBool(const wchar_t *name, bool &value) const;
	bool GetString(const wchar_t *name, char *value, size_t size) const;
	bool GetString(const wchar_t *name, wchar_t *value, size_t size) const;
	bool GetBinary(const wchar_t *name, void *value, size_t bytes) const;

	bool SetInt(const wchar_t *name, int value);
	bool SetFloat(const wchar_t *name, double value);
	bool SetBool(const wchar_t *name, bool value);
	bool SetString(const wchar_t *name, const char *value);
	bool SetString(const wchar_t *name, const wchar_t *value);
	bool SetBinary(const wchar_t *name, const void *value, size_t bytes);

	bool Delete(const wchar_t *name);

protected:
	bool get(const wchar_t *name, String &value) const;
	bool put(const wchar_t *name, const wchar_t *value);

private:
	StringDictionary d;
	String fn;
	bool write;
};

#endif