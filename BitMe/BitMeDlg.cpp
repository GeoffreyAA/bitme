#include "stdafx.h"

#include "BitMe.h"
#include "BitMeDlg.h"

#include "AboutDlg.h"
#include "ResCalcDlg.h"
#include "SettingsDlg.h"

#include "Application.h"
#include "Name.h"
#include "Library\ConfigConcrete.h"
#include "Library\File.h"
#include "Library\Library.h"
#include "Library\ResourceString.h"
#include "Library\Templates.h"
#include "Library\Win32Library.h"
#include "Calculation\ContainerManager.h"
#include "Calculation\Information.h"
#include "TmpLibrary.h"

const int VIDEO_MAX = 900000;				// 900,000 = 900 Mbps
const int AUDIO_MAX = 90000;				// 90,000 = 90 Mbps
const int TIME_MAX  = 32400;				// 32,400 = 9 hours

const wchar_t szFormat[] = L"%.2f";			// 0.00

const COLORREF Colour0 = 0;					// Black
const COLORREF Colour1 = 0x00c00000;		// Bluish
const COLORREF Colour2 = 0x00008000;		// Greenish
const COLORREF Colour3 = RGB(192, 0, 0);	// Reddish

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
						   ID_CALCULATION_CONTAINER14};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	ON_COMMAND(ID_TOOLS_INSTANCE, OnToolsInstance)
	ON_COMMAND(ID_TOOLS_RESCALC, OnToolsResCalc)
	ON_COMMAND(ID_TOOLS_CALCULATOR, OnToolsCalculator)
	ON_COMMAND(ID_TOOLS_GROUPING, OnToolsGrouping)
	ON_COMMAND(ID_TOOLS_COLOURS, OnToolsColours)
	ON_COMMAND(ID_TOOLS_SETTINGS, OnToolsSettings)
	ON_COMMAND(ID_TOOLS_ABOUT, OnToolsAbout)
	ON_COMMAND(ID_TOOLS_QUIT, OnToolsQuit)
	ON_COMMAND(ID_CALCULATION_OVERHEAD, OnCalculationOverhead)
	ON_COMMAND(ID_CALCULATION_INFORMATION, OnCalculationInformation)
	ON_WM_HELPINFO()
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

void CBitMeDlg::OnCancel()
{
	OnBeforeClose();
	EndDialog(IDOK);
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	if (!Cfg.Retrieve(ConfigConcrete().Get()))
		Cfg = CBitMeDlgCfg();

	CheckVideo.SetCheck(Cfg.bVideo);
	CheckAudio.SetCheck(Cfg.bAudio);
	CheckDataRate.SetCheck(Cfg.bDataRate);
	CheckCustomSize.SetCheck(Cfg.bCustomSize);
	Video.SetPos(Cfg.nVideo);
	Audio.SetPos(Cfg.nAudio);
	Time.SetPos(Cfg.nTime);

	Model.enableOverhead(Cfg.bOverhead);
	Model.setContainer(ContainerManager::CreateContainer(Cfg.sContainer.c_str()));

	SetMenuItemCheck(::GetMenu(GetSafeHwnd()), ID_TOOLS_GROUPING, Cfg.bGrouping);
	SetMenuItemCheck(::GetMenu(GetSafeHwnd()), ID_TOOLS_COLOURS, Cfg.bColours);

	SetWindowPosition(GetSafeHwnd(), Cfg.x, Cfg.y);
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
	Cfg.nVideo = Video.GetPos();
	Cfg.nAudio = Audio.GetPos();
	Cfg.nTime = Time.GetPos();
	Cfg.bGrouping = h ? GetMenuItemChecked(h, ID_TOOLS_GROUPING) : false;
	Cfg.bColours = h ? GetMenuItemChecked(h, ID_TOOLS_COLOURS) : false;
	Cfg.x = GetWindowLeft(GetSafeHwnd());
	Cfg.y = GetWindowTop(GetSafeHwnd());

	Cfg.Save(ConfigConcrete().Get());
}

