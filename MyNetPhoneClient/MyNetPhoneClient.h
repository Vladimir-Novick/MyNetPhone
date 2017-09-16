// MyNetPhoneClient.h : main header file for the MyNetPhoneClient application
//

#if !defined(AFX_MyNetPhoneClient_H__B0986304_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
#define AFX_MyNetPhoneClient_H__B0986304_5F44_11D6_8897_000B2B0F84B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneClientApp:
// See MyNetPhoneClient.cpp for the implementation of this class
//

class CMyNetPhoneClientApp : public CWinApp
{
public:
	CMyNetPhoneClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyNetPhoneClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyNetPhoneClientApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyNetPhoneClient_H__B0986304_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
