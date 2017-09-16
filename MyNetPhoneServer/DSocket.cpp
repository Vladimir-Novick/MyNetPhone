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
//    Name    : DSocket.cpp
//    Details : Datagram Socket for communication
//
//
//			***  Control Packet Format ***
//		 Type				: 1 byte
//		 Length of hostname : 1 byte
//		 Hostname			: <var>
//
//			***  Text packet format ***
//       Type               : 1 byte
//		 Length of hostname	: 1 byte
//		 Hostname           : < var>
//       Length of message  : 2 byte
//		 Message            : <var>
//
//			***  Audio packet format ***
//       Type				  : 1 byte
//		 Length of hostname	  : 1 byte
//		 Hostname             : < var>
//       size of audio data   : 2 byte
//		 Audio data           : <var>
//	
//			***  Video packet format ***
//       Type                 : 1 byte
//		 Length of hostname	  : 1 byte
//		 Hostname             : < var>
//       size of video data   : 2 byte
//		 Video data           : <var>
//
//
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "DSocket.h"
#include "RequestDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSocket

// Initialize static members...
char DSocket::remoteaddress[500]="";
char DSocket::remotename[500]="";
unsigned char DSocket::data[2000];
unsigned char DSocket::vdata[30000];
unsigned char DSocket::adata[5000];
unsigned int DSocket::length=2000;
unsigned int DSocket::vlength=30000;
unsigned int DSocket::alength=5000;



DSocket::DSocket()
{


}

DSocket::~DSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(DSocket, CSocket)
	//{{AFX_MSG_MAP(DSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// DSocket member functions



/**
*    Creates datagram socket on specified port 
*    @param port Port on which datagram socket is created
*    @param type type indicates the purpose of this socket
*			which can be control, audio or video.
*/

void DSocket::CreateSocket(int port,int dtype)
{

	
	this->Create(port,SOCK_DGRAM);
	type=dtype;

	// Get host name...
	gethostname(localname,300);
	

}




void DSocket::SetParent(CDialog *dlg)
{

	pdlg=dlg;
	

}

/**
*    Invoked when any data arrives from the remote host
*
*/
void DSocket::OnReceive(int errcode)
{
CString address;
char hname[400],str[1000],mesg[500];
unsigned int port,retvalue;
int n,len;

RequestDlg rdlg(NULL);



	// Note : if no error has occured then RETVALUE contains
	//		  the COUNT of actual bytes received.


	// Control type 
	if(type==TYPE_CONTROL)
	{
		
		retvalue=this->ReceiveFrom(data,length,address,port);

		if(retvalue==SOCKET_ERROR)
		return;
	
		// Get host name from the data.	
		for(int i=0;i<data[1];i++)
		hname[i]=data[i+2];
		hname[i]=0;

		strcpy(remotename,hname);
		strcpy(remoteaddress,(LPCTSTR)address);
		
		switch(data[0])
		{
			
			// action   : Remote user has sent the invitation for conference
			// reaction : accept/reject the invitation
			case MESG_CONNECT:
			// display the accept , reject dialog box
			rdlg.SetParameter(remotename,remoteaddress,pdlg);
			rdlg.DoModal();
			return;
			

			// action   : Remote user has disconnected
			// reaction : destroy the conference
			case MESG_DISCONNECT:
//			( (CMyNetPhoneDlg*)pdlg)->DestroyConference();
//			sprintf(str,"User %s has disconnected",hname);
			AfxMessageBox(str);
			return;
			

			// action   : Remote user has accepted the invitation
			// reaction : start the conference
			case MESG_ACCEPT:
//			AfxMessageBox("User has accepted the connection");
//			( (CMyNetPhoneDlg*)pdlg)->StartConference();
			return;

			
			// action   : Remote user has rejected the invitation
			// reaction : what to do...?
			case MESG_REJECT:
			sprintf(str,"User %s has rejected your invitation",hname);
			AfxMessageBox(str);
			return;
		
		}
	
	
		return;
	
	}


	if(type==TYPE_AUDIO)
	{
		
			retvalue=this->ReceiveFrom(adata,alength,address,port);

			if(retvalue==SOCKET_ERROR)
			return;

			// Play the audio
//			((CMyNetPhoneDlg *)pdlg)->play->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK,retvalue,(LPARAM)adata);
		
		return;
	}

	if(type==TYPE_VIDEO)
	{
		
			retvalue=this->ReceiveFrom(vdata,vlength,address,port);

			if(retvalue==SOCKET_ERROR)
			return;

//			((CMyNetPhoneDlg *)pdlg)->DisplayRemoteFrame(vdata,retvalue);

	return;
	}

	if(type==TYPE_TEXT)
	{
		
		retvalue=this->ReceiveFrom(data,length,address,port);

		if(retvalue==SOCKET_ERROR)
		return;

		// Get host name from the data.	
		// Length of username
		n=data[1];

		for(int i=0;i<n;i++)
		hname[i]=data[i+2];
		hname[i]=0;
		
		len=data[n+2] | ( data[n+3]<<8 );

		memcpy(mesg,&data[n+4],len);
		mesg[len]=0;

		sprintf(str,"%s >> %s ",hname,mesg);

		// Display message in list box
//		((CMyNetPhoneDlg *)pdlg)->DisplayMesg(str);

		return;
	}



}


/**
*       Send the control data to remote host
*
*
*/
void DSocket::SendControlMessage(int type,char *address)
{
char data[1000];
int n;

	// Prepare the data packet 
	
	// Type of control packet
	data[0]=type;				

	// Length of hostname
	n=strlen(localname);	
	data[1]=n;					
	
	// Name of the sender host
	memcpy(&data[2],localname,n);
	
	
	if(address==NULL)
	{
	
	SendTo(data,n+2,PORT_CONTROL,remoteaddress);
	
	}
	else
	{
	
	SendTo(data,n+2,PORT_CONTROL,address);
	
	}



}



/**
*       Send the audio data to remote host
*
*/
void DSocket::SendAudioData(unsigned char *data,int length)
{

SendTo(data,length,PORT_AUDIO,remoteaddress);
	
}



/**
*      Send the VIDEO data to remote host
*
*/
void DSocket::SendVideoData(unsigned char *data,int length)
{

// Better to attach video header....
// If dynamic format is supported...
SendTo(data,length,PORT_VIDEO,remoteaddress);
	
}


/**
*      Send the TEXT data to remote host
*
*/
void DSocket::SendTextData(unsigned char *data,short length)
{
unsigned char *packet=new unsigned char[length+500];
int n;	

	// Text message
	packet[0]=TYPE_TEXT;
	
	// Length of hostname
	n=strlen(localname);
	packet[1]=n;
	
	// Hostname
	memcpy(&packet[2],localname,n);

	// Data length
	packet[n+2]=(unsigned char) length;
	packet[n+3]=(unsigned char) (length>>8);

	// Data
	memcpy(&packet[n+4],data,length);

	
	SendTo(packet,n+4+length,PORT_TEXT,remoteaddress);
	
}


/**
*    Closes the socket created by the createsocket method
*
*/
void DSocket::CloseSocket()
{

	DSocket::Close();

}
