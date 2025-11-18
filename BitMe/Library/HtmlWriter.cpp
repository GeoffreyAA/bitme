#include "stdafx.h"
#include "HtmlWriter.h"
#include "String.h"
#include <string>
#include "StrW.h"
#include <assert.h>

String Transform(const wchar_t *pszString)
{
	String s(pszString);

	for (String::size_type i = 0; i < s.size(); i++)
	{
		if (s[i] == L'<')
		{
			s[i] = L'[';
		}
		else if (s[i] == L'>')
		{
			s[i] = L']';
		}
	}

	return (s);
}

std::string Transform(const char *pszString)
{
	std::string s(pszString);

	for (std::string::size_type i = 0; i < s.size(); i++)
	{
		if (s[i] == '<')
		{
			s[i] = '[';
		}
		else if (s[i] == '>')
		{
			s[i] = ']';
		}
	}

	return (s);
}

HtmlWriter::HtmlWriter(const wchar_t *pszFile, Mode mode, const wchar_t *pszTitle) : f(NULL), m(mode)
{
	if (pszFile)
	{
		f = _wfopen(pszFile, L"wb");

		if (f)
		{
			if ((m == MODE_ANSI) || (m == MODE_UTF8))
			{
				fprintf(f, "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"\n\t\"http://www.w3.org/TR/html4/strict.dtd\">\n\n");
				fprintf(f, "<html>\n\n<head>\n");

				if (m == MODE_UTF8)
				{
					fprintf(f, "<title>%s</title>\n", StrUTF8(Transform(pszTitle).c_str()).c_str());
					fprintf(f, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
				}
				else
				{
					fprintf(f, "<title>%s</title>\n", StrA(Transform(pszTitle).c_str()).c_str());
					fprintf(f, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\">\n");
				}

				fprintf(f, "</head>\n\n<body>\n\n");
			}
			else if (m == MODE_UTF16)
			{
				fwprintf(f, L"%c", 0xFEFF);

				fwprintf(f, L"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"\n\t\"http://www.w3.org/TR/html4/strict.dtd\">\n\n");

				fwprintf(f, L"<html>\n\n");

				fwprintf(f, L"<head>\n");
				fwprintf(f, L"<title>%s</title>\n", Transform(pszTitle).c_str());
				fwprintf(f, L"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-16le\">\n");
				fwprintf(f, L"</head>\n\n");

				fwprintf(f, L"<body>\n\n");
			}
			else
			{
				assert(false);
			}
		}
	}
}

HtmlWriter::~HtmlWriter()
{
	Close();
}

void HtmlWriter::Close()
{
	if (f)
	{
		if ((GetMode() == MODE_ANSI) || (GetMode() == MODE_UTF8))
		{
			fprintf(f, "</body>\n\n</html>");
		}
		else if (GetMode() == MODE_UTF16)
		{
			fwprintf(f, L"</body>\n\n</html>");
		}
		else
		{
			assert(false);
		}

		fclose(f);

		f = NULL;
	}
}

HtmlWriter::Mode HtmlWriter::GetMode() const
{
	return (m);
}

bool HtmlWriter::IsReady() const
{
	return (f != NULL);
}

void HtmlWriter::WriteString(const char *s)
{
	if (f && s)
	{
		switch (GetMode())
		{
			case MODE_ANSI:
			case MODE_UTF8:
				fprintf(f, "%s", Transform(s).c_str());
				break;

			case MODE_UTF16:
				fwprintf(f, L"%s", Transform(StrW(s)).c_str());
				break;
		}
	}
}

void HtmlWriter::WriteString(const wchar_t *s)
{
	if (f && s)
	{
		switch (GetMode())
		{
			case MODE_ANSI:
				fprintf(f, "%s", StrA(Transform(s).c_str()).c_str());
				break;

			case MODE_UTF8:
				fprintf(f, "%s", StrUTF8(Transform(s).c_str()).c_str());
				break;

			case MODE_UTF16:
				fwprintf(f, L"%s", Transform(s).c_str());
				break;
		}
	}
}

HtmlWriter& HtmlWriter::operator<<(const char *s)
{
	WriteString(s);

	return *this;
}

HtmlWriter& HtmlWriter::operator<<(const wchar_t *s)
{
	WriteString(s);

	return *this;
}

HtmlWriter& HtmlWriter::operator<<(int x)
{
	if (f)
	{
		switch (GetMode())
		{
			case MODE_ANSI:
			case MODE_UTF8:
				fprintf(f, "%d", x);
				break;

			case MODE_UTF16:
				fwprintf(f, L"%d", x);
				break;
		}
	}

	return *this;
}

HtmlWriter& HtmlWriter::operator<<(double x)
{
	if (f)
	{
		switch (GetMode())
		{
			case MODE_ANSI:
			case MODE_UTF8:
				fprintf(f, "%.16g", x);
				break;

			case MODE_UTF16:
				fwprintf(f, L"%.16g", x);
				break;
		}
	}

	return *this;
}