void CBitMeDlg::OnBeforeClose()
{
	SaveConfiguration();
}

void CBitMeDlg::SetupControls()
{
	Video.SetRange(0, VIDEO_MAX, FALSE);
	Audio.SetRange(0, AUDIO_MAX, FALSE);
	Time.SetRange(0, TIME_MAX, FALSE);

	Video.SetPageSize(500);
	Audio.SetPageSize(128);
	Time.SetPageSize(60);
	Time.SetTicFreq(3600);

	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		SetMenuStrings(h, Containers, _countof(Containers), ContainerManager::GetAvailableContainers());
	}

#if 1

	Font1.Create(L"MS Sans Serif", 10, FW_BOLD);
	Font2.Create(L"Arial", 10);
	Font3.Create(L"MS Sans Serif", 12, FW_BOLD);

	/*
	Font1.Create(L"Arial", 9);
	Font4.Create(L"Arial", 8.5);

	SetWindowFont(GroupOptions.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(GroupVideo.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(GroupAudio.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(GroupTime.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(GroupFileSize.GetSafeHwnd(), Font1.GetFont());
	SetWindowFont(GroupCustomSize.GetSafeHwnd(), Font1.GetFont());

	SetWindowFont(CheckVideo.GetSafeHwnd(), Font4.GetFont());
	SetWindowFont(CheckAudio.GetSafeHwnd(), Font4.GetFont());
	SetWindowFont(CheckDataRate.GetSafeHwnd(), Font4.GetFont());
	SetWindowFont(CheckCustomSize.GetSafeHwnd(), Font4.GetFont());
	SetWindowFont(CheckOverhead.GetSafeHwnd(), Font4.GetFont());
	*/

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
	SetWindowText(GetApplicationName());

#ifdef _DEBUG
	SetWindowText(GetApplicationNameFull().c_str());
#endif
}

void CBitMeDlg::UpdateMenu()
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		ModifyMenu(h, 0, MF_BYPOSITION | MF_STRING, 0, ResourceString(L"IDS_MENU_TOOLS"));
		SetMenuString(h, ID_TOOLS_INSTANCE, ResourceString(L"IDS_TOOLS_INSTANCE"));
		SetMenuString(h, ID_TOOLS_RESCALC, ResourceString(L"IDS_TOOLS_RESCALC"));
		SetMenuString(h, ID_TOOLS_CALCULATOR, ResourceString(L"IDS_TOOLS_CALCULATOR"));
		SetMenuString(h, ID_TOOLS_GROUPING, ResourceString(L"IDS_TOOLS_GROUPING"));
		SetMenuString(h, ID_TOOLS_COLOURS, ResourceString(L"IDS_TOOLS_COLOURS"));
		SetMenuString(h, ID_TOOLS_SETTINGS, ResourceString(L"IDS_TOOLS_SETTINGS"));
		SetMenuString(h, ID_TOOLS_ABOUT, ResourceString(L"IDS_TOOLS_ABOUT"));
		SetMenuString(h, ID_TOOLS_QUIT, ResourceString(L"IDS_TOOLS_QUIT"));

		ModifyMenu(h, 1, MF_BYPOSITION | MF_STRING, 0, ResourceString(L"IDS_MENU_CALCULATION"));
		SetMenuString(h, ID_CALCULATION_OVERHEAD, ResourceString(L"IDS_CALCULATION_OVERHEAD"));
		SetMenuString(h, ID_CALCULATION_INFORMATION, ResourceString(L"IDS_CALCULATION_INFORMATION"));

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

	//SetWindowInt(LabelHours.GetSafeHwnd(), s / 60 / 60);
	//SetWindowInt(LabelMinutes.GetSafeHwnd(), s / 60);
	//SetWindowInt(LabelSeconds.GetSafeHwnd(), s);

	SetWindowFloat(LabelHours.GetSafeHwnd(), s / 60.0 / 60.0, szFormat);
	SetWindowFloat(LabelMinutes.GetSafeHwnd(), s / 60.0, szFormat);
	SetWindowInt(LabelSeconds.GetSafeHwnd(), s);

	SetWindowInt(THrs.GetSafeHwnd(), s / 60 / 60);
	SetWindowInt2(TMin.GetSafeHwnd(), s / 60 % 60);
	SetWindowInt2(TSec.GetSafeHwnd(), s % 60);

	// File Size; Data Rate
	bool bGroup = GetMenuItemChecked(::GetMenu(GetSafeHwnd()), ID_TOOLS_GROUPING);

	if (CheckDataRate.GetCheck())
	{
		double bps = Model.getDataRate();

		SetWindowFloat2(LabelFS1.GetSafeHwnd(), Information(bps).getKB(), szFormat, bGroup);
		SetWindowFloat2(LabelFS2.GetSafeHwnd(), BitsToKilobits(bps), szFormat, bGroup);
		SetWindowFloat2(LabelFS3.GetSafeHwnd(), BitsToMegabits(bps), szFormat, bGroup);
	}
	else
	{
		Information i(Model.getFileSize());

		SetWindowFloat2(LabelFS1.GetSafeHwnd(), i.getKB(), szFormat, bGroup);
		SetWindowFloat2(LabelFS2.GetSafeHwnd(), i.getMB(), szFormat, bGroup);
		SetWindowFloat2(LabelFS3.GetSafeHwnd(), i.getGB(), szFormat, bGroup);
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
	SelectContainer(Model.getContainer().getName());
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
	SetWindowTextRange(LabelTMin.GetSafeHwnd(), Time.GetRangeMin(), ResourceString(L"IDS_SECONDS_ABBRV"));
	SetWindowTextRange(LabelTMax.GetSafeHwnd(), Time.GetRangeMax() / 60 / 60, ResourceString(L"IDS_HOURS_ABBRV"));

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
				CustomSize.SetSel(0, -1);
				break;
		}
	}
}

