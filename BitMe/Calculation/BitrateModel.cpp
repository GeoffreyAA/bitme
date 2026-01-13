#include "stdafx.h"
#include "BitrateModel.h"
#include "Information.h"
#include "..\Library\Maths.h"
#include "..\Library\Library.h"
#include "..\TmpLibrary.h"
#include "..\Library\ResourceString.h"

BitrateModel::BitrateModel(int v, int a, int s) : Video(v), Audio(a), Seconds(s), bVideo(true), bAudio(true), bOverhead(true), pInterface(NULL)
{
}

BitrateModel::~BitrateModel()
{
	if (pInterface)
	{
		delete pInterface;
	}
}

int BitrateModel::getVideoBitrate() const
{
	return (Video);
}

int BitrateModel::getAudioBitrate() const
{
	return (Audio);
}

int BitrateModel::getDuration() const
{
	return (Seconds);
}

double BitrateModel::getFileSize() const
{
	const double v = isVideoEnabled() ? ((double)getVideoBitrate() * 1000.0) : 0.0;
	const double a = isAudioEnabled() ? ((double)getAudioBitrate() * 1000.0) : 0.0;

	return ((v + a) * (double)getDuration() + getOverhead());
}

double BitrateModel::getDataRate() const
{
	return (getFileSize() / (double)getDuration());
}

/*
double BitrateModel::getAVIOverhead() const
{
	if (isOverheadEnabled() && isVideoEnabled())
	{
		if (isAudioEnabled())
		{
			return (10240.0 * (double)getDuration());
		}
		else
		{
			return (5120.0 * (double)getDuration());
		}
	}

	return (0.0);
}
*/

double BitrateModel::getOverhead() const
{
	if (isOverheadEnabled() && isVideoEnabled())
	{
		if (isAudioEnabled())
		{
			return (getContainer().getOverheadFull(getVideoBitrate(), getAudioBitrate(), getDuration()));
		}
		else
		{
			return (getContainer().getOverheadNoAudio(getVideoBitrate(), getDuration()));
		}
	}

	return (0.0);
}

int BitrateModel::getVideoBitrateFromFileSize(double MB) const
{
	// bits = (Vb + Ab) * Ts + Ob;
	//
	// bits - Ob = (Vb + Ab) * Ts
	//
	// bits - Ob = Vb + Ab
	// ---------
	//     Ts
	//
	// bits - Ob - Ab = Vb
	// ---------
	//     Ts

	Information i;
	i.setMB(MB);

	double v = ((i.getBits() - getOverhead()) / (double)getDuration() - (isAudioEnabled() ? ((double)getAudioBitrate() * 1000.0) : 0.0));

	return Round(v / 1000.0);
}

int BitrateModel::getVideoBitrateFromDataRate(double kBps) const
{
	// bps = (Vb + Ab) * Ts + Ob
	//       -------------------
	//                Ts
	//
	// bps * Ts = (Vb + Ab) * Ts + Ob
	//
	// bps * Ts - Ob = (Vb + Ab) * Ts
	//
	// bps * Ts - Ob = Vb + Ab
	// -------------
	//      Ts
	//
	// bps * Ts - Ob - Ab = Vb
	// -------------
	//      Ts

	double bps = kBps * 1024.0 * 8.0;
	double a = isAudioEnabled() ? ((double)getAudioBitrate() * 1000.0) : 0.0;

	double vbps = (bps * (double)getDuration() - getOverhead()) / (double)getDuration() - a;

	return Round(vbps / 1000.0);
}

void BitrateModel::setVideoBitrate(int kbps)
{
	Video = kbps;
}

void BitrateModel::setAudioBitrate(int kbps)
{
	Audio = kbps;
}

void BitrateModel::setDuration(int seconds)
{
	Seconds = seconds;
}

void BitrateModel::enableVideo(bool b)
{
	bVideo = b;
}

void BitrateModel::enableAudio(bool b)
{
	bAudio = b;
}

