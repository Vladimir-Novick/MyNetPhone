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
//    Name    :  VideoCapture.cpp
//    Details :  Captures the frames from webcam.
//
//
/////////////////////////////////////////////////////////////////////////////


#include "Stdafx.h"
#include "VideoCapture.h"
#include "MyNetPhoneServerDlg.h"


#include <afxmt.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VideoCapture::VideoCapture()
{
	m_capwnd=NULL;
	isOver=FALSE;
	
//	log.Open("videocapture.log",CFile::modeCreate | CFile::modeWrite);
}





VideoCapture::~VideoCapture()
{
}





void VideoCapture::SetDialog(CDialog *dialog)
{
	dlg=dialog;
}





BOOL VideoCapture::Initialize()
{
char devname[100],devversion[100];
char str[200];
int index=1;

m_capwnd = capCreateCaptureWindow("Capture",WS_POPUP,0,0,1,1,0,0);


	if(m_capwnd==NULL)
	{
//		log.WriteString("\n Unable to create capture window");
		return FALSE;
	}

	

	//connect callback functions
	capSetUserData(m_capwnd,this);


	//Change destroy functions also........

     capSetCallbackOnVideoStream(m_capwnd,OnCaptureVideo);
 
	capGetDriverDescription(index,devname,100,devversion,100);
	
	sprintf(str,"\n Driver name = %s version = %s ",devname,devversion);
//	log.WriteString(str);

	// Connect to webcam driver
	if( ! capDriverConnect(m_capwnd,index) )
	{
		
		// Device may be open already or it may not have been
		// closed properly last time.
		AfxMessageBox("Unable to open Video Capture Device");
//		log.WriteString("\n Unable to connect driver to the window");
		m_capwnd=NULL;
		return FALSE;
	}

	// Set the capture parameters
	if(SetCapturePara()==FALSE)
	{
//	log.WriteString("\n Setting capture parameters failed");
	capDriverDisconnect(m_capwnd);
	return FALSE;
	}

	
return TRUE;
}




/**
*   Start capturing frames from webcam
*
*/

BOOL VideoCapture::StartCapture()
{
	// Start live capturing ...
	if(capCaptureSequenceNoFile(m_capwnd)==FALSE)
	{
//	log.WriteString("\n Failed to capture Sequence ..");
	return FALSE;
	}
	

return TRUE;

}





/**
*   Stop the capturing process
*
*/

BOOL VideoCapture::StopCapture()
{
	
	capCaptureStop(m_capwnd);
	capCaptureAbort(m_capwnd);
	Sleep(500);	

return TRUE;
}






/**
*   Stop the catpure process and disconnect the driver
*
*/
void VideoCapture::Destroy()
{

	if(m_capwnd==NULL) return;
    
    // Stop the capturing process    
	capCaptureAbort(m_capwnd);
          
    // Disable the callback function..
	capSetCallbackOnVideoStream(m_capwnd, NULL);
     
	Sleep(300);		// This delay is important...
			
	// Finally disconnect the driver
    capDriverDisconnect(m_capwnd);
}








/**
*
*     Set various capture parameters...
*
*/

BOOL  VideoCapture::SetCapturePara()
{
	CAPTUREPARMS CapParms={0};	


	capCaptureGetSetup(m_capwnd,&CapParms,sizeof(CapParms));

	CapParms.fAbortLeftMouse = FALSE;
	CapParms.fAbortRightMouse = FALSE;
	CapParms.fYield = TRUE;
	CapParms.fCaptureAudio = FALSE;
	CapParms.wPercentDropForError = 50;

	if(capCaptureSetSetup(m_capwnd,&CapParms,sizeof(CapParms))==FALSE)
	{
//	log.WriteString("\n Failed to set the capture parameters ");
	return FALSE;
	}

	// Set Video Format 

	capGetVideoFormat(m_capwnd,&m_bmpinfo,sizeof(m_bmpinfo));

	m_bmpinfo.bmiHeader.biWidth=IMAGE_WIDTH;
	m_bmpinfo.bmiHeader.biHeight=IMAGE_HEIGHT;

	BOOL ret=capSetVideoFormat(m_capwnd,&m_bmpinfo,sizeof(m_bmpinfo));

	if(ret==TRUE)
//	log.WriteString("\n Video parameters set properly");

	return TRUE;
}




/**
*
*  Allocate Memory for DIB image buffer
* 
*/

int VideoCapture::AllocateMemory(PBITMAPINFO &bmpinfo)
{
int size1,size2,size;
BITMAPINFO tbmp;
char  str[200];

	capGetVideoFormat(m_capwnd,&tbmp,sizeof(tbmp));

	size1 = getFormatSize ( tbmp );
	size2 = getImageSize ( tbmp );
	size = size1 + size2;


	sprintf(str,"\n Formatsize = %d imagesize = %d , fun_size = %d ",
			 size1,size2, capGetVideoFormatSize(m_capwnd));
//	log.WriteString(str);

	bmpinfo=(BITMAPINFO *) new BYTE[size];

	
	if(bmpinfo==NULL)
	{
	AfxMessageBox("Unable to allocate memory");
    return -1;
	}

	memset(bmpinfo,0,sizeof(*bmpinfo));

	capGetVideoFormat(m_capwnd,bmpinfo,sizeof(*bmpinfo));
	return size1;


}




/**
*
*   Calculates the Format Size for DIB image
*
*/

int VideoCapture::getFormatSize(BITMAPINFO bmp)
{
int size;
	size=(bmp.bmiHeader.biSize!=0)?bmp.bmiHeader.biSize :sizeof(BITMAPINFOHEADER);

	//return (size+ bmp.bmiHeader.biClrUsed *sizeof(RGBQUAD));

	return size; //RGBQUAD is absent for 24 bit bmp image.
}






/**
*	Calculates the Size of Image
*
*/

int VideoCapture::getImageSize(BITMAPINFO bmp)
{
int size;
BITMAPINFOHEADER head=bmp.bmiHeader;


	if( head.biSizeImage==0 )
	{
		size=( head.biWidth * head.biHeight * head.biBitCount)/8;
	}
	else
	size = head.biSizeImage;

return size;

}



/**
*    Invoked when the video frame is captured by the driver
*
*
*/

LRESULT CALLBACK OnCaptureVideo(HWND mwnd,LPVIDEOHDR lphdr)
{

VideoCapture *vidcap=(VideoCapture *)capGetUserData(mwnd);

   if(vidcap!=NULL )
   ((CMyNetPhoneServerDlg*) (vidcap->dlg))->SendVideo(lphdr->lpData,lphdr->dwBytesUsed);

 
return TRUE;

}



