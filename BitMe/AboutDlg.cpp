#include "stdafx.h"

#include "BitMe.h"
#include "AboutDlg.h"

#include "Application.h"
#include "Name.h"
#include "Library\Library.h"
#include "Library\ResourceString.h"
#include "Library\Win32Library.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAboutDlg::Initialise()
{
	wchar_t s[128];
	swprintfs(s, sizeof(s) / sizeof(s[0]), L"%s %s", ResourceString(L"IDS_ABOUT").c_str(),
													 GetApplicationName());

	SetWindowText(s);
	SetDlgItemText(IDC_ABOUT_TEXT, GetApplicationNameEx().c_str());
	SetDlgItemText(IDC_BUTTON1, ResourceString(L"IDS_HOME_PAGE"));
	SetDlgItemText(IDOK, ResourceString(L"IDS_OK"));
}

void CAboutDlg::OnHomePage()
{
	ShellOpen(L"https://github.com/GeoffreyAA/bitme", NULL);
}

BOOL CAboutDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	return TRUE;
}