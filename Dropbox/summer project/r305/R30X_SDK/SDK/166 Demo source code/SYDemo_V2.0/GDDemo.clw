; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRNoteDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gddemo.h"
LastPage=0

ClassCount=12
Class1=CCom
Class2=CDlgFingerDB
Class3=CDLGUSERDEFINE
Class4=CGDDemoApp
Class5=CAboutDlg
Class6=CGDDemoDlg
Class7=CNoteDlg
Class8=CPwd
Class9=CRNoteDlg
Class10=CSortHeaderCtrl
Class11=CSortListCtrl
Class12=CUser

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDD_GDDEMO_DIALOG
Resource3=IDD_DLG_Note
Resource4=IDD_DLGCOM
Resource5=IDD_USERDEFINE
Resource6=IDD_DLGUSER
Resource7=IDD_DLG_RNote
Resource8=IDD_DLG_FingerDB
Resource9=IDR_ACCELERATOR1

[CLS:CCom]
Type=0
BaseClass=CDialog
HeaderFile=Com.h
ImplementationFile=Com.cpp

[CLS:CDlgFingerDB]
Type=0
BaseClass=CDialog
HeaderFile=DlgFingerDB.h
ImplementationFile=DlgFingerDB.cpp

[CLS:CDLGUSERDEFINE]
Type=0
BaseClass=CDialog
HeaderFile=DLGUSERDEFINE.h
ImplementationFile=DLGUSERDEFINE.cpp

[CLS:CGDDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=GDDemo.h
ImplementationFile=GDDemo.cpp
LastObject=CGDDemoApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GDDemoDlg.cpp
ImplementationFile=GDDemoDlg.cpp
LastObject=CAboutDlg

[CLS:CGDDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=GDDemoDlg.h
ImplementationFile=GDDemoDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMLANG

[CLS:CNoteDlg]
Type=0
BaseClass=CDialog
HeaderFile=NoteDlg.h
ImplementationFile=NoteDlg.cpp
LastObject=CNoteDlg
Filter=D
VirtualFilter=dWC

[CLS:CPwd]
Type=0
BaseClass=CDialog
HeaderFile=Pwd.h
ImplementationFile=Pwd.cpp

[CLS:CRNoteDlg]
Type=0
BaseClass=CDialog
HeaderFile=RNoteDlg.h
ImplementationFile=RNoteDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CRNoteDlg

[CLS:CSortHeaderCtrl]
Type=0
BaseClass=CHeaderCtrl
HeaderFile=SortHeaderCtrl.h
ImplementationFile=SortHeaderCtrl.cpp

[CLS:CSortListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=SortListCtrl.h
ImplementationFile=SortListCtrl.cpp

[CLS:CUser]
Type=0
BaseClass=CDialog
HeaderFile=User.h
ImplementationFile=User.cpp

[DLG:IDD_DLGCOM]
Type=1
Class=CCom
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COM,static,1342308352
Control4=IDC_COMBO1,combobox,1344339971
Control5=IDC_SETTING,button,1342177287

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
ControlCount=52
Control1=IDC_IMAGE,static,1350570510
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_INIT,button,1342177287
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_FINGERENROLL,button,1342177287
Control6=IDC_BUTTON4,button,1342242816
Control7=IDC_SEARCH,button,1342177287
Control8=IDC_BUTTON7,button,1342242816
Control9=IDC_BUTTON8,button,1342242816
Control10=IDC_DB,button,1342177287
Control11=IDC_BUTTON9,button,1342242816
Control12=IDC_BUTTON10,button,1342242816
Control13=IDC_INFO,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_LISTUSER,SysListView32,1350631693
Control16=IDC_BUTTON6,button,1342242816
Control17=IDC_IMAGEMANAGE,button,1342177287
Control18=IDC_TIP,static,1342308352
Control19=IDC_BUTTON2,button,1342242816
Control20=IDC_BUTTON5,button,1342242816
Control21=IDC_CHKDEV,button,1342242819
Control22=IDC_DEVSETTING,button,1342177287
Control23=IDC_BTN_SAVEBMP,button,1342242816
Control24=IDC_BTN_DLBMP,button,1342242816
Control25=IDC_COMBO_BAUD,combobox,1344339971
Control26=IDC_BTN_RANDOM,button,1342242816
Control27=IDC_SPECULE,button,1342177287
Control28=IDC_BTN_WNOTE,button,1342242816
Control29=IDC_BTN_RNOTE,button,1342242816
Control30=IDC_BTN_RNUM,button,1342242816
Control31=IDC_BANDRATE,static,1342308352
Control32=IDC_COMBO_PAKAGESIZE,combobox,1344339971
Control33=IDC_PACKAGESIZE,static,1342308352
Control34=IDC_COMBO_LEVEL,combobox,1344339971
Control35=IDC_SECURELEVEL,static,1342308352
Control36=IDC_DOWITHIMG,button,1342177287
Control37=IDC_BTN_BIN,button,1342242816
Control38=IDC_BTN_THIN,button,1342242816
Control39=IDC_BTN_TZ,button,1342242816
Control40=IDC_BTN_ORIBMP,button,1342242816
Control41=IDC_BTN_GETDB,button,1342242816
Control42=IDC_Preview,button,1342242819
Control43=IDC_IMGPREVIEW,static,1342308352
Control44=IDC_HDINFO,button,1342177287
Control45=IDC_Exit,button,1342242816
Control46=IDC_Path,edit,1350633600
Control47=IDC_BUTTON13,button,1342242816
Control48=IDC_OpenDev,static,1342308352
Control49=IDC_GetImgCon,button,1342242816
Control50=IDC_USERDEFINE,button,1073807360
Control51=IDC_STATIC,button,1342177287
Control52=IDC_COMLANG,combobox,1344340227

[DLG:IDD_DIALOG_Note]
Type=1
Class=CNoteDlg

[DLG:IDD_DLGPWD]
Type=1
Class=CPwd

[DLG:IDD_DIALOG_RNote]
Type=1
Class=CRNoteDlg

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

[DLG:IDD_DLG_Note]
Type=1
Class=CNoteDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_Note,edit,1352728580
Control4=IDC_PAGE,static,1342308352
Control5=IDC_EDIT_PAGE,edit,1350639744

[DLG:IDD_DLG_RNote]
Type=1
Class=CRNoteDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PAGE,static,1342308352
Control4=IDC_EDIT_PAGE,edit,1350639744
Control5=IDC_Note,edit,1352728580

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDC_Exit
CommandCount=1

