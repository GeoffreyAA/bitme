#ifndef __C_BITME_APP_H__
#define __C_BITME_APP_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error Include "stdafx.h" before including this file for PCH
#endif

#include "Resource.h"

class CBitMeApp : public CWinApp
{
public:
	CBitMeApp();

	//{{AFX_VIRTUAL(CBitMeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBitMeApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif