////////////////////////////////////////////////////////////////////////////
//
//
//    Project     : MyNetPhoneClient Ver. 1.0
//    Description : Video Conferencing over the LAN.
//	  Author      :	Vladiimir Novick ( v_novick@yahoo.com)
//    Date        : 17/12/2005
//
//
//    File description : 
//    Name    :  MyNetPhoneClient.cpp
//    Details :  Main application class
//
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyNetPhoneClient.h"
#include "MyNetPhoneClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneClientApp

BEGIN_MESSAGE_MAP(CMyNetPhoneClientApp, CWinApp)
	//{{AFX_MSG_MAP(CMyNetPhoneClientApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneClientApp construction

CMyNetPhoneClientApp::CMyNetPhoneClientApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyNetPhoneClientApp object

CMyNetPhoneClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneClientApp initialization

BOOL CMyNetPhoneClientApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization

	CMyNetPhoneClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
