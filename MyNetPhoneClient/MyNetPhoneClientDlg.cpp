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
//    Name    : MyNetPhoneClientDlg.cpp
//    Details : Main dialog class
//
//
/////////////////////////////////////////////////////////////////////////////





#include "stdafx.h"
#include "MyNetPhoneClient.h"
#include "MyNetPhoneClientDlg.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()










/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneClientDlg dialog




// Global varialbes...
int count=0;
unsigned char cdata[10000];
int cbuffer_size=10000;
unsigned char rgbdata[80000];
int buffersize=80000;




// Callback function gets invoked during compression...
// It returns the compressed data byte by byte...
void OwnWriteFunction(int byte)
{
	if(count<cbuffer_size)
	cdata[count]=(unsigned char)byte;
	
	count++;

}



CMyNetPhoneClientDlg::CMyNetPhoneClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyNetPhoneClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyNetPhoneClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyNetPhoneClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyNetPhoneClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}





BEGIN_MESSAGE_MAP(CMyNetPhoneClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMyNetPhoneClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	// Conference menu handlers
	ON_COMMAND(CONF_CONNECT,OnConnect)
	ON_COMMAND(CONF_DISCONNECT,OnDisconnect)
	ON_COMMAND(CONF_EXIT,OnCancel)
	
	// View menu handlers
	ON_COMMAND(VIEW_LOCAL,OnViewLocal)
	ON_COMMAND(VIEW_REMOTE,OnViewRemote)
	
	// Audio menu handlers
	ON_COMMAND(AUDIO_CONTROL,OnVolumeControl)
	ON_COMMAND(AUDIO_SEND,OnAudioSend)
	ON_COMMAND(AUDIO_RECEIVE,OnAudioReceive)
	

	// Video menu handlers
	ON_COMMAND(VIDEO_SEND,OnVideoSend)
	ON_COMMAND(VIDEO_RECEIVE,OnVideoReceive)
	

	// Help menu handlers
	ON_COMMAND(HELP_ABOUT,OnAbout)

	ON_COMMAND(IDC_BUTTON1,OnSendMesg)
	

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()










BOOL CMyNetPhoneClientDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	// Open log file...
//	log.Open("main.log",CFile::modeCreate | CFile::modeWrite);



	// Disable the menu items...at startup
	menu=this->GetMenu();
	menu->EnableMenuItem(CONF_CONNECT,MF_ENABLED);
	menu->EnableMenuItem(CONF_DISCONNECT,MF_DISABLED | MF_GRAYED);
	menu->EnableMenuItem(AUDIO_SEND,MF_GRAYED);
	menu->EnableMenuItem(AUDIO_RECEIVE,MF_GRAYED);
	menu->EnableMenuItem(VIDEO_SEND,MF_GRAYED);
	menu->EnableMenuItem(VIDEO_RECEIVE,MF_GRAYED);
	menu->EnableMenuItem(VIEW_LOCAL,MF_GRAYED);
	menu->EnableMenuItem(VIEW_REMOTE,MF_GRAYED);
	

	list=(CListBox*)GetDlgItem(IDC_LIST1);
	bsend=(CButton*)GetDlgItem(IDC_BUTTON1);

	// Disable the send button
	bsend->EnableWindow(FALSE);

		


	// Create Player thread
	play=new PlaySound1(this);
	play->CreateThread();


	// Prepare for capture video from webcam...



		isVideo=FALSE;
			
		// Setup bmpinfo structure yourself
		m_bmpinfo=new BITMAPINFO;
		m_bmpinfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		m_bmpinfo->bmiHeader.biWidth=IMAGE_WIDTH;
		m_bmpinfo->bmiHeader.biHeight=IMAGE_HEIGHT;
		m_bmpinfo->bmiHeader.biPlanes=1;
		m_bmpinfo->bmiHeader.biBitCount=24;
		m_bmpinfo->bmiHeader.biCompression=0;
		m_bmpinfo->bmiHeader.biSizeImage=0;
		m_bmpinfo->bmiHeader.biXPelsPerMeter=0;
		m_bmpinfo->bmiHeader.biYPelsPerMeter=0;
		m_bmpinfo->bmiHeader.biClrUsed=0;
		m_bmpinfo->bmiHeader.biClrImportant=0;

		// Disable menu items...
		menu->EnableMenuItem(VIEW_LOCAL,MF_DISABLED | MF_GRAYED);
		menu->EnableMenuItem(VIDEO_SEND,MF_DISABLED | MF_GRAYED);
	

	
	
	// Capturing is not yet started...
	isCaptureStarted=FALSE;

	isViewLocalVideo=TRUE;
	isViewRemoteVideo=TRUE;

	isAudioSend=TRUE;
	isAudioReceive=TRUE;

	isVideoSend=TRUE;
	isVideoReceive=TRUE;


	
	// Initialize decompressor
	InitH263Decoder();
	
	
	// Adjust display windows
	CWnd *wnd,*bwnd;
	CRect rect,brect;

	// For local video display window


	local_wnd_x=brect.TopLeft().x+(brect.Width()-IMAGE_WIDTH)/2;
	local_wnd_y=brect.TopLeft().y+(brect.Height()-IMAGE_HEIGHT)/2;
	
	// Centre the local video window

	// For remote video display window
	wnd=this->GetDlgItem(IDC_REMOTEVIDEO);	// Video display window
   	bwnd=this->GetDlgItem(IDC_REMOTEBORDER); // Border window...
   	bwnd->GetWindowRect(brect);
	ScreenToClient(brect);

	remote_wnd_x=brect.TopLeft().x+(brect.Width()-IMAGE_WIDTH)/2;
	remote_wnd_y=brect.TopLeft().y+(brect.Height()-IMAGE_HEIGHT)/2;
	
	// Centre the remote video window
	wnd->SetWindowPos(&wndTop,remote_wnd_x-4,remote_wnd_y-4,IMAGE_WIDTH+9,IMAGE_HEIGHT+9,SWP_SHOWWINDOW | SWP_DRAWFRAME);

	

	// Get Dialog DC
	m_hdc=this->GetDC()->m_hDC;

	
	// Initialize DIB for drawing...


	hdib=::DrawDibOpen();
	if(hdib!=NULL)
	{
	 
		::DrawDibBegin(hdib,
					   m_hdc,
					   -1,				
					   -1,				
					   &m_bmpinfo->bmiHeader,
					   IMAGE_WIDTH,         
					   IMAGE_HEIGHT,        
					   0				
					   );
	
	}
    


	// Setup the connect dialog box
	connectdlg=new ConnectDlg(NULL);
	connectdlg->SetParent(this);

	
	// Setup the parent for differnt datagram sockets
	dcontrol.SetParent(this);
	daudio.SetParent(this);
	dvideo.SetParent(this);
	dtext.SetParent(this);

	// Create  control datagram socket for handling messages
	dcontrol.CreateSocket(PORT_CONTROL,TYPE_CONTROL);

	// Conference not yet started...
	isStarted=FALSE;

	
	return TRUE;  // return TRUE  unless you set the focus to a control

}






void CMyNetPhoneClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}






//  If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyNetPhoneClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}






HCURSOR CMyNetPhoneClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





void CMyNetPhoneClientDlg::OnCancel() 
{
	
	// If conference is going on...then 
	// it must be destroyed...
	if(isStarted)
	DestroyConference();

	// Close the control session
	dcontrol.CloseSocket();

	// End recording and player thread


	
	play->PostThreadMessage(WM_PLAYSOUND_ENDTHREAD,0,0);

	// Close the video capture device


		
	// Close graphics....
	if(hdib!=NULL)
	{
	::DrawDibEnd(hdib);
	::DrawDibClose(hdib);
	}
	
	// Close the encoder
	if(isVideo)
	ExitH263Encoder(&cparams);

	// close decoder ......
	ExitH263Decoder();
	

	CDialog::OnCancel();
}



/**
*	  Connect to remote host
*	  Invoked when user presses connect menu item
*	  Displays the connect dialog box
*/
void CMyNetPhoneClientDlg::OnConnect()
{

	// Show the connect dialog box
	connectdlg->DoModal();

}




/**
*	  Disconnect the remote host
*	  Invoked when user presses disconnect menu item
*	  Stops the current conference
*/
void CMyNetPhoneClientDlg::OnDisconnect()
{
	// Send notification to the remote host...
	dcontrol.SendControlMessage(MESG_DISCONNECT,NULL);

	DestroyConference();

}



