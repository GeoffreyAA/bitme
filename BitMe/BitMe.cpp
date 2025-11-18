#include "stdafx.h"

#include "BitMe.h"
#include "BitMeDlg.h"


///////////////////////////////////////////////////////////////

CBitMeApp Application;


///////////////////////////////////////////////////////////////

CBitMeApp::CBitMeApp()
{
}

BEGIN_MESSAGE_MAP(CBitMeApp, CWinApp)
	//{{AFX_MSG_MAP(CBitMeApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

BOOL CBitMeApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CBitMeDlg Dlg;
	m_pMainWnd = &Dlg;

	Dlg.DoModal();

	return FALSE;
}