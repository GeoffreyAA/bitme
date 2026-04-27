#include "stdafx.h"

#include "BitMe.h"
#include "SettingsDlg.h"

#include "Library\Language.h"
#include "Library\ResourceString.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSettingsDlg::CSettingsDlg(CWnd *pParent) : CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	//}}AFX_DATA_INIT
}

void CSettingsDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Control(pDX, IDC_COMBO1, Languages);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Initialise();

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSettingsDlg::Initialise()
{
	SetWindowText(ResourceString(L"IDS_SETTINGS"));
	SetDlgItemText(IDC_LANGUAGE, ResourceString(L"IDS_LANGUAGE"));

	StringList s = LanguageManager::getInstance().getAvailableLanguages();

	for (StringList::const_iterator i = s.begin(); i != s.end(); i++)
	{
		Languages.AddString((*i).c_str());
	}

	Languages.SelectString(-1, LanguageManager::getInstance().getCurrentLanguage().getName().c_str());

	SetDlgItemText(IDOK, ResourceString(L"IDS_OK"));
	SetDlgItemText(IDCANCEL, ResourceString(L"IDS_CANCEL"));
}

void CSettingsDlg::OnOK()
{
	wchar_t w[512];
	Languages.GetWindowText(w, sizeof(w) / sizeof(w[0]));

	LanguageManager::getInstance().setCurrentLanguage(w);

	EndDialog(IDOK);
}

BOOL CSettingsDlg::OnHelpInfo(HELPINFO *pHelpInfo)
{
	return TRUE;
}