/**
*	  Show / Hide the local video screen
*/
void CMyNetPhoneClientDlg::OnViewLocal()
{

	CMenu *menu=this->GetMenu();
	
	if(isViewLocalVideo)
	{
	isViewLocalVideo=FALSE;
	menu->CheckMenuItem(VIEW_LOCAL,MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
	isViewLocalVideo=TRUE;
	menu->CheckMenuItem(VIEW_LOCAL,MF_BYCOMMAND | MF_CHECKED);
	}



}




/**
*	  Show / Hide the remote video screen
*/
void CMyNetPhoneClientDlg::OnViewRemote()
{

	CMenu *menu=this->GetMenu();
	
	if(isViewRemoteVideo)
	{
	isViewRemoteVideo=FALSE;
	menu->CheckMenuItem(VIEW_REMOTE,MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
	isViewRemoteVideo=TRUE;
	menu->CheckMenuItem(VIEW_REMOTE,MF_BYCOMMAND | MF_CHECKED);
	}





}
	

	
/**
*	  Displays the volume control dialog box
*/
void CMyNetPhoneClientDlg::OnVolumeControl()
{
	
	Volume vol(IDD_DIALOG3);

 vol.DoModal();


}




/**
*	  Enables/Disables transmission of audio
*     Invoked when user presses Audio -> Send menu item
*/
void CMyNetPhoneClientDlg::OnAudioSend()
{

	if(isAudioSend)
	{
		// Stop recording audio

		//>PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		isAudioSend=FALSE;
		menu->CheckMenuItem(AUDIO_SEND,MF_BYCOMMAND | MF_UNCHECKED);

	}
	else
	{
		// Start recording audio

		//record->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING,0,0);
		isAudioSend=TRUE;
		menu->CheckMenuItem(AUDIO_SEND,MF_BYCOMMAND | MF_CHECKED);
	}
}



/**
*	  Enables/Disables reception of audio
*     Invoked when user presses Audio -> Receive menu item
*/
void CMyNetPhoneClientDlg::OnAudioReceive()
{


	if(isAudioReceive)
	{
		isAudioReceive=FALSE;
		menu->CheckMenuItem(AUDIO_RECEIVE,MF_BYCOMMAND | MF_UNCHECKED);
		
	
	}
	else
	{
		isAudioReceive=TRUE;
		menu->CheckMenuItem(AUDIO_RECEIVE,MF_BYCOMMAND | MF_CHECKED);
	}





}
	

/**
*	  Enables/Disables transmission of video
*     Invoked when user presses Video-> Send menu item
*/
void CMyNetPhoneClientDlg::OnVideoSend()
{

	if(isVideoSend)
	{
		isVideoSend=FALSE;
		menu->CheckMenuItem(VIDEO_SEND,MF_BYCOMMAND | MF_UNCHECKED);
	
	}
	else
	{
		isVideoSend=TRUE;
		menu->CheckMenuItem(VIDEO_SEND,MF_BYCOMMAND | MF_CHECKED);
	}




}




/**
*	  Enables/Disables reception of video
*     Invoked when user presses Video -> Receive menu item
*/
void CMyNetPhoneClientDlg::OnVideoReceive()
{

	if(isVideoReceive)
	{
		isVideoReceive=FALSE;
		menu->CheckMenuItem(VIDEO_RECEIVE,MF_BYCOMMAND | MF_UNCHECKED);

	
	}
	else
	{
		isVideoReceive=TRUE;
		menu->CheckMenuItem(VIDEO_RECEIVE,MF_BYCOMMAND | MF_CHECKED);
	}



}
	


/**
*	  Display the about dialog box
*/
void CMyNetPhoneClientDlg::OnAbout()
{

		CAboutDlg dlgAbout;
		dlgAbout.DoModal();

}




/**
*	  Send the message to remote host
*/
void CMyNetPhoneClientDlg::OnSendMesg()
{
unsigned char data[500];

	GetDlgItemText(IDC_EDIT1,(char*)data,500);
	
	
	if(strlen((const char*)data)>0)
	{
	dtext.SendTextData(data,strlen((const char*)data));
	SetDlgItemText(IDC_EDIT1,"");
	}
		
}




/**
*	  Display mesg received from the remote host
*/
void CMyNetPhoneClientDlg::DisplayMesg(char *mesg)
{

	list->AddString(mesg);
	// Highlight the currently added string
	// This will scroll the window automatically
	list->SetCurSel(list->GetCount()-1);

	
}



/**
*	  Display frame got from remote host
*/
void CMyNetPhoneClientDlg::DisplayRemoteFrame(unsigned char *data,int size)
{
int retvalue;

	// If remote view disabled then return...
	if(!isViewRemoteVideo)
	return;

	// If video reception disabled..then return..
	if(!isVideoReceive)
	return;

	retvalue=DecompressFrame(data,size,rgbdata,buffersize);

	if(!retvalue)
	{
//		log.WriteString("\n Decompression failed");
		return;
	}


//	log.WriteString("\n Decompression succeeded");


	::DrawDibDraw(hdib,
				  m_hdc,
				  remote_wnd_x,		// dest : left pos
				  remote_wnd_y,		// dest : top pos
				  -1,					 // don't zoom x
				  -1,					 // don't zoom y
				  &m_bmpinfo->bmiHeader,			 // bmp header info
				  rgbdata,					 // bmp data
				  0,					 // src :left
				  0,					 // src :top
				  IMAGE_WIDTH,				 // src : width
				  IMAGE_HEIGHT,				 // src : height
				  DDF_SAME_DRAW			 // use prev params....
				  );


}



/**
*
*	Send the video frame to the remote host...
*
*/
void CMyNetPhoneClientDlg::SendVideo(BYTE *data,int size)
{
CRect wndrect;
Bits bits;		// Various count about compression



	
	if(data==NULL)
	return;


	// Display the captured frame...
	if(isViewLocalVideo)
	{

	::DrawDibDraw(hdib,
				  m_hdc,
				  local_wnd_x,		// dest : left pos
				  local_wnd_y,		// dest : top pos
				  -1,					 // don't zoom x
				  -1,					 // don't zoom y
				  &m_bmpinfo->bmiHeader,			 // bmp header info
				  data,					 // bmp data
				  0,					 // src :left
				  0,					 // src :top
				  IMAGE_WIDTH,				 // src : width
				  IMAGE_HEIGHT,				 // src : height
				  DDF_SAME_DRAW			 // use prev params....
				  );

	}

	
	if(isVideoSend)
	{

		//log.WriteString("\n Converting to YUV format..");
		
		//Convert the data from rgb format to YUV format	
		ConvertRGB2YUV(IMAGE_WIDTH,IMAGE_HEIGHT,data,yuv);


		// Reset the counter
		count=0;

		//Compress the data...to h263
		cparams.format=CPARAM_QCIF;
		cparams.inter = CPARAM_INTRA;  
		cparams.Q_intra = 8;
		cparams.data=yuv;		//  Data in YUV format...
		CompressFrame(&cparams, &bits);
		
		// Transmit the compressed frame
		//log.WriteString("Transmitting the frame");
		dvideo.SendVideoData(cdata,count);

	}

}





/**
*	  Start the conference ....
*
*/
void CMyNetPhoneClientDlg::StartConference()
{
	
	// If already started....then return
	if(isStarted)
	return;

	isStarted=TRUE;
	isViewLocalVideo=TRUE;
	isViewRemoteVideo=TRUE;
	
	// Enable / Disable menu items...
	menu->EnableMenuItem(CONF_CONNECT,MF_DISABLED | MF_GRAYED);
	menu->EnableMenuItem(CONF_DISCONNECT,MF_ENABLED);
	
	menu->EnableMenuItem(AUDIO_SEND,MF_ENABLED);
	menu->EnableMenuItem(AUDIO_RECEIVE,MF_ENABLED);
	
	menu->EnableMenuItem(VIDEO_SEND,MF_ENABLED);
	menu->EnableMenuItem(VIDEO_RECEIVE,MF_ENABLED);

	menu->EnableMenuItem(VIEW_LOCAL,MF_ENABLED);
	menu->EnableMenuItem(VIEW_REMOTE,MF_ENABLED);

	menu->CheckMenuItem(VIEW_LOCAL,MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(VIEW_REMOTE,MF_BYCOMMAND | MF_CHECKED);

	// Start text Session
	dtext.CreateSocket(PORT_TEXT,TYPE_TEXT);

	// Enable the send button
	bsend->EnableWindow(TRUE);


	// Start audio Session
	daudio.CreateSocket(PORT_AUDIO,TYPE_AUDIO);


	// Start video Session
	dvideo.CreateSocket(PORT_VIDEO,TYPE_VIDEO);


	
	// Start playing audio
	play->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING,0,0);

	


}




/**
*	  Destroy the current conference
*/
void CMyNetPhoneClientDlg::DestroyConference()
{

	// If not started / already destroyed..then return;
	if(isStarted==FALSE)
	return;

	isStarted=FALSE;
	isViewLocalVideo=FALSE;
	isViewRemoteVideo=FALSE;


	// Enable/disable menu items
	menu->EnableMenuItem(CONF_CONNECT,MF_ENABLED);
	menu->EnableMenuItem(CONF_DISCONNECT,MF_DISABLED | MF_GRAYED);


	// Disable Text session
	dtext.CloseSocket();

	// Disable the send button...
	bsend->EnableWindow(FALSE);

	// Clear the contents of text chat windows
	SetDlgItemText(IDC_EDIT1,"");
	list->ResetContent();

		
	 

	// stop audio session
	daudio.CloseSocket();

	// stop playing audio
	play->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,0,0);


	
	
	// stop video session
	dvideo.CloseSocket();

	// Update local and remote viewer..
	CWnd *wnd;


	wnd=(CWnd*)this->GetDlgItem(IDC_REMOTEVIDEO);
    wnd->Invalidate(TRUE);

	// Reset the status..


	isAudioSend=TRUE;
	menu->CheckMenuItem(AUDIO_SEND,MF_BYCOMMAND | MF_CHECKED);

	isAudioReceive=TRUE;
	menu->CheckMenuItem(AUDIO_RECEIVE,MF_BYCOMMAND | MF_CHECKED);
	
	isVideoSend=TRUE;
	menu->CheckMenuItem(VIDEO_SEND,MF_BYCOMMAND | MF_CHECKED);

	isVideoReceive=TRUE;
	menu->CheckMenuItem(VIDEO_RECEIVE,MF_BYCOMMAND | MF_CHECKED);

	menu->EnableMenuItem(AUDIO_SEND,MF_GRAYED);
	menu->EnableMenuItem(AUDIO_RECEIVE,MF_GRAYED);
	
	menu->EnableMenuItem(VIDEO_SEND,MF_GRAYED);
	menu->EnableMenuItem(VIDEO_RECEIVE,MF_GRAYED);

	menu->EnableMenuItem(VIEW_LOCAL,MF_GRAYED);
	menu->EnableMenuItem(VIEW_REMOTE,MF_GRAYED);





}
