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
//    Name    : Mixer.cpp
//    Details : Functions for controlling volume..
//
//
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Volume Controler
// by Whoo(whoo@isWhoo.com)
// Oct.1 2001

//////////////////////////////////////////////////////////////////////




#if !defined(AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_)
#define AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMixer  
{
public:
	DWORD GetVolume();
	void SetVolume(DWORD dwVol);
	// Destination Kind;
	enum DestKind
	{
		Record,
		Play
	};
	CMixer(DWORD ComponentType, DestKind dkKind,int &min,int &max);

private:
	DWORD m_dwChannels;
	DWORD m_dwControlID;
	bool m_bOK;
};

#endif // !defined(AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_)
