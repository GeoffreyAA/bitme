#ifndef __BITRATE_MODEL_H__
#define __BITRATE_MODEL_H__

#include "ContainerInterface.h"
#include "..\Library\String.h"

class BitrateModel
{
public:
	BitrateModel(int v = 0, int a = 0, int s = 0);
	~BitrateModel();

	int getVideoBitrate() const;
	int getAudioBitrate() const;
	int getDuration() const;

	double getFileSize() const;
	double getDataRate() const;
	double getOverhead() const;

	void setVideoBitrate(int kbps);
	void setAudioBitrate(int kbps);
	void setDuration(int seconds);

	void enableVideo(bool b);
	void enableAudio(bool b);
	void enableOverhead(bool b);

	bool isVideoEnabled() const;
	bool isAudioEnabled() const;
	bool isOverheadEnabled() const;

	int getVideoBitrateFromFileSize(double MB) const;
	int getVideoBitrateFromDataRate(double kBps) const;

	const ContainerInterface& getContainer() const;
	void setContainer(ContainerInterface *p);

	String getInformation() const;

private:
	int Video;
	int Audio;
	int Seconds;
	bool bVideo;
	bool bAudio;
	bool bOverhead;
	ContainerInterface *pInterface;
	const ContainerInterface DefInterface;
};

#endif