#include "stdafx.h"

#include "BitMe.h"
#include "AboutDlg.h"

#include "Application.h"
#include "Library\Library.h"
#include "Library\Win32Library.h"
#include "Library\ResourceString.h"


///////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg(CWnd *pParent) : CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnHomePage)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Initialise();

	return TRUE;
}


///////////////////////////////////////////////////////////////

void CAboutDlg::Initialise()
{
	wchar_t s[1024];

	swprintfs(s, sizeof(s) / sizeof(s[0]), L"%s %s", ResourceString(L"IDS_ABOUT").c_str(),
													 GetApplicationName());

	SetWindowText(s);

	wchar_t d[128];
	SYSTEMTIME st;

	if (!TimeToSystemTimeLocal(GetBuildTime(), &st) || !GetDateTimeFormatted(d, sizeof(d) / sizeof(d[0]), &st))
	{
		wcscpys(d, ResourceString(L"IDS_DATE_ERROR"), sizeof(d) / sizeof(d[0]));
	}

	swprintfs(s, sizeof(s) / sizeof(s[0]), L"%s\n"
										   L"© Geoffrey Angapa, 2021. %s.\n\n"
										   L"%s %s\n\n"
										   L"%s",

										   GetApplicationNameFull2().c_str(),
										   ResourceString(L"IDS_ALL_RIGHTS_RESERVED").c_str(),
										   ResourceString(L"IDS_COMPILED_ON").c_str(), d,
										   ResourceString(L"IDS_LICENCE").c_str());

	SetDlgItemText(IDC_ABOUT_TEXT, s);
	SetDlgItemText(IDOK, ResourceString(L"IDS_OK"));
	SetDlgItemText(IDC_BUTTON1, ResourceString(L"IDS_HOME_PAGE"));
}

void CAboutDlg::OnHomePage()
{
	ShellOpen(L"https://github.com/GeoffreyAA/bitme", NULL);
}

BOOL CAboutDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	return TRUE;
}