void BitrateModel::enableOverhead(bool b)
{
	bOverhead = b;
}

bool BitrateModel::isVideoEnabled() const
{
	return (bVideo);
}

bool BitrateModel::isAudioEnabled() const
{
	return (bAudio);
}

bool BitrateModel::isOverheadEnabled() const
{
	return (bOverhead);
}

const ContainerInterface& BitrateModel::getContainer() const
{
	return (pInterface ? *pInterface : DefInterface);
}

void BitrateModel::setContainer(ContainerInterface *p)
{
	if (pInterface)
	{
		delete pInterface;
	}

	pInterface = p;
}

String BitrateModel::getInformation() const
{
	wchar_t w[1024];

	swprintfs(w, sizeof(w) / sizeof(w[0]), L"%s: %d %s"
										   L"\n%s: %d %s"
										   L"\n%s: %d %s"
										   L"\n\n%s: %d"
										   L"\n%s: %d"
										   L"\n%s: %d"
										   L"\n\n%s: %s %s"
										   L"\n%s: %s %s"
										   L"\n%s: %s"
										   L"\n\n%s: %s"
										   //L"\n%s: %s"
										   //L"\n%s: %s"
										   L"\n%s: %s"
										   L"\n%s: %s"
										   L"\n%s: %s"

										   , ResourceString(L"IDS_INFORMATION_VIDEO_BITRATE").c_str(), getVideoBitrate(), ResourceString(L"IDS_INFORMATION_KBPS").c_str()
										   , ResourceString(L"IDS_INFORMATION_AUDIO_BITRATE").c_str(), getAudioBitrate(), ResourceString(L"IDS_INFORMATION_KBPS").c_str()
										   , ResourceString(L"IDS_INFORMATION_DURATION").c_str(), getDuration(), ResourceString(L"IDS_INFORMATION_SECONDS").c_str()
										   , ResourceString(L"IDS_INFORMATION_VIDEO_ENABLED").c_str(), isVideoEnabled()
										   , ResourceString(L"IDS_INFORMATION_AUDIO_ENABLED").c_str(), isAudioEnabled()
										   , ResourceString(L"IDS_INFORMATION_OVERHEAD_ENABLED").c_str(), isOverheadEnabled()
										   , ResourceString(L"IDS_INFORMATION_FILE_SIZE").c_str(), FloatToStr2(Information(getFileSize()).getBytes()).c_str(), ResourceString(L"IDS_INFORMATION_BYTES").c_str()
										   , ResourceString(L"IDS_INFORMATION_DATA_RATE").c_str(), FloatToStr2(Information(getDataRate()).getBytes()).c_str(), ResourceString(L"IDS_INFORMATION_BYTES_SEC").c_str()
										   , ResourceString(L"IDS_INFORMATION_OVERHEAD").c_str(), FloatToStr2(getOverhead()).c_str()
										   , ResourceString(L"IDS_INFORMATION_CONTAINER").c_str(), getContainer().getName().c_str()
										   //, ResourceString(L"IDS_INFORMATION_VIDEO_FORMAT").c_str(), getContainer().getVideoInterface().getName().c_str()
										   //, ResourceString(L"IDS_INFORMATION_AUDIO_FORMAT").c_str(), getContainer().getAudioInterface().getName().c_str()
										   , ResourceString(L"IDS_INFORMATION_CONTAINER_PTR").c_str(), pInterface ? L"Not null" : L"Null"
										   , ResourceString(L"IDS_INFORMATION_CONTAINER_OVERHEAD_FULL").c_str(), FloatToStr2(getContainer().getOverheadFull(getVideoBitrate(), getAudioBitrate(), getDuration())).c_str()
										   , ResourceString(L"IDS_INFORMATION_CONTAINER_OVERHEAD_NA").c_str(), FloatToStr2(getContainer().getOverheadNoAudio(getVideoBitrate(), getDuration())).c_str());

	return (w);
}