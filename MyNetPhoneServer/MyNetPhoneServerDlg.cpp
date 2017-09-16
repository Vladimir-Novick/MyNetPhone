// MyNetPhoneServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyNetPhoneServer.h"
#include "MyNetPhoneServerDlg.h"

#include ".\..\decoder\convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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
// CMyNetPhoneServerDlg dialog

CMyNetPhoneServerDlg::CMyNetPhoneServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyNetPhoneServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyNetPhoneServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyNetPhoneServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyNetPhoneServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyNetPhoneServerDlg, CDialog)
	//{{AFX_MSG_MAP(CMyNetPhoneServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneServerDlg message handlers

BOOL CMyNetPhoneServerDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Create Recording  thread
	record=new RecordSound(this);
	record->CreateThread();


	// Prepare for capture video from webcam...
	vidcap=new VideoCapture();
	vidcap->SetDialog(this);

	if(vidcap->Initialize()) // success
	{
		
		
		this->m_bmpinfo=&vidcap->m_bmpinfo;
			
		isVideo=TRUE;

		// Initialize the compressor

		     // Initialize table for RGB to YUV conversion
			InitLookupTable();

			// Initialize the compressor
			cparams.format = CPARAM_QCIF;
			InitH263Encoder(&cparams);  

			// Set up the callback function
			WriteByteFunction = OwnWriteFunction;

	}
	else
	{
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

	
	}
	
	
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
	wnd=this->GetDlgItem(IDC_LOCALVIDEO);
   	bwnd=this->GetDlgItem(IDC_LOCALBORDER);
   	bwnd->GetWindowRect(brect);
	ScreenToClient(brect);

	local_wnd_x=brect.TopLeft().x+(brect.Width()-IMAGE_WIDTH)/2;
	local_wnd_y=brect.TopLeft().y+(brect.Height()-IMAGE_HEIGHT)/2;
	
	// Centre the local video window
	wnd->SetWindowPos(&wndTop,local_wnd_x-4,local_wnd_y-4,IMAGE_WIDTH+9,IMAGE_HEIGHT+9,SWP_SHOWWINDOW | SWP_DRAWFRAME);

	// For remote video display window

	

	// Get Dialog DC
	m_hdc=this->GetDC()->m_hDC;

	
	// Initialize DIB for drawing...
	hdib=::DrawDibOpen();
	if(hdib!=NULL)
	{
	 
		::DrawDibBegin(hdib,
					   m_hdc,
					   -1,				// don't stretch
					   -1,				// don't stretch
					   &m_bmpinfo->bmiHeader,
					   IMAGE_WIDTH,         // width of image
					   IMAGE_HEIGHT,        // height of image
					   0				
					   );
	
	}
    


	// Setup the connect dialog box


	
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






void CMyNetPhoneServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyNetPhoneServerDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyNetPhoneServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyNetPhoneServerDlg::SendVideo(BYTE *data, int size)
{
CRect wndrect;
Bits bits;		// Various count about compression


	if(vidcap->isOver==TRUE)
	return;
	
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

void CMyNetPhoneServerDlg::OnClose() 
{
	// If conference is going on...then 
	// it must be destroyed...
	if(isStarted)


	// Close the control session
	dcontrol.CloseSocket();

	// End recording and player thread

	record->PostThreadMessage(WM_RECORDSOUND_ENDTHREAD,0,0);
	

	// Close the video capture device
	vidcap->Destroy();

		
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
