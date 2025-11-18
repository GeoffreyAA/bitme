#include "BuildInformation.h"
#include <fstream>

BuildInformation::BuildInformation() : BuildNumber(0), BuildTime(0)
{
}

int BuildInformation::GetBuildNumber() const
{
	return (BuildNumber);
}

void BuildInformation::SetBuildNumber(int n)
{
	BuildNumber = n;
}

void BuildInformation::IncrementBuildNumber()
{
	BuildNumber++;
}

time_t BuildInformation::GetBuildTime() const
{
	return (BuildTime);
}

void BuildInformation::SetBuildTime(time_t t)
{
	BuildTime = t;
}


///////////////////////////////////////////////////////////////

bool ReadBuildInformation(const char *pszFile, BuildInformation &b)
{
	if (pszFile)
	{
		std::ifstream fin(pszFile);

		if (fin)
		{
			int n;
			time_t t;

			fin >> n >> t;

			b.SetBuildNumber(n);
			b.SetBuildTime(t);

			fin.close();

			return true;
		}
	}

	return false;
}

bool WriteBuildInformation(const char *pszFile, const BuildInformation &b)
{
	if (pszFile)
	{
		std::ofstream fout(pszFile);

		if (fout)
		{
			fout << b.GetBuildNumber() << " " << b.GetBuildTime();

			fout.close();

			return true;
		}
	}

	return false;
}

bool WriteBuildInformationSrc(const char *pszFile, const BuildInformation &b)
{
	if (pszFile)
	{
		std::ofstream fout(pszFile);

		if (fout)
		{
			fout << "#include <time.h>\n\n"
				 << "const int build_number = " << b.GetBuildNumber() << ";\n"
				 << "const time_t build_time = " << b.GetBuildTime() << ";";

			fout.close();

			return true;
		}
	}

	return false;
}