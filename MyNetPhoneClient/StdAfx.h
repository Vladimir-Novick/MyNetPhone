// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B0986308_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
#define AFX_STDAFX_H__B0986308_5F44_11D6_8897_000B2B0F84B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions


#define IMAGE_SIZE  76032
#define FILE_SIZE   76086


#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144

#define IMAGE_WIDTH       QCIF_WIDTH
#define IMAGE_HEIGHT      QCIF_HEIGHT

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B0986308_5F44_11D6_8897_000B2B0F84B6__INCLUDED_)
