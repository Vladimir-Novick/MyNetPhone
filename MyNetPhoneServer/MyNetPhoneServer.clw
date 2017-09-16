; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=RequestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyNetPhoneServer.h"

ClassCount=5
Class1=CMyNetPhoneServerApp
Class2=CMyNetPhoneServerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG2 (Neutral)
Class5=RequestDlg
Resource4=IDD_MYNETPHONESERVER_DIALOG

[CLS:CMyNetPhoneServerApp]
Type=0
HeaderFile=MyNetPhoneServer.h
ImplementationFile=MyNetPhoneServer.cpp
Filter=N

[CLS:CMyNetPhoneServerDlg]
Type=0
HeaderFile=MyNetPhoneServerDlg.h
ImplementationFile=MyNetPhoneServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyNetPhoneServerDlg.h
ImplementationFile=MyNetPhoneServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MYNETPHONESERVER_DIALOG]
Type=1
Class=CMyNetPhoneServerDlg
ControlCount=2
Control1=IDC_LOCALVIDEO,static,1350565892
Control2=IDC_LOCALBORDER,button,1342177287

[CLS:RequestDlg]
Type=0
HeaderFile=RequestDlg.h
ImplementationFile=RequestDlg.cpp
BaseClass=CDialog

[DLG:IDD_DIALOG2 (Neutral)]
Type=1
Class=RequestDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDREJECT,button,1342242816
Control3=IDC_MESG,static,1342308352

