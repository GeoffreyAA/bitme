#include "stdafx.h"

#include "BitMe.h"
#include "BitMeDlg.h"

#include "AboutDlg.h"
#include "ResCalcDlg.h"
#include "SettingsDlg.h"

#include "Application.h"
#include "Library\Library.h"
#include "Library\Win32Library.h"
#include "Library\ResourceString.h"
#include "Library\Registry.h"
#include "Library\File.h"
#include "Library\Templates.h"
//#include "Library\SettingsManager.h"
#include "Library\ConfigFile.h"
#include "Interfaces\Information.h"
#include "Calculation\ContainerManager.h"
#include "Calculation\Report.h"

#include "Glue.h"
#include "TmpLibrary.h"

const wchar_t szFormat[] = L"%.2f";

const UINT Containers[] = {ID_CALCULATION_CONTAINER0,
						   ID_CALCULATION_CONTAINER1,
						   ID_CALCULATION_CONTAINER2,
						   ID_CALCULATION_CONTAINER3,
						   ID_CALCULATION_CONTAINER4,
						   ID_CALCULATION_CONTAINER5,
						   ID_CALCULATION_CONTAINER6,
						   ID_CALCULATION_CONTAINER7,
						   ID_CALCULATION_CONTAINER8,
						   ID_CALCULATION_CONTAINER9,
						   ID_CALCULATION_CONTAINER10,
						   ID_CALCULATION_CONTAINER11,
						   ID_CALCULATION_CONTAINER12,
						   ID_CALCULATION_CONTAINER13,
						   ID_CALCULATION_CONTAINER14,};

/*
const UINT VideoFormats[] = {ID_CALCULATION_VIDEO0,
							 ID_CALCULATION_VIDEO1,
							 ID_CALCULATION_VIDEO2,
							 ID_CALCULATION_VIDEO3,
							 ID_CALCULATION_VIDEO4};

const UINT AudioFormats[] = {ID_CALCULATION_AUDIO0,
							 ID_CALCULATION_AUDIO1,
							 ID_CALCULATION_AUDIO2,
							 ID_CALCULATION_AUDIO3,
							 ID_CALCULATION_AUDIO4};*/


///////////////////////////////////////////////////////////////

CBitMeDlg::CBitMeDlg(CWnd *pParent) : CDialog(CBitMeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitMeDlg)
	//}}AFX_DATA_INIT

	hIcon = AfxGetApp()->LoadIcon(IDR_BITME_ICON);
}

void CBitMeDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitMeDlg)
	DDX_Control(pDX, IDC_GROUPBOX1, GroupOptions);
	DDX_Control(pDX, IDC_GROUPBOX2, GroupVideo);
	DDX_Control(pDX, IDC_GROUPBOX3, GroupAudio);
	DDX_Control(pDX, IDC_GROUPBOX4, GroupTime);
	DDX_Control(pDX, IDC_GROUPBOX5, GroupFileSize);
	DDX_Control(pDX, IDC_GROUPBOX6, GroupCustomSize);
	DDX_Control(pDX, IDC_CHECK1, CheckVideo);
	DDX_Control(pDX, IDC_CHECK2, CheckAudio);
	DDX_Control(pDX, IDC_CHECK3, CheckDataRate);
	DDX_Control(pDX, IDC_CHECK4, CheckCustomSize);
	DDX_Control(pDX, IDC_SLIDER1, Video);
	DDX_Control(pDX, IDC_SLIDER2, Audio);
	DDX_Control(pDX, IDC_SLIDER3, Time);
	DDX_Control(pDX, IDC_EDIT1, THrs);
	DDX_Control(pDX, IDC_EDIT2, TMin);
	DDX_Control(pDX, IDC_EDIT3, TSec);
	DDX_Control(pDX, IDC_EDIT4, CustomSize);
	DDX_Control(pDX, IDC_LABEL1, LabelV1);
	DDX_Control(pDX, IDC_LABEL2, LabelV2);
	DDX_Control(pDX, IDC_LABEL12, LabelV1Title);
	DDX_Control(pDX, IDC_LABEL13, LabelV2Title);
	DDX_Control(pDX, IDC_LABEL14, LabelVMin);
	DDX_Control(pDX, IDC_LABEL15, LabelVMax);
	DDX_Control(pDX, IDC_LABEL3, LabelA1);
	DDX_Control(pDX, IDC_LABEL4, LabelA2);
	DDX_Control(pDX, IDC_LABEL16, LabelA1Title);
	DDX_Control(pDX, IDC_LABEL17, LabelA2Title);
	DDX_Control(pDX, IDC_LABEL18, LabelAMin);
	DDX_Control(pDX, IDC_LABEL19, LabelAMax);
	DDX_Control(pDX, IDC_LABEL5, LabelHours);
	DDX_Control(pDX, IDC_LABEL6, LabelMinutes);
	DDX_Control(pDX, IDC_LABEL7, LabelSeconds);
	DDX_Control(pDX, IDC_LABEL20, LabelT1Title);
	DDX_Control(pDX, IDC_LABEL21, LabelT2Title);
	DDX_Control(pDX, IDC_LABEL22, LabelT3Title);
	DDX_Control(pDX, IDC_LABEL23, LabelTMin);
	DDX_Control(pDX, IDC_LABEL24, LabelTMax);
	DDX_Control(pDX, IDC_LABEL8, LabelFS1);
	DDX_Control(pDX, IDC_LABEL9, LabelFS2);
	DDX_Control(pDX, IDC_LABEL10, LabelFS3);
	DDX_Control(pDX, IDC_LABEL25, LabelFS1Title);
	DDX_Control(pDX, IDC_LABEL26, LabelFS2Title);
	DDX_Control(pDX, IDC_LABEL27, LabelFS3Title);
	DDX_Control(pDX, IDC_LABEL28, LabelCustomSizeMsg);
	DDX_Control(pDX, IDC_LABEL11, LabelCustomSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBitMeDlg, CDialog)
	//{{AFX_MSG_MAP(CBitMeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK1, OnCheckVideo)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckAudio)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckDataRate)
	ON_BN_CLICKED(IDC_CHECK4, OnCheckCustomSize)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT1, OnChangeClock)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnChangeClock)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnChangeClock)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_TOOLS_RESCALC, OnToolsResCalc)
	ON_COMMAND(ID_TOOLS_SETTINGS, OnToolsSettings)
	//ON_COMMAND(ID_TOOLS_REPORT, OnToolsReport)
	//ON_COMMAND(ID_TOOLS_CALCULATOR, OnToolsCalculator)
	ON_COMMAND(ID_TOOLS_QUIT, OnToolsQuit)
	ON_COMMAND(ID_CALCULATION_OVERHEAD, OnCalculationOverhead)
	ON_COMMAND(ID_CALCULATION_INFORMATION, OnCalculationInformation)
	//ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_WM_HELPINFO()
	//ON_COMMAND(ID_HELP_HOMEPAGE, OnHelpHomePage)
	//ON_COMMAND(ID_HELP_LICENCE, OnHelpLicence)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBitMeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	Initialise();

	return FALSE;
}

void CBitMeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CBitMeDlg::OnQueryDragIcon()
{
	return (HCURSOR)hIcon;
}

void CBitMeDlg::OnOK()
{
}

void CBitMeDlg::OnClose()
{
	OnBeforeClose();

	CDialog::OnClose();
}

BOOL CBitMeDlg::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg && (pMsg->message == WM_KEYDOWN))
	{
		switch (pMsg->wParam)
		{
			case VK_RETURN:
				OnReturnKey();
				break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


///////////////////////////////////////////////////////////////

void CBitMeDlg::Initialise()
{
	UpdateWindowTitle();
	UpdateMenu();

	SetupControls();
	RetrieveConfiguration();
	OnCheckVideo();
	OnCheckAudio();
	OnCheckDataRate();
	OnCheckCustomSize();
	OnChangeVideo();
	OnChangeAudio();
	OnChangeTime();

	UpdateControls();
	UpdateStrings();
	UpdateWindowPos();

	Video.SetFocus();
}

void CBitMeDlg::RetrieveConfiguration()
{
	CBitMeDlgCfg Cfg;

	//if (!CBitMeDlgCfgSerializer().Retrieve(Cfg, Registry(GetRegistryKey(), KEY_READ, false)))
	if (!CBitMeDlgCfgSerializer().Retrieve(Cfg, ConfigFile()))
	{
		Cfg = CBitMeDlgCfg();
	}

	CheckVideo.SetCheck(Cfg.bVideo);
	CheckAudio.SetCheck(Cfg.bAudio);
	CheckDataRate.SetCheck(Cfg.bDataRate);
	CheckCustomSize.SetCheck(Cfg.bCustomSize);
	Video.SetPos(Cfg.nVideo);
	Audio.SetPos(Cfg.nAudio);
	Time.SetPos(Cfg.nTime);

	Model.enableOverhead(Cfg.bOverhead);
	Model.setContainer(ContainerManager::CreateContainer(Cfg.sContainer.c_str()));
	//Model.setContainer(ContainerManager::CreateInterface(Cfg.sContainer.c_str(), Cfg.sVideoFormat.c_str(), Cfg.sAudioFormat.c_str()));

	::SetWindowPos(GetSafeHwnd(), NULL, Cfg.x, Cfg.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	/*
	Settings_t s;

	if (!SettingsManager::GetInstance().GetSettings(&s))
	{
		s = Settings_t();
	}

	Model.enableOverhead(s.bUseOverhead);
	Model.setContainer(ContainerManager::GetContainerInterface(s.sContainerName.c_str()));
	*/
}

void CBitMeDlg::SaveConfiguration()
{
	CBitMeDlgCfg Cfg;
	HMENU h = ::GetMenu(GetSafeHwnd());

	Cfg.bVideo = ToBool(CheckVideo.GetCheck());
	Cfg.bAudio = ToBool(CheckAudio.GetCheck());
	Cfg.bDataRate = ToBool(CheckDataRate.GetCheck());
	Cfg.bCustomSize = ToBool(CheckCustomSize.GetCheck());
	Cfg.bOverhead = h ? GetMenuItemChecked(h, ID_CALCULATION_OVERHEAD) : false;
	Cfg.sContainer = GetSelectedContainer();
	//Cfg.sVideoFormat = GetSelectedVideoFormat();
	//Cfg.sAudioFormat = GetSelectedAudioFormat();
	Cfg.nVideo = Video.GetPos();
	Cfg.nAudio = Audio.GetPos();
	Cfg.nTime = Time.GetPos();
	Cfg.x = GetWindowLeft(GetSafeHwnd());
	Cfg.y = GetWindowTop(GetSafeHwnd());

	//CBitMeDlgCfgSerializer().Save(Cfg, Registry(GetRegistryKey(), KEY_WRITE, true));
	CBitMeDlgCfgSerializer().Save(Cfg, ConfigFile());
}

void CBitMeDlg::OnBeforeClose()
{
	SaveConfiguration();
}

void CBitMeDlg::SetupControls()
{
	Video.SetRange(0, 900000, FALSE); // 900000 = 900 Mbps
	Audio.SetRange(0, 20000, FALSE); // 20000 = 20 Mbps
	Time.SetRange(0, 32400, FALSE); // 32400 = 9 hours

	Video.SetPageSize(500);
	Audio.SetPageSize(128);
	Time.SetPageSize(60);
	Time.SetTicFreq(3600);

	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		SetMenuStrings(h, Containers, sizeof(Containers) / sizeof(Containers[0]), ContainerManager::GetAvailableContainers());
		//SetMenuStrings(h, VideoFormats, sizeof(VideoFormats) / sizeof(VideoFormats[0]), ContainerManager::GetAvailableVideoFormats());
		//SetMenuStrings(h, AudioFormats, sizeof(AudioFormats) / sizeof(AudioFormats[0]), ContainerManager::GetAvailableAudioFormats());

		/*
		StringList s = ContainerManager::GetAvailableInterfaces();

		for (int i = 0; i < (sizeof(Containers) / sizeof(Containers[0])); i++)
		{
			if (i < s.size())
			{
				SetMenuString(p->GetSafeHmenu(), Containers[i], s[i].c_str());
			}
			else
			{
				RemoveMenu(p->GetSafeHmenu(), Containers[i], MF_BYCOMMAND);
			}
		}
		*/
	}

#if 1

	Font1.Create(L"MS Sans Serif", 10, true);
	Font2.Create(L"Arial", 10);
	Font3.Create(L"MS Sans Serif", 12, true);

	//Font1.Create(L"Arial", 9);
	//Font4.Create(L"Arial", 8.5);

	//SetWindowFont(GroupOptions.GetSafeHwnd(), Font1.GetFont());
	//SetWindowFont(GroupVideo.GetSafeHwnd(), Font1.GetFont());
	//SetWindowFont(GroupAudio.GetSafeHwnd(), Font1.GetFont());
	//SetWindowFont(GroupTime.GetSafeHwnd(), Font1.GetFont());
	//SetWindowFont(GroupFileSize.GetSafeHwnd(), Font1.GetFont());
	//SetWindowFont(GroupCustomSize.GetSafeHwnd(), Font1.GetFont());

	//SetWindowFont(CheckVideo.GetSafeHwnd(), Font4.GetFont());
	//SetWindowFont(CheckAudio.GetSafeHwnd(), Font4.GetFont());
	//SetWindowFont(CheckDataRate.GetSafeHwnd(), Font4.GetFont());
	//SetWindowFont(CheckCustomSize.GetSafeHwnd(), Font4.GetFont());
	//SetWindowFont(CheckOverhead.GetSafeHwnd(), Font4.GetFont());

	SetWindowFont(LabelV1.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelV2.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelA1.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelA2.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelHours.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelMinutes.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(LabelSeconds.GetSafeHwnd(), Font1.GetFont());

	SetWindowFont(LabelV1Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelV2Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelA1Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelA2Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelT1Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelT2Title.GetSafeHwnd(), Font2.GetFont());
	SetWindowFont(LabelT3Title.GetSafeHwnd(), Font2.GetFont());

	SetWindowFont(LabelFS1.GetSafeHwnd(), Font3.GetFont());
	SetWindowFont(LabelFS2.GetSafeHwnd(), Font3.GetFont());
	SetWindowFont(LabelFS3.GetSafeHwnd(), Font3.GetFont());
	SetWindowFont(LabelFS1Title.GetSafeHwnd(), Font3.GetFont());
	SetWindowFont(LabelFS2Title.GetSafeHwnd(), Font3.GetFont());
	SetWindowFont(LabelFS3Title.GetSafeHwnd(), Font3.GetFont());

#endif
}

void CBitMeDlg::UpdateWindowTitle()
{
#ifndef _DEBUG
	SetWindowText(GetApplicationName());
#else
	SetWindowText(GetApplicationNameFull().c_str());
#endif
}

void CBitMeDlg::UpdateMenu()
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		ModifyMenu(h, 0, MF_BYPOSITION | MF_STRING, 0, ResourceString(L"IDS_MENU_TOOLS"));
		ModifyMenu(h, 1, MF_BYPOSITION | MF_STRING, 0, ResourceString(L"IDS_MENU_CALCULATION"));
		//ModifyMenu(h, 2, MF_BYPOSITION | MF_STRING, 0, ResourceString(L"IDS_MENU_HELP"));

		SetMenuString(h, ID_TOOLS_RESCALC, ResourceString(L"IDS_TOOLS_RESCALC"));
		SetMenuString(h, ID_TOOLS_SETTINGS, ResourceString(L"IDS_TOOLS_SETTINGS"));
		//SetMenuString(h, ID_TOOLS_REPORT, ResourceString(L"IDS_TOOLS_REPORT"));
		//SetMenuString(h, ID_TOOLS_CALCULATOR, ResourceString(L"IDS_TOOLS_CALCULATOR"));
		SetMenuString(h, ID_TOOLS_QUIT, ResourceString(L"IDS_TOOLS_QUIT"));

		SetMenuString(h, ID_CALCULATION_OVERHEAD, ResourceString(L"IDS_CALCULATION_OVERHEAD"));
		SetMenuString(h, ID_CALCULATION_INFORMATION, ResourceString(L"IDS_CALCULATION_INFORMATION"));

		//SetMenuString(h, ID_HELP_HELP, ResourceString(L"IDS_HELP_HELP"));
		//SetMenuString(h, ID_HELP_HOMEPAGE, ResourceString(L"IDS_HELP_HOMEPAGE"));
		//SetMenuString(h, ID_HELP_LICENCE, ResourceString(L"IDS_HELP_LICENCE"));
		SetMenuString(h, ID_HELP_ABOUT, ResourceString(L"IDS_HELP_ABOUT"));

		::DrawMenuBar(GetSafeHwnd());
	}
}

void CBitMeDlg::UpdateControls()
{
	// Video
	SetWindowInt(LabelV1.GetSafeHwnd(), Model.getVideoBitrate());
	SetWindowFloat(LabelV2.GetSafeHwnd(), Information(Model.getVideoBitrate() * 1000.0).getKB(), szFormat);
	GroupVideo.EnableWindow(Model.isVideoEnabled());
	Video.EnableWindow(Model.isVideoEnabled());
	LabelV1.EnableWindow(Model.isVideoEnabled());
	LabelV2.EnableWindow(Model.isVideoEnabled());
	LabelV1Title.EnableWindow(Model.isVideoEnabled());
	LabelV2Title.EnableWindow(Model.isVideoEnabled());
	LabelVMin.EnableWindow(Model.isVideoEnabled());
	LabelVMax.EnableWindow(Model.isVideoEnabled());

	// Audio
	SetWindowInt(LabelA1.GetSafeHwnd(), Model.getAudioBitrate());
	SetWindowFloat(LabelA2.GetSafeHwnd(), Information(Model.getAudioBitrate() * 1000.0).getKB(), szFormat);
	GroupAudio.EnableWindow(Model.isAudioEnabled());
	Audio.EnableWindow(Model.isAudioEnabled());
	LabelA1.EnableWindow(Model.isAudioEnabled());
	LabelA2.EnableWindow(Model.isAudioEnabled());
	LabelA1Title.EnableWindow(Model.isAudioEnabled());
	LabelA2Title.EnableWindow(Model.isAudioEnabled());
	LabelAMin.EnableWindow(Model.isAudioEnabled());
	LabelAMax.EnableWindow(Model.isAudioEnabled());

	// Time
	int s = Model.getDuration();

	SetWindowInt(LabelHours.GetSafeHwnd(), s / 60 / 60);
	SetWindowInt(LabelMinutes.GetSafeHwnd(), s / 60);
	SetWindowInt(LabelSeconds.GetSafeHwnd(), s);

	SetWindowInt(THrs.GetSafeHwnd(), s / 60 / 60);
	SetWindowInt2(TMin.GetSafeHwnd(), s / 60 % 60);
	SetWindowInt2(TSec.GetSafeHwnd(), s % 60);

	// File Size; Data Rate
	if (CheckDataRate.GetCheck())
	{
		double bps = Model.getDataRate();

		SetWindowFloat2(LabelFS1.GetSafeHwnd(), Information(bps).getKB(), szFormat);
		SetWindowFloat2(LabelFS2.GetSafeHwnd(), BitsToKilobits(bps), szFormat);
		SetWindowFloat2(LabelFS3.GetSafeHwnd(), BitsToMegabits(bps), szFormat);
	}
	else
	{
		Information i(Model.getFileSize());

		SetWindowFloat2(LabelFS1.GetSafeHwnd(), i.getKB(), szFormat);
		SetWindowFloat2(LabelFS2.GetSafeHwnd(), i.getMB(), szFormat);
		SetWindowFloat2(LabelFS3.GetSafeHwnd(), i.getGB(), szFormat);
	}

	// Custom Size
	CheckCustomSize.EnableWindow(Model.isVideoEnabled());

	if (Model.isVideoEnabled() && CheckCustomSize.GetCheck())
	{
		GroupCustomSize.ShowWindow(SW_SHOW);
		CustomSize.EnableWindow(TRUE);
	}
	else
	{
		GroupCustomSize.ShowWindow(SW_HIDE);
		CustomSize.EnableWindow(FALSE);
	}

	// Calculation Menu
	SetMenuItemCheck(::GetMenu(GetSafeHwnd()), ID_CALCULATION_OVERHEAD, Model.isOverheadEnabled());
	SelectContainer(Model.getContainer().getName().c_str());
	//SelectVideoFormat(Model.getContainer().getVideoInterface().getName().c_str());
	//SelectAudioFormat(Model.getContainer().getAudioInterface().getName().c_str());
	EnableContainersAndFormats(Model.isOverheadEnabled());
}

void CBitMeDlg::UpdateStrings()
{
	GroupOptions.SetWindowText(ResourceString(L"IDS_OPTIONS"));
	CheckVideo.SetWindowText(ResourceString(L"IDS_VIDEO"));
	CheckAudio.SetWindowText(ResourceString(L"IDS_AUDIO"));
	CheckDataRate.SetWindowText(ResourceString(L"IDS_RATE"));

	GroupVideo.SetWindowText(ResourceString(L"IDS_VIDEO_BITRATE"));
	LabelV1Title.SetWindowText(ResourceString(L"IDS_KILOBITS_PER_SECOND"));
	LabelV2Title.SetWindowText(ResourceString(L"IDS_KILOBYTES_PER_SECOND"));
	SetWindowTextRange(LabelVMin.GetSafeHwnd(), Video.GetRangeMin(), ResourceString(L"IDS_KILOBITS_PER_SECOND"));
	SetWindowTextRange(LabelVMax.GetSafeHwnd(), Video.GetRangeMax() / 1000, ResourceString(L"IDS_MEGABITS_PER_SECOND"));

	GroupAudio.SetWindowText(ResourceString(L"IDS_AUDIO_BITRATE"));
	LabelA1Title.SetWindowText(ResourceString(L"IDS_KILOBITS_PER_SECOND"));
	LabelA2Title.SetWindowText(ResourceString(L"IDS_KILOBYTES_PER_SECOND"));
	SetWindowTextRange(LabelAMin.GetSafeHwnd(), Audio.GetRangeMin(), ResourceString(L"IDS_KILOBITS_PER_SECOND"));
	SetWindowTextRange(LabelAMax.GetSafeHwnd(), Audio.GetRangeMax() / 1000, ResourceString(L"IDS_MEGABITS_PER_SECOND"));

	GroupTime.SetWindowText(ResourceString(L"IDS_DURATION"));
	LabelT1Title.SetWindowText(ResourceString(L"IDS_HOURS"));
	LabelT2Title.SetWindowText(ResourceString(L"IDS_MINUTES"));
	LabelT3Title.SetWindowText(ResourceString(L"IDS_SECONDS"));
	SetWindowTextRange(LabelTMin.GetSafeHwnd(), Time.GetRangeMin(), ResourceString(L"IDS_SECONDS"));
	SetWindowTextRange(LabelTMax.GetSafeHwnd(), Time.GetRangeMax(), ResourceString(L"IDS_SECONDS"));

	if (CheckDataRate.GetCheck())
	{
		GroupFileSize.SetWindowText(ResourceString(L"IDS_DATA_RATE"));
		LabelFS1Title.SetWindowText(ResourceString(L"IDS_KILOBYTES_PER_SECOND"));
		LabelFS2Title.SetWindowText(ResourceString(L"IDS_KILOBITS_PER_SECOND"));
		LabelFS3Title.SetWindowText(ResourceString(L"IDS_MEGABITS_PER_SECOND"));

		GroupCustomSize.SetWindowText(ResourceString(L"IDS_CUSTOM_DATA_RATE"));
		LabelCustomSizeMsg.SetWindowText(ResourceString(L"IDS_TYPE_DATA_RATE"));
		LabelCustomSize.SetWindowText(ResourceString(L"IDS_KILOBYTES_PER_SECOND"));
	}
	else
	{
		GroupFileSize.SetWindowText(ResourceString(L"IDS_FILE_SIZE"));
		LabelFS1Title.SetWindowText(ResourceString(L"IDS_KB"));
		LabelFS2Title.SetWindowText(ResourceString(L"IDS_MB"));
		LabelFS3Title.SetWindowText(ResourceString(L"IDS_GB"));

		GroupCustomSize.SetWindowText(ResourceString(L"IDS_CUSTOM_FILE_SIZE"));
		LabelCustomSizeMsg.SetWindowText(ResourceString(L"IDS_TYPE_FILE_SIZE"));
		LabelCustomSize.SetWindowText(ResourceString(L"IDS_MB"));
	}

	CheckCustomSize.SetWindowText(ResourceString(L"IDS_CUSTOM"));
}

void CBitMeDlg::UpdateWindowSize()
{
	HWND hDlg = GetSafeHwnd();

	HWND hGroup = (Model.isVideoEnabled() && CheckCustomSize.GetCheck()) ? GroupCustomSize.GetSafeHwnd()
																		 : GroupFileSize.GetSafeHwnd();

	int Space = GetWindowRight(hDlg) - GetWindowRight(hGroup);

	int h = GetWindowTop(hGroup) + GetWindowHeight(hGroup) + Space -
			GetWindowTop(hDlg);

	SetWindowSize(hDlg, GetWindowWidth(hDlg), h);
}

void CBitMeDlg::UpdateWindowPos()
{
	const HWND hDlg = GetSafeHwnd();

	const int x = GetWindowLeft(hDlg);
	const int y = GetWindowTop(hDlg);

	const int nBorderWidth = GetSystemMetrics(SM_CXEDGE);
	const int nBorderHeight = GetSystemMetrics(SM_CYEDGE);

	const int xMin = 0 + nBorderWidth;
	const int yMin = 0 + nBorderHeight;

	const int xMax = GetDesktopWidth() - GetWindowWidth(hDlg) - nBorderWidth;
	const int yMax = GetDesktopHeight() - GetWindowHeight(hDlg) - nBorderHeight;

	if (!InRange(xMin, xMax, x) || !InRange(yMin, yMax, y))
	{
		SetWindowPosition(hDlg, Clamp(xMin, xMax, x), Clamp(yMin, yMax, y));
	}
}

void CBitMeDlg::OnCheckVideo()
{
	Model.enableVideo(ToBool(CheckVideo.GetCheck()));

	UpdateControls();

	OnCheckCustomSize();
}

void CBitMeDlg::OnCheckAudio()
{
	Model.enableAudio(ToBool(CheckAudio.GetCheck()));

	UpdateControls();
}

void CBitMeDlg::OnCheckDataRate()
{
	UpdateControls();
	UpdateStrings();
}

void CBitMeDlg::OnCheckCustomSize()
{
	UpdateControls();
	UpdateWindowSize();
}

void CBitMeDlg::OnChangeVideo()
{
	Model.setVideoBitrate(Video.GetPos());

	UpdateControls();
}

void CBitMeDlg::OnChangeAudio()
{
	Model.setAudioBitrate(Audio.GetPos());

	UpdateControls();
}

void CBitMeDlg::OnChangeTime()
{
	Model.setDuration(Time.GetPos());

	UpdateControls();
}

void CBitMeDlg::OnChangeClock()
{
	int s = 0;

	s += (GetWindowInt(THrs.GetSafeHwnd()) * 60 * 60);
	s += (GetWindowInt(TMin.GetSafeHwnd()) * 60);
	s +=  GetWindowInt(TSec.GetSafeHwnd());

	Time.SetPos(Clamp(Time.GetRangeMin(), Time.GetRangeMax(), s));
	OnChangeTime();
}

void CBitMeDlg::OnChangeCustomSize()
{
	bool bDataRate = ToBool(CheckDataRate.GetCheck());

	double x = GetWindowFloat(CustomSize.GetSafeHwnd());

	int v = bDataRate ? Model.getVideoBitrateFromDataRate(x)
					  : Model.getVideoBitrateFromFileSize(x);

	Video.SetPos(Clamp(Video.GetRangeMin(), Video.GetRangeMax(), v));
	OnChangeVideo();

	SetWindowFloat(CustomSize.GetSafeHwnd(), bDataRate ? Information(Model.getDataRate()).getKB()
													   : Information(Model.getFileSize()).getMB());
}

void CBitMeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	if (pScrollBar)
	{
		switch (pScrollBar->GetDlgCtrlID())
		{
			case IDC_SLIDER1:
				OnChangeVideo();
				break;

			case IDC_SLIDER2:
				OnChangeAudio();
				break;

			case IDC_SLIDER3:
				OnChangeTime();
				break;
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CBitMeDlg::OnReturnKey()
{
	CWnd *p = GetFocus();

	if (p)
	{
		switch (p->GetDlgCtrlID())
		{
			case IDC_EDIT1:
			case IDC_EDIT2:
			case IDC_EDIT3:
				OnChangeClock();
				break;

			case IDC_EDIT4:
				OnChangeCustomSize();
				break;
		}
	}
}

HBRUSH CBitMeDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd && pDC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
			case IDC_LABEL1:
			case IDC_LABEL2:
			case IDC_LABEL3:
			case IDC_LABEL4:
				pDC->SetTextColor(0x00c00000);
				break;

			case IDC_LABEL5:
			case IDC_LABEL6:
			case IDC_LABEL7:
				pDC->SetTextColor(0x00008000);
				break;

			case IDC_LABEL8:
			case IDC_LABEL9:
			case IDC_LABEL10:
				pDC->SetTextColor(0x00000080);
				break;
		}
	}

	return (hbr);
}

