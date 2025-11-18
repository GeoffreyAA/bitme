#ifndef __BUILD_INFORMATION_H__
#define __BUILD_INFORMATION_H__

#include <time.h>

class BuildInformation
{
public:
	BuildInformation();

	int GetBuildNumber() const;
	void SetBuildNumber(int n);
	void IncrementBuildNumber();

	time_t GetBuildTime() const;
	void SetBuildTime(time_t t);

private:
	int BuildNumber;
	time_t BuildTime;
};

bool ReadBuildInformation(const char *pszFile, BuildInformation &b);
bool WriteBuildInformation(const char *pszFile, const BuildInformation &b);
bool WriteBuildInformationSrc(const char *pszFile, const BuildInformation &b);

#endif