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
//    Name    : Volume.h
//    Details : Dialog class for Volume Control
//
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOLUME_H__0423C7A1_4B57_11D6_8886_B01554C10000__INCLUDED_)
#define AFX_VOLUME_H__0423C7A1_4B57_11D6_8886_B01554C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<afxcmn.h>
#include"Mixer.h"

class Volume : public CDialog  
{
public:
	CMixer *mixrec,*mixplay;
	CSliderCtrl *srec,*splay;
	
	Volume(int n);
	BOOL OnInitDialog();
	void OnHScroll(UINT code,UINT pos,CScrollBar *scroll);
	HBRUSH OnCtlColor(CDC *pdc,CWnd *pwnd,UINT ctrl);
	void OnPaint();


	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_VOLUME_H__0423C7A1_4B57_11D6_8886_B01554C10000__INCLUDED_)