String CBitMeDlg::GetSelectedContainer() const
{
	return (GetMenuItemSelected(::GetMenu(GetSafeHwnd()), Containers, sizeof(Containers) / sizeof(Containers[0])));
}

/*
String CBitMeDlg::GetSelectedVideoFormat() const
{
	return (GetMenuItemSelected(::GetMenu(GetSafeHwnd()), VideoFormats, sizeof(VideoFormats) / sizeof(VideoFormats[0])));
}

String CBitMeDlg::GetSelectedAudioFormat() const
{
	return (GetMenuItemSelected(::GetMenu(GetSafeHwnd()), AudioFormats, sizeof(AudioFormats) / sizeof(AudioFormats[0])));
}
*/

void CBitMeDlg::SelectContainer(const wchar_t *s)
{
	SelectMenuItem(::GetMenu(GetSafeHwnd()), Containers, sizeof(Containers) / sizeof(Containers[0]), s);
}

/*
void CBitMeDlg::SelectVideoFormat(const wchar_t *s)
{
	SelectMenuItem(::GetMenu(GetSafeHwnd()), VideoFormats, sizeof(VideoFormats) / sizeof(VideoFormats[0]), s);
}

void CBitMeDlg::SelectAudioFormat(const wchar_t *s)
{
	SelectMenuItem(::GetMenu(GetSafeHwnd()), AudioFormats, sizeof(AudioFormats) / sizeof(AudioFormats[0]), s);
}
*/

void CBitMeDlg::EnableContainersAndFormats(bool b)
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		EnableMenuItems(h, Containers, sizeof(Containers) / sizeof(Containers[0]), b);
		//EnableMenuItems(h, VideoFormats, sizeof(VideoFormats) / sizeof(VideoFormats[0]), b);
		//EnableMenuItems(h, AudioFormats, sizeof(AudioFormats) / sizeof(AudioFormats[0]), b);
	}
}

/*
String CBitMeDlg::GetSelectedContainer() const
{
	CMenu *p = GetMenu();

	if (p)
	{
		for (int i = 0; i < (sizeof(Containers) / sizeof(Containers[0])); i++)
		{
			if (GetMenuItemChecked(p->GetSafeHmenu(), Containers[i]))
			{
				wchar_t w[32];

				return (GetMenuString(p->GetSafeHmenu(), Containers[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) ? w : L"");
			}
		}
	}

	return (L"");
}

void CBitMeDlg::SelectContainer(const wchar_t *s)
{
	if (s)
	{
		CMenu *p = GetMenu();

		if (p)
		{
			wchar_t w[32];

			for (int i = 0; i < (sizeof(Containers) / sizeof(Containers[0])); i++)
			{
				if (GetMenuString(p->GetSafeHmenu(), Containers[i], w, sizeof(w) / sizeof(w[0]), MF_BYCOMMAND) && !wcscmp(s, w))
				{
					CheckMenuRadioItem(p->GetSafeHmenu(), Containers[0], Containers[sizeof(Containers) / sizeof(Containers[0]) - 1], Containers[i], MF_BYCOMMAND);

					return;
				}
			}

			for (int j = 0; j < (sizeof(Containers) / sizeof(Containers[0])); j++)
			{
				SetMenuItemCheck(p->GetSafeHmenu(), Containers[j], false);
			}
		}
	}
}

void CBitMeDlg::EnableContainers(bool b)
{
	CMenu *p = GetMenu();

	if (p)
	{
		for (int i = 0; i < (sizeof(Containers) / sizeof(Containers[0])); i++)
		{
			EnableMenuItem(p->GetSafeHmenu(), Containers[i], MF_BYCOMMAND | (b ? MF_ENABLED : MF_GRAYED));
		}
	}
}
*/


