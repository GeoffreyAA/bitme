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

	int getInteger(const wchar_t *name, int def = -1) const;
	double getFloat(const wchar_t *name, double def = -1.0) const;
	bool getBool(const wchar_t *name, bool def = false) const;
	char *getString(const wchar_t *name, char *value, size_t size) const;
	wchar_t *getString(const wchar_t *name, wchar_t *value, size_t size) const;
	void *getBinary(const wchar_t *name, void *value, size_t bytes) const;

	bool setInteger(const wchar_t *name, int value);
	bool setFloat(const wchar_t *name, double value);
	bool setBool(const wchar_t *name, bool value);
	bool setString(const wchar_t *name, const char *value);
	bool setString(const wchar_t *name, const wchar_t *value);
	bool setBinary(const wchar_t *name, const void *value, size_t bytes);

	bool deleteValue(const wchar_t *name);

protected:
	bool get(const wchar_t *name, String &value) const;
	bool put(const wchar_t *name, const String &value);

private:
	StringDictionary d;
	String f;
};

#endif