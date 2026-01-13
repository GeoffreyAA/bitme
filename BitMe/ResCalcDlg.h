#ifndef __C_RES_CALC_DLG_H__
#define __C_RES_CALC_DLG_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "Calculation\ResolutionModel.h"

class CResCalcDlg : public CDialog
{
public:
	CResCalcDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CResCalcDlg)
	enum { IDD = IDD_RESCALC_DIALOG };
	CButton	GroupDimensions;
	CButton	GroupAspect;
	CEdit	Width;
	CEdit	Height;
	CEdit	AspectX;
	CEdit	AspectY;
	CButton	CheckRound;
	CComboBox	Factors;
	CStatic	LabelRoundingError;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CResCalcDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

protected:
	void Initialise();
	void UpdateControls();
	void UpdateStrings();
	void UpdateWindowSize();

	void OnChangeWidth();
	void OnChangeHeight();
	void OnChangeAspectX();
	void OnChangeAspectY();
	void OnReturnKey();

	//{{AFX_MSG(CResCalcDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckRound();
	afx_msg void OnChangeFactors();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ResolutionModel Model;
};

//{{AFX_INSERT_LOCATION}}

#endif