///////////////////////////////////////////////////////////////

void CBitMeDlg::OnToolsResCalc()
{
	CResCalcDlg().DoModal();
}

void CBitMeDlg::OnToolsSettings()
{
	if (CSettingsDlg().DoModal() == IDOK)
	{
		UpdateWindowTitle();
		UpdateMenu();
		UpdateStrings();

		/*
		Settings_t s;

		if (GetGlobalSettings(&s))
		{
			Model.enableOverhead(s.bUseOverhead);
			Model.setContainer(ContainerManager::GetContainerInterface(s.sContainerName.c_str()));

			UpdateControls();
		}
		*/
	}
}

/*void CBitMeDlg::OnToolsReport()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	wchar_t w[MAX_PATH] = L"BitMe.htm";
	ResourceString s(L"IDS_REPORT_DLG_TITLE");

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lpstrFilter = L"HTML\0*.htm;*.html\0";
	ofn.lpstrFile = w;
	ofn.nMaxFile = sizeof(w) / sizeof(w[0]);
	ofn.lpstrTitle = s.c_str();
	ofn.Flags = OFN_HIDEREADONLY | OFN_NOREADONLYRETURN | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
	ofn.lpstrDefExt = L"htm";

	if (GetSaveFileName(&ofn))
	{
		if (!SaveReport(w, Model))
		{
			MsgBox(ResourceString(L"IDS_REPORT_ERROR"), ResourceString(L"IDS_REPORT_ERROR_TITLE"), GetSafeHwnd(), MSG_ERROR);
		}
	}
}*/

