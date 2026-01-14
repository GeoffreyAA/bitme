#include "stdafx.h"
#include "Report.h"

#include <stdio.h>
#include "Application.h"
#include "TmpLibrary.h"
#include "Calculation\Information.h"
#include "Library\HtmlWriter.h"
#include "Library\ResourceString.h"
#include "Library\String.h"
#include "Library\StrW.h"
#include "Library\Win32Library.h"

StrUTF8 ResourceStringUTF8(const wchar_t *pszName)
{
	String s(ResourceString(pszName).c_str());

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

	return (s.c_str());
}

bool SaveReport(const wchar_t *pszFile, const BitrateModel &m)
{
	if (pszFile)
	{
		FILE *f = _wfopen(pszFile, L"wb");

		if (f)
		{
			fprintf(f, "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"\n\t\"http://www.w3.org/TR/html4/strict.dtd\">\n\n");

			fprintf(f, "<html>\n\n");

			fprintf(f, "<head>\n");
			fprintf(f, "<title>%s</title>\n", ResourceStringUTF8(L"IDS_REPORT").c_str());
			fprintf(f, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
			fprintf(f, "</head>\n\n");

			fprintf(f, "<body>\n\n");

			wchar_t w[128];

			fprintf(f, "<h1>%s</h1>\n\n", ResourceStringUTF8(L"IDS_REPORT").c_str());
			fprintf(f, "<p>%s</p>\n\n", GetDateTimeFormatted(w, sizeof(w) / sizeof(w[0]), NULL) ? StrUTF8(w).c_str() : ResourceStringUTF8(L"IDS_ERROR").c_str());

			fprintf(f, "<p>");
			fprintf(f, "%s %s; ", ResourceStringUTF8(L"IDS_REPORT_VIDEO").c_str(), m.isVideoEnabled() ? ResourceStringUTF8(L"IDS_REPORT_ENABLED").c_str() : ResourceStringUTF8(L"IDS_REPORT_DISABLED").c_str());
			fprintf(f, "%s %s; ", ResourceStringUTF8(L"IDS_REPORT_AUDIO").c_str(), m.isAudioEnabled() ? ResourceStringUTF8(L"IDS_REPORT_ENABLED").c_str() : ResourceStringUTF8(L"IDS_REPORT_DISABLED").c_str());
			fprintf(f, "%s %s", ResourceStringUTF8(L"IDS_REPORT_OVERHEAD").c_str(), m.isOverheadEnabled() ? ResourceStringUTF8(L"IDS_REPORT_ENABLED").c_str() : ResourceStringUTF8(L"IDS_REPORT_DISABLED").c_str());
			fprintf(f, "</p>\n");

			fprintf(f, "<p>");
			fprintf(f, "%s: %s", ResourceStringUTF8(L"IDS_INFORMATION_CONTAINER").c_str(), StrUTF8(m.getContainer().getName().c_str()).c_str());
			//fprintf(f, "%s: %s; ", ResourceStringUTF8(L"IDS_INFORMATION_VIDEO_FORMAT").c_str(), StrUTF8(m.getContainer().getVideoInterface().getName().c_str()).c_str());
			//fprintf(f, "%s: %s", ResourceStringUTF8(L"IDS_INFORMATION_AUDIO_FORMAT").c_str(), StrUTF8(m.getContainer().getAudioInterface().getName().c_str()).c_str());
			fprintf(f, "</p>\n");

			fprintf(f, "<p>");
			fprintf(f, "%s: %d %s; ", ResourceStringUTF8(L"IDS_INFORMATION_VIDEO_BITRATE").c_str(), m.getVideoBitrate(), ResourceStringUTF8(L"IDS_INFORMATION_KBPS").c_str());
			fprintf(f, "%s: %d %s; ", ResourceStringUTF8(L"IDS_INFORMATION_AUDIO_BITRATE").c_str(), m.getAudioBitrate(), ResourceStringUTF8(L"IDS_INFORMATION_KBPS").c_str());
			fprintf(f, "%s: %d %s", ResourceStringUTF8(L"IDS_INFORMATION_DURATION").c_str(), m.getDuration(), ResourceStringUTF8(L"IDS_INFORMATION_SECONDS").c_str());
			fprintf(f, "</p>\n\n");

			fprintf(f, "<p>%s: %s %s / %s %s / %s %s</p>\n", ResourceStringUTF8(L"IDS_INFORMATION_FILE_SIZE").c_str(), StrUTF8(FloatToStr2(Information(m.getFileSize()).getBytes()).c_str()).c_str(), ResourceStringUTF8(L"IDS_INFORMATION_BYTES").c_str(),
																													   StrUTF8(FloatToStr2(Information(m.getFileSize()).getMB()).c_str()).c_str(), ResourceStringUTF8(L"IDS_MB").c_str(),
																													   StrUTF8(FloatToStr2(Information(m.getFileSize()).getGB()).c_str()).c_str(), ResourceStringUTF8(L"IDS_GB").c_str());

			fprintf(f, "<p>%s: %s %s</p>\n", ResourceStringUTF8(L"IDS_INFORMATION_DATA_RATE").c_str(), StrUTF8(FloatToStr2(Information(m.getDataRate()).getBytes()).c_str()).c_str(), ResourceStringUTF8(L"IDS_INFORMATION_BYTES_SEC").c_str());
			fprintf(f, "<p>%s: %s</p>\n\n", ResourceStringUTF8(L"IDS_INFORMATION_OVERHEAD").c_str(), StrUTF8(FloatToStr2(m.getOverhead()).c_str()).c_str());

			fprintf(f, "</body>\n\n");
			fprintf(f, "</html>");

			fclose(f);

			return true;
		}
	}

	return false;
}

bool __SaveReport(const wchar_t *pszFile, const BitrateModel &m)
{
	HtmlWriter f(pszFile, HtmlWriter::MODE_UTF8, ResourceString(L"IDS_REPORT"));

	if (f.IsReady())
	{
		wchar_t w[128];

		f << "<h1>" << ResourceString(L"IDS_REPORT").c_str() << " (" << (GetDateTimeFormatted(w, sizeof(w) / sizeof(w[0]), NULL) ? w : ResourceString(L"IDS_ERROR").c_str()) << ")</h1>\n\n";

		f << "<p>" << ResourceString(L"IDS_INFORMATION_VIDEO_BITRATE").c_str() << ": " << m.getVideoBitrate() << " " << ResourceString(L"IDS_INFORMATION_KBPS").c_str() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_AUDIO_BITRATE").c_str() << ": " << m.getAudioBitrate() << " " << ResourceString(L"IDS_INFORMATION_KBPS").c_str() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_DURATION").c_str() << ": " << m.getDuration() << " " << ResourceString(L"IDS_INFORMATION_SECONDS").c_str() << "</p>\n\n";

		f << "<p>" << ResourceString(L"IDS_INFORMATION_VIDEO_ENABLED").c_str() << ": " << m.isVideoEnabled() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_AUDIO_ENABLED").c_str() << ": " << m.isAudioEnabled() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_OVERHEAD_ENABLED").c_str() << ": " << m.isOverheadEnabled() << "</p>\n\n";

		f << "<p>" << ResourceString(L"IDS_INFORMATION_FILE_SIZE").c_str() << ": " << FloatToStr2(Information(m.getFileSize()).getBytes()).c_str() << " " << ResourceString(L"IDS_INFORMATION_BYTES").c_str() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_DATA_RATE").c_str() << ": " << FloatToStr2(Information(m.getDataRate()).getBytes()).c_str() << " " << ResourceString(L"IDS_INFORMATION_BYTES_SEC").c_str() << "</p>\n";
		f << "<p>" << ResourceString(L"IDS_INFORMATION_OVERHEAD").c_str() << ": " << FloatToStr2(m.getOverhead()).c_str() << "</p>\n\n";

		f << "<p>" << ResourceString(L"IDS_INFORMATION_CONTAINER").c_str() << ": " << m.getContainer().getName().c_str() << "</p>\n";
		//f << "<p>" << ResourceString(L"IDS_INFORMATION_VIDEO_FORMAT").c_str() << ": " << m.getContainer().getVideoInterface().getName().c_str() << "</p>\n";
		//f << "<p>" << ResourceString(L"IDS_INFORMATION_AUDIO_FORMAT").c_str() << ": " << m.getContainer().getAudioInterface().getName().c_str() << "</p>\n\n";

		f.Close();

		return true;
	}

	return false;
}