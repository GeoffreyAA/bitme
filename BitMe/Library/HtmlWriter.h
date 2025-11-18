#ifndef __HTML_WRITER_H__
#define __HTML_WRITER_H__

#include <stddef.h>
#include <stdio.h>

class HtmlWriter
{
public:
	enum Mode { MODE_ANSI, MODE_UTF8, MODE_UTF16 };

	HtmlWriter(const wchar_t *pszFile, Mode mode = MODE_UTF8, const wchar_t *pszTitle = NULL);
	virtual ~HtmlWriter();

	void Close();

	Mode GetMode() const;
	bool IsReady() const;

	void WriteString(const char *s);
	void WriteString(const wchar_t *s);

	HtmlWriter& operator<<(const char *s);
	HtmlWriter& operator<<(const wchar_t *s);
	HtmlWriter& operator<<(int x);
	HtmlWriter& operator<<(double x);

private:
	HtmlWriter(const HtmlWriter &);
	HtmlWriter& operator=(const HtmlWriter &);

private:
	FILE *f;
	Mode m;
};

#endif