BOOL CBitMeDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		if (SelectMenuItemID(h, Containers, _countof(Containers), LOWORD(wParam)))
		{
			Model.setContainer(ContainerManager::CreateContainer(GetSelectedContainer().c_str()));
			UpdateControls();
		}
	}

	switch (HIWORD(wParam))
	{
		case EN_SETFOCUS:
			SelectEditText((HWND)lParam);
			break;
	}

	return CDialog::OnCommand(wParam, lParam);
}

HBRUSH CBitMeDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd && pDC)
	{
		const bool c = GetMenuItemChecked(::GetMenu(GetSafeHwnd()), ID_TOOLS_COLOURS);

		switch (pWnd->GetDlgCtrlID())
		{
			case IDC_LABEL1:
			case IDC_LABEL2:
			case IDC_LABEL3:
			case IDC_LABEL4:
				pDC->SetTextColor(c ? Colour1 : Colour0);
				break;

			case IDC_LABEL5:
			case IDC_LABEL6:
			case IDC_LABEL7:
				pDC->SetTextColor(c ? Colour2 : Colour0);
				break;

			case IDC_LABEL8:
			case IDC_LABEL9:
			case IDC_LABEL10:
				//pDC->SetTextColor(0x00000080);
				pDC->SetTextColor(c ? Colour3 : Colour0);
				break;
		}
	}

	return (hbr);
}

String CBitMeDlg::GetSelectedContainer() const
{
	return GetMenuItemSelected(::GetMenu(GetSafeHwnd()), Containers, _countof(Containers));
}

void CBitMeDlg::SelectContainer(const wchar_t *s)
{
	SelectMenuItem(::GetMenu(GetSafeHwnd()), Containers, _countof(Containers), s);
}