/*void CBitMeDlg::OnToolsCalculator()
{
	wchar_t c[MAX_PATH];

	const UINT cbSize = sizeof(c) / sizeof(c[0]);

	UINT n = GetSystemDirectory(c, cbSize);

	if ((0 < n) && (n < cbSize) && AddFileName(c, L"calc.exe", cbSize))
	{
		if (!ShellOpen(c, GetSafeHwnd()))
		{
			MsgBox(ResourceString(L"IDS_CALCULATOR_ERROR"), ResourceString(L"IDS_CALCULATOR_ERROR_TITLE"), GetSafeHwnd(), MSG_ERROR);
		}
	}
}*/

void CBitMeDlg::OnToolsQuit()
{
	OnBeforeClose();

	EndDialog(IDOK);
}

void CBitMeDlg::OnCalculationOverhead()
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		bool b = GetMenuItemChecked(h, ID_CALCULATION_OVERHEAD);

		SetMenuItemCheck(h, ID_CALCULATION_OVERHEAD, !b);

		Model.enableOverhead(!b);

		UpdateControls();
	}
}

BOOL CBitMeDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		/*
		if (SelectMenuItemID(h, Containers, sizeof(Containers) / sizeof(Containers[0]), LOWORD(wParam)) ||
			SelectMenuItemID(h, VideoFormats, sizeof(VideoFormats) / sizeof(VideoFormats[0]), LOWORD(wParam)) ||
			SelectMenuItemID(h, AudioFormats, sizeof(AudioFormats) / sizeof(AudioFormats[0]), LOWORD(wParam)))
			*/

		if (SelectMenuItemID(h, Containers, sizeof(Containers) / sizeof(Containers[0]), LOWORD(wParam)))
		{
			Model.setContainer(ContainerManager::CreateContainer(GetSelectedContainer().c_str()));
			//Model.setContainer(ContainerManager::CreateInterface(GetSelectedContainer().c_str(), GetSelectedVideoFormat().c_str(), GetSelectedAudioFormat().c_str()));

			UpdateControls();
		}

		/*
		for (int i = 0; i < (sizeof(Containers) / sizeof(Containers[0])); i++)
		{
			if (LOWORD(wParam) == Containers[i])
			{
				CheckMenuRadioItem(p->GetSafeHmenu(), Containers[0], Containers[sizeof(Containers) / sizeof(Containers[0]) - 1], Containers[i], MF_BYCOMMAND);

				OnChangeContainer();

				UpdateControls();

				break;
			}
		}
		*/
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CBitMeDlg::OnCalculationInformation()
{
	MsgBox(Model.getInformation().c_str(), ResourceString(L"IDS_INFORMATION"), GetSafeHwnd());
}

