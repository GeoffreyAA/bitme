#ifndef __AFX_STDAFX_H__
#define __AFX_STDAFX_H__

#if _MSC_VER > 1000
#pragma once
#endif

#define VC_EXTRALEAN		// Exclude rarely-used things from Windows headers

#if _MSC_VER > 1200
#include "targetver.h"
#endif

#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS	// Cuts down size of statically-linked executables

#include <afxwin.h>			// MFC core and standard components
#include <afxext.h>			// MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif

//{{AFX_INSERT_LOCATION}}

#endif