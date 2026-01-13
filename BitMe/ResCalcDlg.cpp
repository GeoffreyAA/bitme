#include "stdafx.h"
#include "BitMe.h"
#include "ResCalcDlg.h"

#include "Library\Library.h"
#include "Library\Win32Library.h"
#include "Library\ResourceString.h"
#include "Library\Templates.h"
#include "Application.h"
#include <math.h>

#include "TmpLibrary.h"

CResCalcDlg::CResCalcDlg(CWnd *pParent) : CDialog(CResCalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResCalcDlg)
	//}}AFX_DATA_INIT
}

void CResCalcDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResCalcDlg)
	DDX_Control(pDX, IDC_GROUPBOX1, GroupDimensions);
	DDX_Control(pDX, IDC_GROUPBOX2, GroupAspect);
	DDX_Control(pDX, IDC_EDIT1, Width);
	DDX_Control(pDX, IDC_EDIT2, Height);
	DDX_Control(pDX, IDC_EDIT3, AspectX);
	DDX_Control(pDX, IDC_EDIT4, AspectY);
	DDX_Control(pDX, IDC_CHECK1, CheckRound);
	DDX_Control(pDX, IDC_COMBO1, Factors);
	DDX_Control(pDX, IDC_LABEL1, LabelRoundingError);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CResCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CResCalcDlg)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnChangeWidth)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnChangeHeight)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnChangeAspectX)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnChangeAspectY)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckRound)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeFactors)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CResCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Initialise();

	return TRUE;
}

void CResCalcDlg::OnOK()
{
}

BOOL CResCalcDlg::PreTranslateMessage(MSG *pMsg)
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

void CResCalcDlg::Initialise()
{
	UpdateStrings();
	UpdateControls();
	UpdateWindowSize();
}

void CResCalcDlg::UpdateControls()
{
	SetWindowFloat(Width.GetSafeHwnd(), Model.getWidth());
	SetWindowFloat(Height.GetSafeHwnd(), Model.getHeight());
	SetWindowFloat(AspectX.GetSafeHwnd(), Model.getAspectX());
	SetWindowFloat(AspectY.GetSafeHwnd(), Model.getAspectY());

	CheckRound.SetCheck(Model.isRoundingEnabled());
	Factors.EnableWindow(Model.isRoundingEnabled());

	wchar_t w[64];

	FloatToStr(Model.getRoundingValue(), w, sizeof(w) / sizeof(w[0]));

	if (Factors.SelectString(-1, w) == CB_ERR)
	{
		int index = Factors.AddString(w);

		if (index >= 0)
		{
			Factors.SetCurSel(index);
		}
	}

	ResolutionModel m(Model);
	m.enableRounding(false);

	swprintfs(w, sizeof(w) / sizeof(w[0]), L"%s %s %g %s; %s %g %s",
										   ResourceString(L"IDS_ROUNDING_ERROR").c_str(),
										   ResourceString(L"IDS_WIDTH").c_str(),
										   fabs(Model.getWidth() - m.getWidth()),
										   ResourceString(L"IDS_ABRV_PIXEL").c_str(),
										   ResourceString(L"IDS_HEIGHT").c_str(),
										   fabs(Model.getHeight() - m.getHeight()),
										   ResourceString(L"IDS_ABRV_PIXEL").c_str());

	LabelRoundingError.SetWindowText(w);
}

void CResCalcDlg::UpdateStrings()
{
	SetWindowText(ResourceString(L"IDS_RESOLUTION_CALC"));
	GroupDimensions.SetWindowText(ResourceString(L"IDS_DIMENSIONS"));
	GroupAspect.SetWindowText(ResourceString(L"IDS_ASPECT_RATIO"));
	CheckRound.SetWindowText(ResourceString(L"IDS_ROUND_TO_MULTIPLE"));
}

void CResCalcDlg::UpdateWindowSize()
{
	/*
	const int Space = 18;

	HWND hDlg = GetSafeHwnd();

	HWND hBottom = CheckRound.GetCheck() ? LabelRoundingError.GetSafeHwnd()
										 : CheckRound.GetSafeHwnd();

	int h = GetWindowTop(hBottom) + GetWindowHeight(hBottom) - GetWindowTop(hDlg) + Space;

	SetWindowSize(hDlg, GetWindowWidth(hDlg), h);
	*/
}

void CResCalcDlg::OnChangeWidth()
{
	Model.setWidth(GetWindowFloat(Width.GetSafeHwnd()));

	UpdateControls();
}

void CResCalcDlg::OnChangeHeight()
{
	Model.setHeight(GetWindowFloat(Height.GetSafeHwnd()));

	UpdateControls();
}

void CResCalcDlg::OnChangeAspectX()
{
	Model.setAspectX(GetWindowFloat(AspectX.GetSafeHwnd()));

	UpdateControls();
}

void CResCalcDlg::OnChangeAspectY()
{
	Model.setAspectY(GetWindowFloat(AspectY.GetSafeHwnd()));

	UpdateControls();
}

void CResCalcDlg::OnCheckRound()
{
	Model.enableRounding(ToBool(CheckRound.GetCheck()));

	UpdateControls();
	UpdateWindowSize();
}

void CResCalcDlg::OnChangeFactors()
{
	Model.setRoundingValue(GetWindowFloat(Factors.GetSafeHwnd()));

	UpdateControls();
}

void CResCalcDlg::OnReturnKey()
{
	CWnd *p = GetFocus();

	if (p)
	{
		switch (p->GetDlgCtrlID())
		{
			case IDC_EDIT1:
				OnChangeWidth();
				break;

			case IDC_EDIT2:
				OnChangeHeight();
				break;

			case IDC_EDIT3:
				OnChangeAspectX();
				break;

			case IDC_EDIT4:
				OnChangeAspectY();
				break;
		}
	}
}

BOOL CResCalcDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	//HtmlHelp(ApplicationFile(GetHelpFileName()), L"ResCalc.htm", GetSafeHwnd());

	return TRUE;
}