/*void CBitMeDlg::OnHelpHelp()
{
	//HtmlHelp(ApplicationFile(GetHelpFileName()), NULL, GetSafeHwnd());
}*/

BOOL CBitMeDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	//OnHelpHelp();

	return TRUE;
}

/*void CBitMeDlg::OnHelpHomePage()
{
	ShellOpen(L"https://github.com/GeoffreyAA/bitme", NULL);
}*/

/*void CBitMeDlg::OnHelpLicence()
{
	if (::MessageBox(GetSafeHwnd(), ResourceString(L"IDS_LICENCE_MSG"), ResourceString(L"IDS_LICENCE_TITLE"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
	{
		if (!HtmlHelp(ApplicationFile(GetHelpFileName()), L"Licence.txt", GetSafeHwnd()))
		{
			MsgBox(ResourceString(L"IDS_LICENCE_ERROR"), ResourceString(L"IDS_LICENCE_TITLE"), GetSafeHwnd(), MSG_ERROR);
		}
	}
}*/

void CBitMeDlg::OnHelpAbout()
{
	CAboutDlg().DoModal();
}


///////////////////////////////////////////////////////////////

CBitMeDlgCfg::CBitMeDlgCfg() : bVideo(true), bAudio(true), bDataRate(false), bCustomSize(false), bOverhead(true), sContainer(L"MP4/MOV/3GP"), /*sVideoFormat(L"H.264/MPEG-4 AVC"), sAudioFormat(L"AAC"),*/ nVideo(2000), nAudio(192), nTime(7200), x(32), y(32)
{
}

