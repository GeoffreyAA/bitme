#include <iostream>
#include <time.h>
#include "BuildInformation.h"

using namespace std;

const char sBuildFile[] = "Build.rad";
const char sBuildSrcFile[] = "Build.c";

int main()
{
	cout << "Incrementing build number" << endl;

	BuildInformation b;

	if (!ReadBuildInformation(sBuildFile, b))
	{
		cout << "Cannot open \"" << sBuildFile << "\" Starting new build history." << endl;

		b = BuildInformation();
	}

	cout << "Build number is: " << b.GetBuildNumber() << endl;

	b.SetBuildTime(time(0));

	const BuildInformation old = b;

	b.IncrementBuildNumber();

	if (WriteBuildInformation(sBuildFile, b))
	{
		cout << "Incremented to: " << b.GetBuildNumber() << endl;
	}
	else
	{
		cout << "Cannot write to \"" << sBuildFile << "\"" << endl;

		b = old;
	}

	if (!WriteBuildInformationSrc(sBuildSrcFile, b))
	{
		cout << "Cannot write to \"" << sBuildSrcFile << "\"" << endl;
	}

	return (0);
}