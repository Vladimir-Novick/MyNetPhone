// MyNetPhoneServerDlg.h : header file
//

#if !defined(AFX_MYNETPHONESERVERDLG_H__519BF944_05A8_4E27_98F1_DE1650DA5C71__INCLUDED_)
#define AFX_MYNETPHONESERVERDLG_H__519BF944_05A8_4E27_98F1_DE1650DA5C71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"
#include "VideoCapture.h"
#include ".\..\RecordSound.h"

#include "DSocket.h"



#include "Encoder\libr263.h"
#include "Decoder\tmndec.h"

#include "DSocket.h"


/////////////////////////////////////////////////////////////////////////////
// CMyNetPhoneServerDlg dialog

class CMyNetPhoneServerDlg : public CDialog
{

public:

	VideoCapture *vidcap;
	BOOL isVideo , isAudio , isStarted , isCaptureStarted;
	BOOL isViewLocalVideo,isViewRemoteVideo;
	BOOL isAudioSend,isAudioReceive;
	BOOL isVideoSend,isVideoReceive;
	CParam cparams;

	PBITMAPINFO m_bmpinfo;
	BITMAPINFO compbmp;
	RecordSound *record;
	HDC m_hdc;


	
	DSocket dcontrol,daudio,dvideo,dtext;

	HDRAWDIB hdib;
	int local_wnd_x , local_wnd_y;
	int remote_wnd_x , remote_wnd_y;



	
	// Buffer for storing YUV data....
	unsigned int yuv[ QCIF_WIDTH*QCIF_HEIGHT  + (QCIF_WIDTH*QCIF_HEIGHT)/2 ];



// Construction
public:
	void SendVideo(BYTE *data,int size);
	CMyNetPhoneServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyNetPhoneServerDlg)
	enum { IDD = IDD_MYNETPHONESERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyNetPhoneServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyNetPhoneServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYNETPHONESERVERDLG_H__519BF944_05A8_4E27_98F1_DE1650DA5C71__INCLUDED_)