bool CBitMeDlgCfgSerializer::Save(const CBitMeDlgCfg &Cfg, Configuration &c) const
{
	bool b;

	b = c.setBool(L"bVideo", Cfg.bVideo);
	b = c.setBool(L"bAudio", Cfg.bAudio);
	b = c.setBool(L"bDataRate", Cfg.bDataRate);
	b = c.setBool(L"bCustomSize", Cfg.bCustomSize);
	b = c.setBool(L"bOverhead", Cfg.bOverhead);
	b = c.setString(L"sContainer", Cfg.sContainer.c_str());
	//b = c.setString(L"sVideoFormat", Cfg.sVideoFormat.c_str());
	//b = c.setString(L"sAudioFormat", Cfg.sAudioFormat.c_str());
	b = c.setInteger(L"nVideo", Cfg.nVideo);
	b = c.setInteger(L"nAudio", Cfg.nAudio);
	b = c.setInteger(L"nTime", Cfg.nTime);
	b = c.setInteger(L"x", Cfg.x);
	b = c.setInteger(L"y", Cfg.y);

	return (b);
}

bool CBitMeDlgCfgSerializer::Retrieve(CBitMeDlgCfg &Cfg, const Configuration &c) const
{
	CBitMeDlgCfg d;
	wchar_t w[32];

	Cfg.bVideo = c.getBool(L"bVideo", d.bVideo);
	Cfg.bAudio = c.getBool(L"bAudio", d.bAudio);
	Cfg.bDataRate = c.getBool(L"bDataRate", d.bDataRate);
	Cfg.bCustomSize = c.getBool(L"bCustomSize", d.bCustomSize);
	Cfg.bOverhead = c.getBool(L"bOverhead", d.bOverhead);
	Cfg.sContainer = c.getString(L"sContainer", w, sizeof(w) / sizeof(w[0])) ? w : d.sContainer;
	//Cfg.sVideoFormat = c.getString(L"sVideoFormat", w, sizeof(w) / sizeof(w[0])) ? w : d.sVideoFormat;
	//Cfg.sAudioFormat = c.getString(L"sAudioFormat", w, sizeof(w) / sizeof(w[0])) ? w : d.sAudioFormat;
	Cfg.nVideo = c.getInteger(L"nVideo", d.nVideo);
	Cfg.nAudio = c.getInteger(L"nAudio", d.nAudio);
	Cfg.nTime = c.getInteger(L"nTime", d.nTime);
	Cfg.x = c.getInteger(L"x", d.x);
	Cfg.y = c.getInteger(L"y", d.y);

	return true;
}