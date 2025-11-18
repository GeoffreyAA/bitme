#ifndef __C_ABOUT_DLG_H__
#define __C_ABOUT_DLG_H__

#if _MSC_VER > 1000
#pragma once
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUT_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

protected:
	void Initialise();

	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHomePage();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif