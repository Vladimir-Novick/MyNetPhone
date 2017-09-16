// MyNetPhoneClientDlg.h : header file
//

#if !defined(AFX_MyNetPhoneClientDLG_H__B0986306_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
#define AFX_MyNetPhoneClientDLG_H__B0986306_5F44_11D6_8897_000B2B0F84B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "DSocket.h"
#include "ConnectDlg.h"


#include "PlaySound.h"
#include "Volume.h"
#include "Encoder/libr263.h"
#include "Decoder/tmndec.h"
#include<mmsystem.h>
#include<mmreg.h>
#include <Vfw.h>


class CMyNetPhoneClientDlg : public CDialog
{

	// Attributes
	public:
	

	BOOL isVideo , isAudio , isStarted , isCaptureStarted;
	BOOL isViewLocalVideo,isViewRemoteVideo;
	BOOL isAudioSend,isAudioReceive;
	BOOL isVideoSend,isVideoReceive;

	PBITMAPINFO m_bmpinfo;
	BITMAPINFO compbmp;

	PlaySound1 *play;
	HDC m_hdc;

	CMenu *menu;
	CButton *bsend;
	CListBox *list;
	CStdioFile log;

	HICON m_hIcon;
	HWND hwnd;

	ConnectDlg *connectdlg;	
	
	DSocket dcontrol,daudio,dvideo,dtext;

	HDRAWDIB hdib;
	int local_wnd_x , local_wnd_y;
	int remote_wnd_x , remote_wnd_y;


	// Compression parameters....
	CParam cparams;
	
	// Buffer for storing YUV data....
	unsigned int yuv[ QCIF_WIDTH*QCIF_HEIGHT  + (QCIF_WIDTH*QCIF_HEIGHT)/2 ];




	
// Construction
public:
	CMyNetPhoneClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyNetPhoneClientDlg)
	enum { IDD = IDD_MyNetPhoneClient_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyNetPhoneClientDlg)
public:	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


public:
		void OnConnect();

	virtual void OnCancel();
	


	void OnDisconnect();
	

	void OnViewLocal();
	void OnViewRemote();
	
	

	void OnVolumeControl();
	void OnAudioSend();
	void OnAudioReceive();
	


	void OnVideoSend();
	void OnVideoReceive();
	


	void OnAbout();
		
	void StartConference();
	
	void DestroyConference();

	void OnSendMesg();

	void DisplayMesg(char *str);

	void SendVideo(BYTE *data,int size);

	void DisplayRemoteFrame(unsigned char *data,int size);
	
	
	
	// Implementation




	// Generated message map functions
	//{{AFX_MSG(CMyNetPhoneClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyNetPhoneClientDLG_H__B0986306_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