void CBitMeDlg::EnableContainersAndFormats(bool b)
{
	HMENU h = ::GetMenu(GetSafeHwnd());

	if (h)
	{
		EnableMenuItems(h, Containers, _countof(Containers), b);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CBitMeDlg::OnToolsInstance()
{
	wchar_t s[MAX_PATH];

	if (!GetExecutablePath(s, _countof(s)) || !ShellOpen(s, GetSafeHwnd()))
		MsgBox(ResourceString(L"IDS_ERROR_INSTANCE"), ResourceString(L"IDS_ERROR"), GetSafeHwnd(), MSG_ERROR);
}

void CBitMeDlg::OnToolsResCalc()
{
	CResCalcDlg().DoModal();
}

void CBitMeDlg::OnToolsCalculator()
{
	if (!ShellOpen(L"calc", GetSafeHwnd()))
		MsgBox(ResourceString(L"IDS_ERROR_CALCULATOR"), ResourceString(L"IDS_ERROR"), GetSafeHwnd(), MSG_ERROR);
}

void CBitMeDlg::OnToolsGrouping()
{
	ToggleMenuItemCheck(::GetMenu(GetSafeHwnd()), ID_TOOLS_GROUPING);
	UpdateControls();
}

void CBitMeDlg::OnToolsColours()
{
	ToggleMenuItemCheck(::GetMenu(GetSafeHwnd()), ID_TOOLS_COLOURS);
	RedrawWindow();
}

void CBitMeDlg::OnToolsSettings()
{
	if (CSettingsDlg().DoModal() == IDOK)
	{
		UpdateWindowTitle();
		UpdateMenu();
		UpdateStrings();
	}
}

void CBitMeDlg::OnToolsAbout()
{
	CAboutDlg().DoModal();
}

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

void CBitMeDlg::OnCalculationInformation()
{
	MsgBox(Model.getInformation().c_str(), ResourceString(L"IDS_INFORMATION"), GetSafeHwnd());
}

BOOL CBitMeDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	ShellOpen(GetURL(), nullptr);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CBitMeDlgCfg::CBitMeDlgCfg() : bVideo(true),
							   bAudio(true),
							   bDataRate(false),
							   bCustomSize(false),
							   bOverhead(true),
							   sContainer(L"MP4/MOV/3GP"),
							   nVideo(2000), nAudio(192), nTime(7200),
							   bGrouping(true), bColours(true),
							   x(32), y(32)
{
}

bool CBitMeDlgCfg::Save(Configuration &to) const
{
	to.SetBool(L"bVideo", bVideo);
	to.SetBool(L"bAudio", bAudio);
	to.SetBool(L"bDataRate", bDataRate);
	to.SetBool(L"bCustomSize", bCustomSize);
	to.SetBool(L"bOverhead", bOverhead);
	to.SetString(L"sContainer", sContainer.c_str());
	to.SetInt(L"nVideo", nVideo);
	to.SetInt(L"nAudio", nAudio);
	to.SetInt(L"nTime", nTime);
	to.SetBool(L"bGrouping", bGrouping);
	to.SetBool(L"bColours", bColours);
	to.SetInt(L"x", x);
	to.SetInt(L"y", y);

	return true;
}

bool CBitMeDlgCfg::Retrieve(const Configuration &from)
{
	const CBitMeDlgCfg def;

	if (!from.GetBool(L"bVideo", bVideo))			bVideo = def.bVideo;
	if (!from.GetBool(L"bAudio", bAudio))			bAudio = def.bAudio;
	if (!from.GetBool(L"bDataRate", bDataRate))		bDataRate = def.bDataRate;
	if (!from.GetBool(L"bCustomSize", bCustomSize))	bCustomSize = def.bCustomSize;
	if (!from.GetBool(L"bOverhead", bOverhead))		bOverhead = def.bOverhead;
	if (!from.GetString(L"sContainer", sContainer))	sContainer = def.sContainer;
	if (!from.GetInt(L"nVideo", nVideo))			nVideo = def.nVideo;
	if (!from.GetInt(L"nAudio", nAudio))			nAudio = def.nAudio;
	if (!from.GetInt(L"nTime", nTime))				nTime = def.nTime;
	if (!from.GetBool(L"bGrouping", bGrouping))		bGrouping = def.bGrouping;
	if (!from.GetBool(L"bColours", bColours))		bColours = def.bColours;
	if (!from.GetInt(L"x", x))						x = def.x;
	if (!from.GetInt(L"y", y))						y = def.y;

	return true;
}