////////////////////////////////////////////////////////////////////////////
//
//
//    Project     : MyNetPhone Ver. 1.0
//    Description : Video Conferencing over the LAN.
//	  Author      :	Vladiimir Novick ( v_novick@yahoo.com)
//    Date        : 17/12/2005
//
//
//    File description : 
//    Name    : RequestDlg.cpp
//    Details : Dialog box which display accept/reject choice , when 
//				invitation from remote host arrives.
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "MyNetPhoneServer.h"
#include "RequestDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RequestDlg dialog


RequestDlg::RequestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RequestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RequestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RequestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RequestDlg, CDialog)
	//{{AFX_MSG_MAP(RequestDlg)
	ON_BN_CLICKED(IDOK, OnAccept)
	ON_BN_CLICKED(IDREJECT, OnReject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





BOOL RequestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char str[600];
	sprintf(str,"Connection request from user %s ",rname);

	this->SetDlgItemText(IDC_MESG,str);
	
	return TRUE;
}


/**
*    Set remote user name and address
*/  

void RequestDlg::SetParameter(char *hostname,char *hostaddress,CDialog *dlg) 
{

strcpy(rname,hostname);
strcpy(raddress,hostaddress);
pdlg=dlg;
	
}


/**
*    User has accepted the connection request
*    Now send acceptance request to remote user
*    and start the conference
*/  

void RequestDlg::OnAccept() 
{
this->OnCancel();

// Send notification to remote user
//((CMyNetPhoneDlg*)pdlg)->dcontrol.SendControlMessage(MESG_ACCEPT,NULL);



// Start the conference...
//((CMyNetPhoneDlg*)pdlg)->StartConference();



}



/**
*    User has rejected  the connection request
*    Now send reject notification request to remote user
*/  

void RequestDlg::OnReject() 
{
	
	// Send notification to remote user
//	((CMyNetPhoneDlg*)pdlg)->dcontrol.SendControlMessage(MESG_REJECT,NULL);


	CDialog::OnCancel();
}
