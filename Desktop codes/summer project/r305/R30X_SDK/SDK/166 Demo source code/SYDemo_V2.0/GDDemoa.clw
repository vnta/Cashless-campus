; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPwd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GDDemo.h"

ClassCount=11
Class1=CGDDemoApp
Class2=CGDDemoDlg
Class3=CAboutDlg

ResourceCount=11
Resource1=IDD_DLG_RNote
Resource2=IDR_MAINFRAME
Resource3=IDD_DLG_Note
Class4=CCom
Resource4=IDD_DLGUSER
Class5=CPwd
Class6=CUser
Resource5=IDD_DIALOGBAR (English (U.S.))
Class7=CNoteDlg
Resource6=IDD_DLG_FingerDB
Class8=CRNoteDlg
Class9=CImageDemoDlg
Resource7=IDD_GDDEMO_DIALOG
Class10=CDlgFingerDB
Resource8=IDD_DLGCOM
Resource9=IDD_ABOUTBOX
Resource10=IDD_USERDEFINE
Class11=CDLGUSERDEFINE
Resource11=IDR_ACCELERATOR1

[CLS:CGDDemoApp]
Type=0
HeaderFile=GDDemo.h
ImplementationFile=GDDemo.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CGDDemoApp

[CLS:CGDDemoDlg]
Type=0
HeaderFile=GDDemoDlg.h
ImplementationFile=GDDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CGDDemoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=GDDemoDlg.h
ImplementationFile=GDDemoDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342181383

[DLG:IDD_GDDEMO_DIALOG]
Type=1
Class=CGDDemoDlg
ControlCount=51
Control1=IDC_IMAGE,static,1350570510
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON4,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_BUTTON7,button,1342242816
Control9=IDC_BUTTON8,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_BUTTON9,button,1342242816
Control12=IDC_BUTTON10,button,1342242816
Control13=IDC_INFO,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_LISTUSER,SysListView32,1350631693
Control16=IDC_BUTTON6,button,1342242816
Control17=IDC_STATIC,button,1342177287
Control18=IDC_TIP,static,1342308352
Control19=IDC_BUTTON2,button,1342242816
Control20=IDC_BUTTON5,button,1342242816
Control21=IDC_CHKDEV,button,1342242819
Control22=IDC_STATIC,button,1342177287
Control23=IDC_BTN_SAVEBMP,button,1342242816
Control24=IDC_BTN_DLBMP,button,1342242816
Control25=IDC_COMBO_BAUD,combobox,1344339971
Control26=IDC_BTN_RANDOM,button,1342242816
Control27=IDC_STATIC,button,1342177287
Control28=IDC_BTN_WNOTE,button,1342242816
Control29=IDC_BTN_RNOTE,button,1342242816
Control30=IDC_BTN_RNUM,button,1342242816
Control31=IDC_STATIC,static,1342308352
Control32=IDC_COMBO_PAKAGESIZE,combobox,1344339971
Control33=IDC_STATIC,static,1342308352
Control34=IDC_COMBO_LEVEL,combobox,1344339971
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,button,1342177287
Control37=IDC_BTN_BIN,button,1342242816
Control38=IDC_BTN_THIN,button,1342242816
Control39=IDC_BTN_TZ,button,1342242816
Control40=IDC_BTN_ORIBMP,button,1342242816
Control41=IDC_BTN_GETDB,button,1342242816
Control42=IDC_Preview,button,1342242819
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,button,1342177287
Control45=IDC_Exit,button,1342242816
Control46=IDC_Path,edit,1350633600
Control47=IDC_BUTTON13,button,1342242816
Control48=IDC_OpenDev,static,1342308352
Control49=IDC_GetImgCon,button,1342242816
Control50=IDC_USERDEFINE,button,1073807360
Control51=IDC_DBINFO,static,1342308352

[CLS:CCom]
Type=0
HeaderFile=Com.h
ImplementationFile=Com.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO3

[CLS:CPwd]
Type=0
HeaderFile=Pwd.h
ImplementationFile=Pwd.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPwd

[CLS:CUser]
Type=0
HeaderFile=User.h
ImplementationFile=User.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUser

[CLS:CNoteDlg]
Type=0
HeaderFile=NoteDlg.h
ImplementationFile=NoteDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNoteDlg

[CLS:CRNoteDlg]
Type=0
HeaderFile=RNoteDlg.h
ImplementationFile=RNoteDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CRNoteDlg
VirtualFilter=dWC

[CLS:CImageDemoDlg]
Type=0
HeaderFile=ImageDemoDlg.h
ImplementationFile=ImageDemoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DLG_FingerDB]
Type=1
Class=CDlgFingerDB
ControlCount=17
Control1=IDCANCEL,button,1342242816
Control2=IDC_IMAGE,static,1350570510
Control3=IDC_FINGERNUM,static,1342308352
Control4=IDC_EDIT_NUMPFIN,edit,1350631552
Control5=IDC_FINGERPATH,static,1342308352
Control6=IDC_EDIT_PATH,edit,1350631552
Control7=IDC_BTN_GETPATH,button,1342242816
Control8=IDC_GETIMAGCON,button,1342177287
Control9=IDC_EDIT_RUN_NUM,edit,1350631552
Control10=IDC_BTN_RUN,button,1342242816
Control11=IDC_IMAGENUM1,static,1342308352
Control12=IDC_GETONE,button,1342177287
Control13=IDC_EDIT_SIG_NUM,edit,1350631552
Control14=IDC_BTN_SIG,button,1342242816
Control15=IDC_IMAGENUM2,static,1342308352
Control16=IDC_BTN_CANCEL_RUN,button,1342242816
Control17=IDC_BTN_CANCEL_SIG,button,1342242816

[DLG:IDD_DLG_Note]
Type=1
Class=CNoteDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_Note,edit,1352728580
Control4=IDC_PAGE,static,1342308352
Control5=IDC_EDIT_PAGE,edit,1350639744

[DLG:IDD_DLGUSER]
Type=1
Class=CUser
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ADDR,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_USERNAME,static,1073872896
Control6=IDC_EDIT2,edit,1082196096
Control7=IDC_SETTING,button,1342177287

[DLG:IDD_DLGCOM]
Type=1
Class=CCom
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344339971
Control5=IDC_STATIC,button,1342177287

[DLG:IDD_DLG_RNote]
Type=1
Class=CRNoteDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_PAGE,edit,1350639744
Control5=IDC_Note,edit,1352728580

[CLS:CDlgFingerDB]
Type=0
HeaderFile=DlgFingerDB.h
ImplementationFile=DlgFingerDB.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgFingerDB
VirtualFilter=dWC

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDC_Exit
CommandCount=1

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_USERDEFINE]
Type=1
Class=CDLGUSERDEFINE
ControlCount=7
Control1=IDC_COMBO1,combobox,1344340227
Control2=IDC_COMBO2,combobox,1344340227
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CDLGUSERDEFINE]
Type=0
HeaderFile=DLGUSERDEFINE.h
ImplementationFile=DLGUSERDEFINE.cpp
BaseClass=CDialog
Filter=D
LastObject=CDLGUSERDEFINE
VirtualFilter=dWC

