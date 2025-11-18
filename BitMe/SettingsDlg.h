#ifndef __C_SETTINGS_DLG_H__
#define __C_SETTINGS_DLG_H__

#if _MSC_VER > 1000
#pragma once
#endif

class CSettingsDlg : public CDialog
{
public:
	CSettingsDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_SETTINGS_DIALOG };
	CComboBox	Languages;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

protected:
	void Initialise();
	void SetupControls();
	void UpdateControls();

	//{{AFX_MSG(CSettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif