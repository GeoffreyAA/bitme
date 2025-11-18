#ifndef __C_BITME_DLG_H__
#define __C_BITME_DLG_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "Calculation\BitrateModel.h"
#include "Library\Font.h"
#include "Library\Configuration.h"
#include "Library\String.h"

class CBitMeDlg : public CDialog
{
public:
	CBitMeDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CBitMeDlg)
	enum { IDD = IDD_BITME_DIALOG };
	CButton	GroupOptions;
	CButton	GroupVideo;
	CButton	GroupAudio;
	CButton	GroupTime;
	CButton	GroupFileSize;
	CButton	GroupCustomSize;
	CButton	CheckVideo;
	CButton	CheckAudio;
	CButton	CheckDataRate;
	CButton	CheckCustomSize;
	CSliderCtrl	Video;
	CSliderCtrl	Audio;
	CSliderCtrl	Time;
	CEdit	THrs;
	CEdit	TMin;
	CEdit	TSec;
	CEdit	CustomSize;
	CStatic	LabelV1;
	CStatic	LabelV2;
	CStatic	LabelV1Title;
	CStatic	LabelV2Title;
	CStatic	LabelVMin;
	CStatic	LabelVMax;
	CStatic	LabelA1;
	CStatic	LabelA2;
	CStatic	LabelA1Title;
	CStatic	LabelA2Title;
	CStatic	LabelAMin;
	CStatic	LabelAMax;
	CStatic	LabelHours;
	CStatic	LabelMinutes;
	CStatic	LabelSeconds;
	CStatic	LabelT1Title;
	CStatic	LabelT2Title;
	CStatic	LabelT3Title;
	CStatic	LabelTMin;
	CStatic	LabelTMax;
	CStatic	LabelFS1;
	CStatic	LabelFS2;
	CStatic	LabelFS3;
	CStatic	LabelFS1Title;
	CStatic	LabelFS2Title;
	CStatic	LabelFS3Title;
	CStatic	LabelCustomSizeMsg;
	CStatic	LabelCustomSize;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBitMeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	void Initialise();
	void RetrieveConfiguration();
	void SaveConfiguration();
	void OnBeforeClose();

	void SetupControls();

	void UpdateWindowTitle();
	void UpdateMenu();
	void UpdateControls();
	void UpdateStrings();
	void UpdateWindowSize();
	void UpdateWindowPos();

	void OnChangeVideo();
	void OnChangeAudio();
	void OnChangeTime();
	void OnChangeCustomSize();
	void OnReturnKey();

	String GetSelectedContainer() const;
	//String GetSelectedVideoFormat() const;
	//String GetSelectedAudioFormat() const;
	void SelectContainer(const wchar_t *s);
	//void SelectVideoFormat(const wchar_t *s);
	//void SelectAudioFormat(const wchar_t *s);
	void EnableContainersAndFormats(bool b);

	//{{AFX_MSG(CBitMeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnCheckVideo();
	afx_msg void OnCheckAudio();
	afx_msg void OnCheckDataRate();
	afx_msg void OnCheckCustomSize();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnChangeClock();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnToolsResCalc();
	afx_msg void OnToolsSettings();
	//afx_msg void OnToolsReport();
	//afx_msg void OnToolsCalculator();
	afx_msg void OnToolsQuit();
	afx_msg void OnCalculationOverhead();
	afx_msg void OnCalculationInformation();
	//afx_msg void OnHelpHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	//afx_msg void OnHelpHomePage();
	//afx_msg void OnHelpLicence();
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BitrateModel Model;
	HICON hIcon;
	Font Font1;
	Font Font2;
	Font Font3;
};

struct CBitMeDlgCfg
{
	CBitMeDlgCfg();

	bool bVideo;
	bool bAudio;
	bool bDataRate;
	bool bCustomSize;
	bool bOverhead;

	String sContainer;
	//String sVideoFormat;
	//String sAudioFormat;

	int nVideo;
	int nAudio;
	int nTime;

	int x;
	int y;
};

class CBitMeDlgCfgSerializer
{
public:
	bool Save(const CBitMeDlgCfg &Cfg, Configuration &c) const;
	bool Retrieve(CBitMeDlgCfg &Cfg, const Configuration &c) const;
};

//{{AFX_INSERT_LOCATION}}

#endif