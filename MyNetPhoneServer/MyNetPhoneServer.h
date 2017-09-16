// MyNetPhoneServer.h : main header file for the MYNETPHONESERVER application
//

#if !defined(AFX_MYNETPHONESERVER_H__AF5393FA_21FB_4813_AAB6_1279F01C64AB__INCLUDED_)
#define AFX_MYNETPHONESERVER_H__AF5393FA_21FB_4813_AAB6_1279F01C64AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneServerApp:
// See MyNetPhoneServer.cpp for the implementation of this class
//

class CMyNetPhoneServerApp : public CWinApp
{
public:
	CMyNetPhoneServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyNetPhoneServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyNetPhoneServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYNETPHONESERVER_H__AF5393FA_21FB_4813_AAB6_1279F01C64AB__INCLUDED_)
