// GDDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "GDDemoDlg.h"
#include "Com.h"

#include "DBManager.h"
#include "protocol.h"
#include "User.h"
#include "Shlwapi.h"
#include "math.h"

#include "notedlg.h"
#include "rnotedlg.h"
#include "DlgFingerDB.h"

#include "DLGUSERDEFINE.h"

#include "FingerFileTabe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define   IMG_FILE  "c:\\Finger.bmp"
#define	  IMAGE_SIZE (256*288)

CGDDemoDlg* pMyDlg;

LANGID glangid;



bool bSelect;
int iCurSelID;
int nSelectItem;
int mCap=0;
bool gbCancel=false;
int nDevAddr=0xffffffff;
static char BASED_CODE szFilter[] = "Bmp File (*.bmp)|*.bmp|";

bool gbOpen = false;
unsigned int g_SaveMode = 0;  //0 �Ǵ���λ�����ϴ�ͼƬ���棬 1 ��ֱ�ӱ��浱ǰ�Ļ�������ͼƬ,2 ������ȡͼ�󱣴� 
unsigned char gImgData[IMAGE_SIZE]={0};

CCriticalSection CriticalSection;

TCHAR szUserLogoPath[255] = {0};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGDDemoDlg dialog

CGDDemoDlg::CGDDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGDDemoDlg::IDD, pParent)
{
	glangid = GetSystemDefaultLangID();
	if(glangid==0x0804)
	{
		m_sTip = _T("��ӭʹ��Syno ���Գ������ȴ��豸!");
		m_Lang = _T("Chinese");
	}
	else
	{
        m_sTip = _T("Welcome,Please Open Device first!");
		m_Lang = _T("English");
	}
	//{{AFX_DATA_INIT(CGDDemoDlg)	
	m_bUpImg = FALSE;
	m_ComPakageSize = -1;
	m_ComBaud = -1;
	m_ComLevel = -1;
	m_bPreImg = FALSE;
	m_Addr = 0;
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

int strHexToInt(CString strSource,UINT *nVal)
{	
	int nTemp=0;
	
	CString strTemp;
	strTemp=strSource;
	for(char cc='G',dd='g';   cc<='Z',dd<='z';  cc++,dd++)    //�ж�������ַ����Ƿ�Ϸ�
	{
		if(strTemp.Find(cc,0) !=-1  ||  strTemp.Find(dd,0) !=-1)
		{
			if(glangid==0x0804)
				::MessageBox(NULL,"��������ȷ��16�����ַ���!","�������",MB_ICONEXCLAMATION);
			else
				::MessageBox(NULL,"please input hex format data!","Input error",MB_ICONEXCLAMATION);
			return -1;
		}
	}
	
	for(int i = 0;  i<(int)::strlen(strSource);  i++)
	{
		int nDecNum;
		switch(strSource[i])
		{
		case 'a':
		case 'A':	nDecNum = 10;	break;
		case 'b':
		case 'B':	nDecNum = 11;	break;
		case 'c':
		case 'C':   nDecNum = 12;   break;
		case 'd':
		case 'D':   nDecNum = 13;   break;
		case 'e':
		case 'E':   nDecNum = 14;   break;
		case 'f':
		case 'F':   nDecNum = 15;   break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':    nDecNum = strSource[i] - '0';     break;
		default:     return -1;			
        }
		nTemp += nDecNum * (int)::pow(16,::strlen(strSource)-i -1);
	}
	*nVal=nTemp;
	return 0;
}
void CGDDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGDDemoDlg)
	DDX_Control(pDX, IDC_TIP, m_Tip);
	DDX_Control(pDX, IDC_INFO, m_TipInfo);
	DDX_Control(pDX, IDC_LISTUSER, m_ListUser);
	DDX_Text(pDX, IDC_TIP, m_sTip);
	DDX_Check(pDX, IDC_CHKDEV, m_bUpImg);
	DDX_CBIndex(pDX, IDC_COMBO_PAKAGESIZE, m_ComPakageSize);
	DDX_CBIndex(pDX, IDC_COMBO_BAUD, m_ComBaud);
	DDX_CBIndex(pDX, IDC_COMBO_LEVEL, m_ComLevel);
	DDX_Check(pDX, IDC_Preview, m_bPreImg);
	DDX_CBString(pDX, IDC_COMLANG, m_Lang);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGDDemoDlg, CDialog)
//{{AFX_MSG_MAP(CGDDemoDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON3, OnGenImg)
ON_BN_CLICKED(IDC_BUTTON1, OnOpenCom)
ON_BN_CLICKED(IDC_BUTTON4, OnEnroll)
ON_BN_CLICKED(IDC_BUTTON7, OnVerify)
ON_BN_CLICKED(IDC_BUTTON8, OnSearch)
ON_BN_CLICKED(IDC_BUTTON10, OnEmpty)
ON_BN_CLICKED(IDC_BUTTON9, OnDelete)
ON_NOTIFY(NM_CLICK, IDC_LISTUSER, OnClickListuser)
ON_BN_CLICKED(IDC_BUTTON6, OnCancelOpt)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON2, OnEnrollCon)
ON_BN_CLICKED(IDC_BUTTON5, OnSearchCon)
ON_CBN_SELCHANGE(IDC_COMBO_BAUD, OnSelchangeComboBaud)
ON_CBN_SELCHANGE(IDC_COMBO_PAKAGESIZE, OnSelchangeComboPakagesize)
ON_CBN_SELCHANGE(IDC_COMBO_LEVEL, OnSelchangeComboLevel)
ON_CBN_SETFOCUS(IDC_COMBO_BAUD, OnSetfocusComboBaud)
ON_CBN_SETFOCUS(IDC_COMBO_PAKAGESIZE, OnSetfocusComboPakagesize)
ON_CBN_SETFOCUS(IDC_COMBO_LEVEL, OnSetfocusComboLevel)
ON_BN_CLICKED(IDC_BTN_SAVEBMP, OnBtnSavebmp)
ON_BN_CLICKED(IDC_BTN_DLBMP, OnBtnDlbmp)
ON_BN_CLICKED(IDC_BTN_WNOTE, OnBtnWnote)
ON_BN_CLICKED(IDC_BTN_RNOTE, OnBtnRnote)
ON_BN_CLICKED(IDC_BTN_RANDOM, OnBtnRandom)
ON_BN_CLICKED(IDC_BTN_RNUM, OnBtnRnum)
ON_BN_CLICKED(IDC_BTN_BIN, OnBtnBin)
ON_BN_CLICKED(IDC_BTN_THIN, OnBtnThin)
ON_BN_CLICKED(IDC_BTN_TZ, OnBtnTz)
ON_BN_CLICKED(IDC_BTN_ORIBMP, OnBtnOribmp)
ON_BN_CLICKED(IDC_BTN_GETDB, OnBtnGetdb)
ON_BN_CLICKED(IDC_BUTTON12, OnExit)
ON_BN_CLICKED(IDC_BUTTON13, OnPath)
ON_BN_CLICKED(IDC_BUTTON14, OnGetImgCon)
ON_BN_CLICKED(IDC_USERDEFINE, OnUserdefine)
ON_WM_SHOWWINDOW()
ON_WM_CLOSE()
	ON_CBN_EDITCHANGE(IDC_COMLANG, OnEditchangeComlang)
ON_BN_CLICKED(IDC_Exit, OnExit)
ON_BN_CLICKED(IDC_GetImgCon, OnGetImgCon)
	ON_CBN_SELCHANGE(IDC_COMLANG, OnSelchangeComlang)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CGDDemoDlg::ShowPara()
{
	int ret;
	unsigned char iParTable[512];
	int nLevel,nPackSize,nBaud;	
	int i;
	
	memset(iParTable, 0, 512*sizeof(unsigned char));
	Sleep(200);
	
	ret = PSReadInfPage(nDevAddr,iParTable);
	if(ret != PS_OK)
		return;
	CString strTemp,strPara;
	mCap=(iParTable[4]<<8)+iParTable[5];
	if(glangid==0x0804)
	{
		
		strTemp.Format("ָ�ƿ��С��%d\r\n",mCap);
		
		
		strPara = strTemp;
		
		nLevel = (iParTable[6]<<8)+iParTable[7];
		strTemp.Format("��ȫ�ȼ���%d\r\n",nLevel);
		strPara += strTemp;
		
		strPara += "�豸��ַ��0x";
		for(i=8; i<8+4; i++)
		{
			strTemp.Format("%02x",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
		
		if(!bUsbComm)
		{
			nPackSize = (iParTable[12]<<8)+iParTable[13];
			strTemp.Format("���ݰ���С��%d bytes\r\n",(int)pow(2,nPackSize)*32);
			strPara += strTemp;
			
			nBaud = (iParTable[14]<<8)+iParTable[15];
			strTemp.Format("�����ʣ�%d bps\r\n",nBaud*9600);
			strPara += strTemp;
		}
	
			
		strPara += "��Ʒ�ͺţ�";
		for(i=28; i<28+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
		

		strPara += "����汾:";
		for(i=36; i<36+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
	
		strPara += "�������ƣ�";
		for(i=44; i<44+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
			
		
		strPara += "���������ƣ�";
		for(i=52; i<52+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
	}
	else
	{
		strTemp.Format("Finger Database: %d\r\n",mCap);
		
		
		strPara = strTemp;
		
		nLevel = (iParTable[6]<<8)+iParTable[7];
		strTemp.Format("Secure Level: %d\r\n",nLevel);
		strPara += strTemp;
		
		strPara += "Address: 0x";
		for(i=8; i<8+4; i++)
		{
			strTemp.Format("%02x",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
		
		if(!bUsbComm)
		{
			nPackSize = (iParTable[12]<<8)+iParTable[13];
			strTemp.Format("Package Size: %d bytes\r\n",(int)pow(2,nPackSize)*32);
			strPara += strTemp;
			
			nBaud = (iParTable[14]<<8)+iParTable[15];
			strTemp.Format("Bandrate: %d bps\r\n",nBaud*9600);
			strPara += strTemp;
		}
	
		strPara += "Product Type:";
		for(i=28; i<28+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
		

		strPara += "Version:";
		for(i=36; i<36+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
	
		strPara += "Manufacture:";
		for(i=44; i<44+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		strPara += "\r\n";
		
		
		strPara += "Sensor:";
		for(i=52; i<52+8; i++)
		{
			strTemp.Format("%c",iParTable[i]);
			strPara += strTemp;
			
		}
		
	}
	strPara += "\r\n";
	
	m_sTip=strPara;	//�豸������Ϣ
	
	//�����б���ʾ������
	if(nBaud == 12)
		m_ComBaud = 4;
	else
		m_ComBaud = nBaud/2;
	m_ComPakageSize = nPackSize-1;	//�����б���ʾ���ݰ���С
	m_ComLevel = (iParTable[6]<<8)+iParTable[7]-1;	//�����б���ʾ��ȫ�ȼ�
	
	UpdateData(FALSE);
}

// CGDDemoDlg message handlers
BOOL CGDDemoDlg::AutoOpen()
{
	CString sPassword;	
	unsigned char iPwd[4]={0};	
	int iCom;
	CCom pComDlg;	
	PSCloseDevice();
	bUsbComm = TRUE;
    if(PSOpenDevice(DEVICE_USB,0,0))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) 	goto OPENOK;		
	}
	
	bUsbComm = FALSE;
	//��ʼ������	
	if(pComDlg.DoModal()!=IDOK)
		return 0; 	
	iCom = pComDlg.nCom;
	
	if(PSOpenDevice(DEVICE_COM,iCom,57600/9600))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) goto OPENOK;		
	}
	PSCloseDevice();
	
	if(PSOpenDevice(DEVICE_COM,iCom,115200/9600))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) goto OPENOK;		
	}
	PSCloseDevice();
	
	if(PSOpenDevice(DEVICE_COM,iCom,38400/9600))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) goto OPENOK;		
	}
	PSCloseDevice();
	
	if(PSOpenDevice(DEVICE_COM,iCom,19200/9600))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) goto OPENOK;		
	}
	PSCloseDevice();
	
	if(PSOpenDevice(DEVICE_COM,iCom,9600/9600))
	{ 
		if(PSVfyPwd(nDevAddr,iPwd)==PS_OK) goto OPENOK;		
	}
	if(glangid==0x0804)
		AfxMessageBox("���豸ʧ�ܣ�����������豸��ַ�Ƿ���ȷ");
	else
		AfxMessageBox("Open Device fail,please check the password and the device address!");
	return FALSE;
	
OPENOK:
    if (bUsbComm) 
	{
		CStatic *ps = (CStatic *)GetDlgItem(IDC_OpenDev);
		if(glangid==0x0804)
			ps->SetWindowText("����ʹ��USBͨ��");
		else
			ps->SetWindowText("Communicate with USB");
		m_bUpImg = TRUE;
		m_bPreImg = TRUE ;
	}
	else
	{
		CStatic *ps = (CStatic *)GetDlgItem(IDC_OpenDev);
		CString stmp;
		stmp.Format("%d",iCom);
		if(glangid==0x0804)
			ps->SetWindowText("����ʹ�ô���"+stmp+"ͨ��");
		else
			ps->SetWindowText("Communicate with COM"+stmp);
		m_bUpImg = FALSE;
		m_bPreImg = FALSE ;
	}
	gbOpen = true;
		if(szHard[0]=='1')
		{
	ShowPara();
		}
	EnableBtn(TRUE);
	if(glangid==0x0804)
		ShowInfo("���豸�ɹ�");
	else
		ShowInfo("Open Device Success!");
	
	return TRUE;
	
}
BOOL CGDDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	pMyDlg=this;
	EnableBtn(FALSE);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	m_HeadIcon.Create(16,16,TRUE,2,2);
	m_HeadIcon.Add(AfxGetApp()->LoadIcon(IDI_HEADICON));
	m_ListUser.SetImageList(&m_HeadIcon,LVSIL_SMALL);
	
	Update();
    
	
	m_color=RGB(0,0,255);     //�˴����ÿؼ������ֳ�ʼ��ɫΪ��ɫ��
	memset(gImgData,0,IMAGE_SIZE);
	
	LoadUserDefine();
	gbCancel = true;
	
	
	return 1;
	
}

void CGDDemoDlg::EnableBtn(BOOL bEnable)
{
	((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON4))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON5))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON6))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON7))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON8))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON9))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON10))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_GetImgCon))->EnableWindow(bEnable);
	
    if (bUsbComm)
    {
		((CButton*)GetDlgItem(IDC_COMBO_BAUD))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_COMBO_PAKAGESIZE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_COMBO_LEVEL))->EnableWindow(FALSE);
    }
	else
	{
		((CButton*)GetDlgItem(IDC_COMBO_BAUD))->EnableWindow(bEnable);
		((CButton*)GetDlgItem(IDC_COMBO_PAKAGESIZE))->EnableWindow(bEnable);
		((CButton*)GetDlgItem(IDC_COMBO_LEVEL))->EnableWindow(bEnable);
	}
    
	((CButton*)GetDlgItem(IDC_BTN_DLBMP))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_SAVEBMP))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_WNOTE))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_RNOTE))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_RANDOM))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_RNUM))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_BIN))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_THIN))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_TZ))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_ORIBMP))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BTN_GETDB))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_CHKDEV))->EnableWindow(bEnable);	
    ((CButton*)GetDlgItem(IDC_Preview))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_USERDEFINE))->EnableWindow(bEnable);
}


void CGDDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGDDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	/*
	if (gbCancel)
	{
	ShowDefaltImg();
	}
	else
	{
	   if ((!gbOpen) && (!gbCancel))
	   ShowDefaltImg();
	   else
	   ShowImage();
	   }
		*/
		if (gbCancel)
			ShowDefaltImg();
		else
			ShowImage();
		CDialog::OnPaint();
	}
	
}

void CGDDemoDlg::ShowInfo(CString strInfo,int iFlag)
{
	if (iFlag>0)
	{
		ShowInfomation(strInfo,RGB(255,0,0));
		return;
	}
	ShowInfomation(strInfo,RGB(0,0,255));
	//   UpdateData(FALSE);	
	//	this->GetDlgItem(IDC_INFO)->SetWindowText(strInfo);
}

void CGDDemoDlg::ShowCmdInfo(int ret)
{
	if(ret!=PS_OK)
	{
		ShowInfo( PSErr2Str(ret) );		
		return ;
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGDDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT GenImg(LPVOID pParam)
{ 
	int ret,i=0;
	int ImgLen;
	unsigned char ImgData[IMAGE_SIZE]; 
	CString strinfo;
	pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	pMyDlg->ShowDefaltImg();
	
	if(glangid==0x0804)
		pMyDlg->ShowInfo("�뽫��ָƽ���ڴ�������...");
	else
		pMyDlg->ShowInfo("Please put your finger to sensor!");
	
	gbCancel=false;
    clock_t start,finish;	 
	start = clock();
	ret = PSGetImage(nDevAddr);  //��ȡͼ��  
	finish = clock();
	
	while(ret==PS_NO_FINGER)
	{   
		start = clock();
		finish=start;
		ret=PSGetImage(nDevAddr);
		finish = clock();
		if(gbCancel)
		{
			pMyDlg->EnableBtn(true);
			return 1;
		}
	}
	
	if(ret!=PS_OK)
	{   
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		return 1;
	}
	if(glangid==0x0804)	
		pMyDlg->ShowInfo("ͼ�������ϴ�...");
	else
		pMyDlg->ShowInfo("Finger Data transfering...");
	
	ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		return 1;
	}
	
	ret= PSImgData2BMP(ImgData,IMG_FILE);
	
    if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		
		return 1;
	}
	
	pMyDlg->ShowImage();
	if(glangid==0x0804)
		strinfo.Format("��ȡͼ���ʱ%d����,ͼ��¼��ɹ�!",finish-start);
	else
		strinfo.Format("Success! Get image used %d ms",finish-start);
	pMyDlg->ShowInfo(strinfo);	
	
	pMyDlg->EnableBtn(true);
	
	return 0;
}


void CGDDemoDlg::OnGenImg() 
{   
	g_SaveMode = 0;
	AfxBeginThread( GenImg,NULL);//��ʼִ���߳�
	
}



void CGDDemoDlg::OnOpenCom() 
{
	ShowDefaltImg();
	AutoOpen();
	GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(false);
} 

UINT Enroll(LPVOID pParam)
{ 
	int  ret=0;
	
	unsigned char ImgData[IMAGE_SIZE];
	int ImgLen;
	
    CString Sql;
	pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	BOOL bReplace;
	
	
    if (pMyDlg->m_fingertable->IsExisitId(pMyDlg->m_Addr))
    {
		CString str;
		if(glangid==0x0804)
			str="�õ�ַ�Ѿ������û����Ƿ񸲸�!";
		else
			str="The address has user! do you want to overwrite!";
		if ( AfxMessageBox(str, MB_YESNO) == IDYES )
			bReplace = TRUE;
		else
		{
			pMyDlg->EnableBtn(true);			
			return 1;
		}
    }
	else 	 
	{
		bReplace = FALSE;
	}
	
	
	int iFingerNum = 0;
	int iBuffer;
	
	while (iFingerNum<2)
	{
		//pMyDlg->ShowDefaltImg(); //kzf 
		
		//�ڶ��ΰ���ָʱ����ʾ�û�����ָ��
		if(glangid==0x0804)
			pMyDlg->ShowInfo( "�뽫��ָƽ���ڴ�������..." );
		else
			pMyDlg->ShowInfo("Please put your finger to sensor!");
		
		gbCancel=false;
		ret = PSGetImage(nDevAddr);  //��ȡͼ��  
		
		while(ret==PS_NO_FINGER)
		{
			ret=PSGetImage(nDevAddr);
			if(gbCancel)
			{
				pMyDlg->EnableBtn(true);
				
				return 1;
			}
		}		
		if ( ret!=PS_OK )
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			
			return 1;
		}
		
		//��һ��ִ��ʱ��ʾ�û��ÿ���ָ��
		if(glangid==0x0804)
			pMyDlg->ShowInfo( "���ÿ���ָ");	
		else
			pMyDlg->ShowInfo("Please take off finger!");
		Sleep(300);		
		
		if(pMyDlg->m_bUpImg)
		{
			if(glangid==0x0804)
				pMyDlg->ShowInfo("ͼ��¼��ɹ��������ϴ�...");			
			else
				pMyDlg->ShowInfo("Success,Image transfering...");
			ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);
			}
			
			ret= PSImgData2BMP(ImgData,IMG_FILE);
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);
				return 1;
			}
			pMyDlg->ShowImage();
		}
		
		iBuffer = CHAR_BUFFER_A;
		if (iFingerNum == 1)
			iBuffer = CHAR_BUFFER_B;
		
		ret = PSGenChar(nDevAddr,iBuffer);  //����ģ��
		
		if (ret != PS_OK)
		{
			CString strTmp;
			if(glangid==0x0804)
				strTmp.Format("%s\n%s", PSErr2Str(ret) ,"\n������¼��");
			else
				strTmp.Format("%s\n%s", PSErr2Str(ret) ,"\nPlease reenroll!");
			pMyDlg->ShowInfo(strTmp);
			Sleep(1000);
			continue;			 
		}
		
        iFingerNum++;      
		
		Sleep(500);
		
	}
	
	ret=PSRegModule(nDevAddr);  //�ϲ�����
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		return 1;
	}
	
	ret=PSStoreChar(nDevAddr,iBuffer, pMyDlg->m_Addr);    //���ģ��
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		return FALSE;
	}
	/*	database
	if (bReplace)
	Sql.Format("UPDATE UserInfo SET Address = %d , UserName = '%s'  WHERE Address = %d",pMyDlg->m_Addr,pMyDlg->strUser,pMyDlg->m_Addr);
	else
	Sql.Format("INSERT  INTO UserInfo(Address,UserName) VALUES(%d,'%s')" ,pMyDlg->m_Addr,pMyDlg->strUser);
	
	  if(G_db.DBExecuteSQL(Sql))
	  AfxMessageBox("ע�ᵽ���ݿ��ʧ�ܣ�");
	  
	*/
    
	
	CString tmp;
	if (bReplace)
	{		
		//pMyDlg->Update();
	}
	else
	{
		BOOL bRet;
		bRet = pMyDlg->m_fingertable->AppendTempelet(pMyDlg->m_Addr,pMyDlg->strUser);
		if (!bRet)
		{
			if(glangid==0x0804)
				AfxMessageBox("���ʧ��,������");
			else
				AfxMessageBox("Fail to enroll! Please retry!");
			return 1;
		}
		//	int index = pMyDlg->m_ListUser.GetItemCount();
		//	pMyDlg->m_ListUser.InsertItem(index, tmp);
		tmp.Format("%d",pMyDlg->m_Addr);
		pMyDlg->m_ListUser.AddItem(tmp);
		
		//	pMyDlg->m_ListUser.SetItemText(index,0,tmp);
		//	pMyDlg->m_ListUser.SetItemText(index,1,pMyDlg->strUser);		
	}	
	
	if(glangid==0x0804)
		pMyDlg->ShowInfo("�û���ӳɹ�!");
	else
		pMyDlg->ShowInfo("Success to enroll!");
	
	pMyDlg->m_Addr++;
	
    pMyDlg->EnableBtn(true);
	
	return 1;
}

void CGDDemoDlg::OnEnroll() 
{    
	
	CUser DlgUser;
	UpdateData(TRUE);
	DlgUser.m_Addr=m_Addr;
	DlgUser.m_UserInfo.Format("%d",m_Addr);
	DlgUser.bConEnroll=false;
    this->ShowDefaltImg();
	if(DlgUser.DoModal()==IDOK)
	{		
		m_Addr=DlgUser.m_Addr;
		strUser=DlgUser.m_UserInfo;
		AfxBeginThread( Enroll,NULL);//��ʼִ���߳�
	}
	
}


void CGDDemoDlg::Update()
{
/*
int nColumnCount;
m_ListUser.DeleteAllItems();//����б���е�����
nColumnCount=m_ListUser.GetHeaderCtrl()->GetItemCount();
/////�õ��б��������
for (int i=0;i < nColumnCount;i++)///����б�����
m_ListUser.DeleteColumn(0);
/////����б�����
m_ListUser.InsertColumn(1,"�洢��ַ",LVCFMT_LEFT,80);

  CString Sql,Tmp;
  
	map<int,CString>tmp;
    map<int,CString>::iterator tmp_iter;
	m_fingertable = new CFingerFileTable;
	tmp = m_fingertable->GetAllContent();
	if (tmp.size()==0) return;
    
	  for (tmp_iter=tmp.begin();tmp_iter!=tmp.end();tmp_iter++)
	  {
	  Tmp.Format("%d",tmp_iter->first);
	  m_ListUser.InsertItem(0, Tmp);	
	  
		}
	*/
	int nColumnCount;
    m_ListUser.DeleteAllItems();//����б���е�����
    nColumnCount=m_ListUser.GetHeaderCtrl()->GetItemCount();
	/////�õ��б��������
    for (int i=0;i < nColumnCount;i++)///����б�����
		m_ListUser.DeleteColumn(0);
	
	(void)m_ListUser.SetExtendedStyle( LVS_EX_FULLROWSELECT ); 
	if(glangid==0x0804)
		
		m_ListUser.InsertColumn(1,"Address",LVCFMT_LEFT,170);
	else
		m_ListUser.InsertColumn(1,"Address",LVCFMT_LEFT,170);
	
	
    CString Sql,Tmp;
	
	map<int,CString>tmp;
    map<int,CString>::iterator tmp_iter;
	m_fingertable = new CFingerFileTable;
	tmp = m_fingertable->GetAllContent();
	if (tmp.size()==0) return;
    
	for (tmp_iter=tmp.begin();tmp_iter!=tmp.end();tmp_iter++)
	{
		Tmp.Format("%d",tmp_iter->first);
		(void)m_ListUser.AddItem(Tmp);
		
	}
	
}



UINT Verify(LPVOID pParam)
{ 
	unsigned char ImgData[IMAGE_SIZE];
	int ImgLen;
	int  ret=1;
	pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	ret = PSLoadChar(nDevAddr,CHAR_BUFFER_B,iCurSelID);
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true);
		return 1;
	}
	
	int count = 0;
	
	gbCancel=false;
	ret = PSGetImage(nDevAddr);  //��ȡͼ��  
	
	while(ret==PS_NO_FINGER)
	{
		ret=PSGetImage(nDevAddr);
		if(gbCancel)
		{
			pMyDlg->EnableBtn(true);
			return 1;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	//�ȶ�ʱ����ʾ��ǰ�������ϵ�ָ��
	if(pMyDlg->m_bPreImg)
	{
		if(glangid==0x0804)
			pMyDlg->ShowInfo("ͼ��¼��ɹ��������ϴ�...");
		else
			pMyDlg->ShowInfo("Success! Transfering...");
		
		ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
		
		memcpy(gImgData,ImgData,IMAGE_SIZE);
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		
		ret= PSImgData2BMP(ImgData,IMG_FILE);
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		pMyDlg->ShowImage();
	}
	//////////////////////////////////////////////////////////////////////////////////	
	if(glangid==0x0804)
		pMyDlg->ShowInfo("ͼ��¼��ɹ���\n\r\n");
	else
		pMyDlg->ShowInfo("Success to get image\n\r\n");
	
	ret = PSGenChar(nDevAddr,CHAR_BUFFER_A);  //����ģ��
	if (ret != PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret));
		pMyDlg->EnableBtn(true);
		return 1;
	}
	
    int nScore;
	clock_t finish,start;
	start=clock();
    ret=PSMatch(nDevAddr,&nScore);  //�ȶ�ģ��
    finish=clock();
	
	CString sInfo;
	
	if (ret == PS_OK)
	{
		
		if(nScore>50)
		{
			if(glangid==0x0804)
				sInfo.Format("�ȶ�ͨ��!\n��ʱ:%d����",finish-start);
			else
				sInfo.Format("Pass!\nUsed:%dms",finish-start);
			pMyDlg->ShowInfo(sInfo);
			pMyDlg->EnableBtn(true);
			return 1;
		}
		else
		{
			if(glangid==0x0804)
				sInfo.Format("�ȶ�ʧ��!\n��ʱ:%d����",finish-start);
			else
				sInfo.Format("Deny!\nUsed:%dms",finish-start);
			pMyDlg->ShowInfo(sInfo,1);
		}
		
		
	} 
	if(glangid==0x0804)
		sInfo.Format("�ȶ�ʧ��!\n��ʱ:%d����",finish-start);
	else
		sInfo.Format("Deny!\nUsed:%dms",finish-start);
    pMyDlg->ShowInfo(sInfo,1);
	pMyDlg->EnableBtn(true);
    return 1;
	
}

void CGDDemoDlg::OnVerify() 
{
	if(!bSelect)
	{
		if(glangid==0x0804)
			AfxMessageBox("����ѡ��Ҫ�ȶԵ�ģ�壡");
		else
			AfxMessageBox("Please select the template");
		return;
	}
	g_SaveMode = 1;
	ShowDefaltImg();
	if(glangid==0x0804)
		ShowInfo( "�뽫��ָƽ���ڴ�������..." );
	else
		ShowInfo("Please put your finger to sensor!");
	UpdateData(TRUE);
    AfxBeginThread( Verify,NULL );
}

//ָ������ �̻߳ص����� 
UINT Search(LPVOID pParam)
{ 
	pMyDlg->ShowDefaltImg();
	if(glangid==0x0804)
		pMyDlg->ShowInfo( "�뽫��ָƽ���ڴ�������..." );
	else
		pMyDlg->ShowInfo("Please put your finger to sensor!");
	int  ret=1;
	
    pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	
	gbCancel=false;
	
	
	ret = PSGetImage(nDevAddr);  //��ȡͼ��  
	
	while(ret==PS_NO_FINGER)
	{
		ret=PSGetImage(nDevAddr);
		if(gbCancel)
		{
			pMyDlg->EnableBtn(true);
			return 1;
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////
	//�ȶ�ʱ����ʾ��ǰ�������ϵ�ָ��
	unsigned char ImgData[IMAGE_SIZE];
	int ImgLen;
	if(pMyDlg->m_bPreImg)
	{
		if(glangid==0x0804)
			pMyDlg->ShowInfo("ͼ��¼��ɹ��������ϴ�...");
		else
			pMyDlg->ShowInfo("Success to get image! Transfering...");
		
		ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		memcpy(gImgData,ImgData,IMAGE_SIZE)	;
		ret= PSImgData2BMP(ImgData,IMG_FILE);
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		pMyDlg->ShowImage();
	}
	//////////////////////////////////////////////////////////////////////////////////		
	if(glangid==0x0804)
		pMyDlg->ShowInfo("ͼ��¼��ɹ�,�����С���\r\n");
	else
		pMyDlg->ShowInfo("Success to enroll,Searching...\r\n");
	
	ret = PSGenChar(nDevAddr,CHAR_BUFFER_A);  //����ģ��
	if (ret != PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true); 
		return FALSE;
	}
	
    clock_t start,finish;
	int iPageID = 0;
	start=clock();
	//	ret=PSSearch(nDevAddr,CHAR_BUFFER_A, 0, mCap+1, &iPageID);
	ret = PSHighSpeedSearch(nDevAddr,CHAR_BUFFER_A, 0, mCap+1, &iPageID);
    finish=clock();
	CString str;
	if (ret == PS_OK)
	{
		if(glangid==0x0804)
			str.Format("�ҵ���ͬ��ָ��IDΪ%d,\n��ʱ:%d����",iPageID,finish-start);
		else
			str.Format("Find same finger! ID = %d,\n Used:%d ms",iPageID,finish-start);
		pMyDlg->ShowInfo(str);
		
	}	
    else
	{
		if(glangid==0x0804)
			str.Format("û���ҵ���ͬ����ָ!\n��ʱ:%d����",finish-start);
		else
			str.Format("Not find same finger!\nUsed:%dms",finish-start);
		pMyDlg->ShowInfo(str,1);
	}
	pMyDlg->EnableBtn(true);
	
	
    return 1;
}
void CGDDemoDlg::OnSearch() 
{
	ShowDefaltImg();
	UpdateData(TRUE);
    g_SaveMode = 1; 
	AfxBeginThread( Search,NULL );	
	
}

void CGDDemoDlg::ClearDataBase()
{
	int ret;
	
	ret=PSEmpty(nDevAddr);
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );		
		return ;
	}
	/*	database
    CString Sql;
	Sql.Format("DELETE  FROM UserInfo " );
	G_db.DBExecuteSQL(Sql);
	*/		 	
	m_ListUser.DeleteAllItems();
	
}

void CGDDemoDlg::OnEmpty() 
{
	CString str;
	if(glangid==0x0804)
		str="��ȷʵҪ��������û���?";
	else
		str="Do you really want to clear all user?";
	if(::MessageBox(this->m_hWnd,str,"Tip",MB_OKCANCEL|MB_ICONINFORMATION)==IDCANCEL)
		return;
	
	int ret;
	
	ret=PSEmpty(nDevAddr);
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		
		return ;
	}
	
	if(glangid==0x0804)
		ShowInfo("ɾ���ɹ���");
	else
		ShowInfo("Success to clear!");
	
		/*	
		CString Sql;
		Sql.Format("DELETE  FROM UserInfo " );
		if(G_db.DBExecuteSQL(Sql))
		AfxMessageBox("ɾ�����ݿ�����ʧ�ܣ�");
	*/	
	m_ListUser.DeleteAllItems();	
	m_fingertable->DelAllTempelet();
}

void CGDDemoDlg::OnDelete() 
{
	if(!bSelect)
	{
		if(glangid==0x0804)
			AfxMessageBox("����ѡ��Ҫɾ���Ķ���");
		else
			AfxMessageBox("Please select the template want to delete!");
		return;
	}
	CString str;
	if(glangid==0x0804)
		str="��ȷʵҪɾ��ָ�����û���?";
	else
		str="Do you really want to delete the user?";
	
    if(::MessageBox(this->m_hWnd,str,"Tip",MB_OKCANCEL|MB_ICONINFORMATION)==IDCANCEL)
		return;
	
	
	int ret;
	
	ret=PSDelChar(nDevAddr,iCurSelID,1);
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		
		return ;
	}
	
	m_ListUser.DeleteItem(nSelectItem);
	bSelect=false;
	
	m_fingertable->DelOneTempelet(iCurSelID);
	/*	
    CString Sql;
	Sql.Format("DELETE  FROM UserInfo WHERE Address=%d" ,iCurSelID);
	if(G_db.DBExecuteSQL(Sql))
	AfxMessageBox("ɾ�����ݿ�����ʧ�ܣ�");
	*/	
	if(glangid==0x0804)
		pMyDlg->ShowInfo("ɾ��ָ����ַ�ɹ���");	
	else
		pMyDlg->ShowInfo("Delete the address success!");
}

void CGDDemoDlg::OnClickListuser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION posTemp;
	posTemp=m_ListUser.GetFirstSelectedItemPosition();
	if(posTemp== NULL)
	{
		bSelect=false;
		return;
	}
	nSelectItem=m_ListUser.GetNextSelectedItem(posTemp);
	
	CString sID=m_ListUser.GetItemText(nSelectItem,0);
	iCurSelID=StrToInt(sID);
	bSelect=true;
	
	*pResult = 0;	
	
}

void CGDDemoDlg::OnCancelOpt() 
{	
	gbCancel=true;		 
	Sleep(10);
	if(glangid==0x0804)
		ShowInfo("������ȡ��!");	
	else
		ShowInfo("Cancel");
    ShowDefaltImg();		
	EnableBtn(true);
    GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(false);
}

HBRUSH CGDDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CFont   f;   
	if(pWnd   ==   &m_TipInfo)   
	{   
		pDC->SetBkMode(TRANSPARENT);   
		pDC->SetTextColor(m_color);   		
		//	HBRUSH     newHbr   =   CreateSolidBrush(GetSysColor(COLOR_BTNFACE));   
		LOGFONT   logFont;   
		logFont.lfHeight=20;   
		logFont.lfWidth=0;   
		logFont.lfEscapement=0;   
		logFont.lfOrientation=0;   
		logFont.lfWeight=FW_BOLD;   
		logFont.lfItalic=0;
		logFont.lfQuality=1;
		logFont.lfUnderline=0;
		
		logFont.lfStrikeOut=0;   
		logFont.lfCharSet=ANSI_CHARSET;   
		logFont.lfOutPrecision=OUT_DEFAULT_PRECIS;   
		logFont.lfClipPrecision=OUT_DEFAULT_PRECIS;   
		logFont.lfQuality=PROOF_QUALITY;   
		logFont.lfPitchAndFamily=VARIABLE_PITCH|FF_ROMAN;   
		
		strcpy(logFont.lfFaceName,"Times   New   Roman");   
		f.CreateFontIndirect(&logFont);   
		pDC->SelectObject(&f);
	}  
	
	if(pWnd   ==   &m_Tip)   
	{   
		pDC->SetBkMode(TRANSPARENT);   
		pDC->SetTextColor(RGB(100,120,100));   //m_Tip   //Ӳ��������Ϣ  		
		HBRUSH     newHbr   =   CreateSolidBrush(GetSysColor(COLOR_BTNFACE));   		
		return   newHbr;   
	}   
	return   hbr;  	
}

UINT EnrollCon(LPVOID pParam)
{ 
	int  ret=0;
	
	unsigned char ImgData[IMAGE_SIZE];
	int ImgLen;
	
    CString Sql;
	pMyDlg->EnableBtn(false);
    pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	gbCancel = FALSE;
	
REENROLL:
	if(gbCancel)
		  {
		pMyDlg->EnableBtn(true);
		return 1;
		  }
	pMyDlg->ShowDefaltImg();
	static BOOL bReplace=FALSE;
	
    if (pMyDlg->m_fingertable->IsExisitId(pMyDlg->m_Addr))
    {
		if (!bReplace)
		{
			CString str;
			if(glangid==0x0804)
				str="�õ�ַ�Ѿ������û����Ƿ񸲸�?";
			else
				str="The address exist,Do you want to overwrite?";
			if ( AfxMessageBox(str, MB_YESNO) == IDYES )
				bReplace = TRUE;
			else
			{
				pMyDlg->EnableBtn(true);			
				return 1;
			}
		}
		
    }
	else 	 
	{
		bReplace = FALSE;
	}
	
	int iFingerNum = 0;
	int iBuffer;
	
	while (iFingerNum<2)
	{
		//�ڶ��ΰ���ָʱ����ʾ�û�����ָ��
		if(glangid==0x0804)
			pMyDlg->ShowInfo( "�뽫��ָƽ���ڴ�������..." );		
		else
			pMyDlg->ShowInfo("Please put your finger on sensor!");
		
		gbCancel=false;
		ret = PSGetImage(nDevAddr);  //��ȡͼ��  
		
		while(ret==PS_NO_FINGER)
		{
			ret=PSGetImage(nDevAddr);
			if(gbCancel)
			{
				pMyDlg->EnableBtn(true);
				pMyDlg->GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(false);
				return 1;
			}
		}
		
		if ( ret!=PS_OK )
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		
		
		//��һ��ִ��ʱ��ʾ�û��ÿ���ָ��
		if(glangid==0x0804)
			pMyDlg->ShowInfo( "���ÿ���ָ");	
		else
			pMyDlg->ShowInfo("Please take off finger!");
		Sleep(300);
		
		
		if(pMyDlg->m_bUpImg)
		{
			if(glangid==0x0804)
				pMyDlg->ShowInfo("ͼ��¼��ɹ��������ϴ�...");
			else
				pMyDlg->ShowInfo("Success to get finger,Transfering...");
			
			ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);
				return 1;
			}
			
			ret= PSImgData2BMP(ImgData,IMG_FILE);
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);
				return 1;
			}
			
			pMyDlg->ShowImage();
		}
		
		iBuffer = CHAR_BUFFER_A;
		if (iFingerNum == 1)
			iBuffer = CHAR_BUFFER_B;
		
		ret = PSGenChar(nDevAddr,iBuffer);  //����ģ��
		
		if (ret != PS_OK)
		{
			CString strTmp;
			if(glangid==0x0804)
				strTmp.Format("%s\n%s", PSErr2Str(ret) ,"\n������¼��");
			else
				strTmp.Format("%s\n%s", PSErr2Str(ret) ,"\nPlease reenroll!");
			pMyDlg->ShowInfo(strTmp);
			Sleep(1000);
			continue;			 
		}
		
		
        iFingerNum++;
        
		
		Sleep(500);
		
	}
	
	ret=PSRegModule(nDevAddr);  //�ϲ�����
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		Sleep(1000);
		goto REENROLL;
	}
	
	ret=PSStoreChar(nDevAddr,iBuffer, pMyDlg->m_Addr);    //���ģ��
	
	if(ret!=PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		Sleep(1000);
		goto REENROLL;
	}
	pMyDlg->strUser.Format("%d",pMyDlg->m_Addr);
	
	/*	
	if (bReplace)
	Sql.Format("UPDATE UserInfo SET Address = %d , UserName = '%s'  WHERE Address = %d",pMyDlg->m_Addr,pMyDlg->strUser,pMyDlg->m_Addr);
	else
	Sql.Format("INSERT  INTO UserInfo(Address,UserName) VALUES(%d,'%s')" ,pMyDlg->m_Addr,pMyDlg->strUser);
	
	  if(G_db.DBExecuteSQL(Sql))
	  {
	  AfxMessageBox("ע�ᵽ���ݿ��ʧ�ܣ�");
	  return 0;
	  }
	*/	
	CString tmp;
	if (bReplace)
	{
		//	pMyDlg->Update();
	}
	else
	{
		pMyDlg->m_fingertable->AppendTempelet(pMyDlg->m_Addr,pMyDlg->strUser);
		//	int index = pMyDlg->m_ListUser.GetItemCount();
		//	pMyDlg->m_ListUser.InsertItem(index, tmp);
		tmp.Format("%d",pMyDlg->m_Addr);
		pMyDlg->m_ListUser.AddItem(tmp);
		//	pMyDlg->m_ListUser.SetItemText(index,0,tmp);
		//	pMyDlg->m_ListUser.SetItemText(index,1,pMyDlg->strUser);
		
	}
	
	if(glangid==0x0804)
		pMyDlg->ShowInfo("�û���ӳɹ�!");
	else
		pMyDlg->ShowInfo("Success to add Finger!");
	
	pMyDlg->m_Addr++;
	Sleep(1000);
	goto REENROLL;
	
    pMyDlg->EnableBtn(true);
	
	return 1;
}


void CGDDemoDlg::OnEnrollCon() 
{
	UpdateData(TRUE);
	CUser DlgUser;
	DlgUser.m_Addr=m_Addr;
	DlgUser.m_UserInfo.Format("%d",m_Addr);
	DlgUser.bConEnroll=true;
	if(DlgUser.DoModal()==IDOK)
	{		
		m_Addr=DlgUser.m_Addr;
		strUser=DlgUser.m_UserInfo;
		AfxBeginThread( EnrollCon,NULL);//��ʼִ���߳�
	}
}

UINT SearchCon(LPVOID pParam)
{
	gbCancel=false;
	pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
RESEARCH:
	pMyDlg->ShowDefaltImg();
	if(glangid==0x0804)
		pMyDlg->ShowInfo( "�뽫��ָƽ���ڴ�������..." );
	else
		pMyDlg->ShowInfo( "Please put your finger on sensor..." );
	int  ret=1;
	
	if(gbCancel)
	{
		pMyDlg->EnableBtn(true);
		return 1;
	}
	
	ret = PSGetImage(nDevAddr);  //��ȡͼ��  
	
	while((ret==PS_NO_FINGER)&&(!gbCancel))
	{
		ret=PSGetImage(nDevAddr);
		if(gbCancel)
		{
			pMyDlg->EnableBtn(true);
			pMyDlg->GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(false);
			return 1;
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////
	//�ȶ�ʱ����ʾ��ǰ�������ϵ�ָ��
	unsigned char ImgData[IMAGE_SIZE];
	int ImgLen;
	if(pMyDlg->m_bPreImg)
	{
		if(glangid==0x0804)
			pMyDlg->ShowInfo("ͼ��¼��ɹ��������ϴ�...");
		else
			pMyDlg->ShowInfo("Success to get image,transfering...");
		
		ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		
		ret= PSImgData2BMP(ImgData,IMG_FILE);
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);
			return 1;
		}
		pMyDlg->ShowImage();
	}
	//////////////////////////////////////////////////////////////////////////////////	
	if(glangid==0x0804)
		
		pMyDlg->ShowInfo("ͼ��¼��ɹ�,�����С���\r\n");
	else
		pMyDlg->ShowInfo("Success to get image, Searching...\r\n");
	
	ret = PSGenChar(nDevAddr,CHAR_BUFFER_A);  //����ģ��
	if (ret != PS_OK)
	{
		pMyDlg->ShowInfo( PSErr2Str(ret) );
		pMyDlg->EnableBtn(true); 
		return FALSE;
	}
	
	clock_t start,finish;
	int iPageID = 0;
	start=clock();
	ret=PSSearch(nDevAddr,CHAR_BUFFER_A, 0, mCap+1, &iPageID);
	finish=clock();
	CString str;
	if (ret == PS_OK)
	{
		if(glangid==0x0804)
			str.Format("�ҵ���ͬ��ָ��IDΪ%d,\n��ʱ:%d����",iPageID,finish-start);
		else
			str.Format("Find same finger! ID=%d,\nUsed:%dms",iPageID,finish-start);
		pMyDlg->ShowInfo(str);
		
	}	
	else
	{	if(glangid==0x0804)
	str.Format("û���ҵ���ͬ����ָ!\n��ʱ:%d����",finish-start);
	else
		str.Format("Not find same finger!\nUsed:%dms",finish-start);
	pMyDlg->ShowInfo(str,1);
	}
	Sleep(1000);
	goto RESEARCH;
	pMyDlg->EnableBtn(true);
	return 1;
}

void CGDDemoDlg::OnSearchCon() 
{
	ShowDefaltImg();
	UpdateData(TRUE);
	g_SaveMode = 1;
   	AfxBeginThread( SearchCon,NULL );	
}

void CGDDemoDlg::OnSelchangeComboBaud() 
{
	// TODO: Add your control notification handler code here
	CString strBaud;
	int nBaud;
	if(glangid==0x0804)
		ShowInfo("��ʾ��Ϣ...");
	else
		ShowInfo("Tip...");
	if(bUsbComm)
		return;
	
	//��ȡѡ�в�����
	GetDlgItemText(IDC_COMBO_BAUD,strBaud);
	nBaud = atoi((char*)(LPCTSTR)strBaud);
	
	if(PSSetBaud(nDevAddr,nBaud/9600) == PS_OK)
		if(glangid==0x0804)
			ShowInfomation("���������óɹ���",RGB(0,0,255));
		else
			ShowInfomation("Success to set bandrate!",RGB(0,0,255));
		else
			if(glangid==0x0804)
				ShowInfomation("����������ʧ�ܣ�",RGB(255,0,0));
			else
				ShowInfomation("Fail to set bandrate!",RGB(255,0,0));
			//	EnableBtn(TRUE);
			
}

void CGDDemoDlg::OnSelchangeComboPakagesize() 
{
	// TODO: Add your control notification handler code here
	if(glangid==0x0804)
		ShowInfo("��ʾ��Ϣ...");
	else
		ShowInfo("Tip...");
	if(bUsbComm)
		return;
	
	UpdateData(TRUE);	//��ȡ�����б�ֵ
	
	if(PSSetPacketSize(nDevAddr,m_ComPakageSize) == PS_OK)
		if(glangid==0x0804)
			ShowInfomation("���ݰ���С���óɹ���",RGB(0,0,255));
		else
			ShowInfomation("Success to set package size",RGB(0,0,255));
		else
			if(glangid==0x0804)
				ShowInfomation("���ݰ���С����ʧ�ܣ�",RGB(255,0,0));
			else
				ShowInfomation("Fail to set package size!",RGB(255,0,0));
			//	EnableBtn(TRUE);
			
}

void CGDDemoDlg::OnSelchangeComboLevel() 
{
	// TODO: Add your control notification handler code here
	EnableBtn(FALSE);
	
	UpdateData(TRUE);	//��ȡ�����б�ֵ
	
	if(PSSetSecurLevel(nDevAddr,m_ComLevel+1) == PS_OK)
	{
		if(glangid==0x0804)
			ShowInfomation("��ȫ�ȼ����óɹ���",RGB(0,0,255));
		else
			ShowInfomation("Success to set secure level!",RGB(0,0,255));
		ShowPara();
	}
	else
		if(glangid==0x0804)
			ShowInfomation("��ȫ�ȼ�����ʧ�ܣ�",RGB(255,0,0));
		else
			ShowInfomation("Fail to set secure level!",RGB(255,0,0));
		EnableBtn(TRUE);
}

void CGDDemoDlg::OnSetfocusComboBaud() 
{
	// TODO: Add your control notification handler code here
	// 	EnableBtn(FALSE);
	if(glangid==0x0804)
		ShowInfomation("��ʾ��Ϣ...",RGB(0,0,255));
	else
		ShowInfomation("Tip...",RGB(0,0,255));
}

void CGDDemoDlg::OnSetfocusComboPakagesize() 
{
	// TODO: Add your control notification handler code here
	//	EnableBtn(FALSE);
	if(glangid==0x0804)
		
		ShowInfomation("��ʾ��Ϣ...",RGB(0,0,255));
	else
		ShowInfomation("Tip...",RGB(0,0,255));
	
}

void CGDDemoDlg::OnSetfocusComboLevel() 
{
	// TODO: Add your control notification handler code here
	//	EnableBtn(FALSE);
	if(glangid==0x0804)
		ShowInfomation("��ʾ��Ϣ...",RGB(0,0,255));
	else
		ShowInfomation("Tip...",RGB(0,0,255));
	
}

void CGDDemoDlg::OnBtnSavebmp() 
{
	// TODO: Add your control notification handler code here
	int ret;
	int ImgLen;
	unsigned char ImgData[IMAGE_SIZE]; 
	CString strFile;	
	//	ShowDefaltImg();  //kzf
	
	gbCancel=false;
	CString sFilter;
	if(glangid==0x0804)
		sFilter="λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||";
	else
		sFilter="BMP File(*.bmp)|*.bmp|All File(*.*)|*.*||";
	CFileDialog fo(FALSE,"bmp","Finger.bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFilter,NULL);
	
	if(fo.DoModal() != IDOK)
		return ;
	strFile = fo.GetFileName();
	
	EnableBtn(FALSE);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);	
	switch(g_SaveMode)
	{
		
	case 1:
		{		 
			ret= PSImgData2BMP(gImgData,(char*)(LPCTSTR)strFile);	//���浽�ļ�
			
			if(ret!=PS_OK)
			{
				ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
				EnableBtn(true);
				return ;		
			}
			break;
		}
	case 2:
		{			 
			ret= PSImgData2BMP(gImgData,(char*)(LPCTSTR)strFile);	//���浽�ļ�
			
			if(ret!=PS_OK)
			{
				ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
				EnableBtn(true);
				return ;		
			}
			break;
		}
	default:  //����λ�����ϴ�ͼƬ
		{
			if(glangid==0x0804)
				ShowInfo("ͼ�������ϴ�...");
			else
				ShowInfo("Transfering...");
			ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
			
			if(ret!=PS_OK)
			{
				ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
				EnableBtn(true);
				return ;		
			}
			
			ret= PSImgData2BMP(ImgData,(char*)(LPCTSTR)strFile);	//���浽�ļ�
			
			if(ret!=PS_OK)
			{
				ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
				EnableBtn(true);
				return ;		
			}
			break;
		}
		
	}
	
	
	ShowImage((char*)(LPCTSTR)strFile);
	if(glangid==0x0804)
		ShowInfomation("����ͼ��ɹ���",RGB(0,0,255));	
	else
		ShowInfomation("Success to save image",RGB(0,0,255));	
	EnableBtn(true);
	
	if (g_SaveMode == 2)
	{
		EnableBtn(FALSE);
		pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true); 
		if(glangid==0x0804)
			ShowInfo("�뽫��ָƽ���ڴ�������...");	
		else
			ShowInfo("Please put your finger on sensor...");
	}
	return ;
}



void CGDDemoDlg::OnBtnDlbmp() 
{	
	// TODO: Add your control notification handler code here
	int ret;
	int ImgLen = 0;
	unsigned char ImgData[IMAGE_SIZE]; 
	CString strFile;	
	CString sFilter;
	if(glangid==0x0804)
		sFilter="λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||";
	else
		sFilter="BMP File(*.bmp)|*.bmp|All File(*.*)|*.*||";
	CFileDialog fo(TRUE,"bmp",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFilter,NULL);
	if(fo.DoModal() != IDOK)
		return ;
	strFile = fo.GetFileName();
	
	EnableBtn(FALSE);
	
	ret= PSGetImgDataFromBMP((char*)(LPCTSTR)strFile,ImgData,&ImgLen);	//ͼ������װ�ص��ڴ�
	
    if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;		
	}
	if(glangid==0x0804)
		ShowInfo("��������ͼ��...");
	else
		ShowInfo("Downloading...");
	
	ret = PSDownImage(nDevAddr,ImgData,ImgLen);  //����ͼ��
	
	if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;		
	}
	
	ShowImage((char*)(LPCTSTR)strFile);
	if(glangid==0x0804)
		ShowInfomation("����ͼ��ɹ���",RGB(0,0,255));	
	else
		ShowInfomation("Success to download!",RGB(0,0,255));			
	EnableBtn(true);
	
	
	return ;
	
}

void CGDDemoDlg::ShowInfomation(CString strInfo,COLORREF color) 
{	
	m_color=color;	//��̬�޸���ʾ��Ϣ����ɫ
	SetDlgItemText(IDC_INFO,strInfo);	//��ʾ��ʾ��Ϣ
}

void CGDDemoDlg::OnBtnWnote() 
{
	// TODO: Add your control notification handler code here
	char seps[]   = " ,-";
	char *token;
	char buf[20];
	
	CNoteDlg notedlg;
	unsigned char UserContent[32];
	char noteInfo[100];
	int noteTmp[100];
	char a;
	int validChar=0;
	int noteLen;
	int i;
	
	if(notedlg.DoModal() != IDOK)
		return;
	
	if(notedlg.m_notepage < 0 || notedlg.m_notepage > 16)
	{
		if(glangid==0x0804)
			AfxMessageBox("ҳ��Ƿ���");
		else
			AfxMessageBox("Page is error!");
		return;
	}
	//��ʽת��
	noteLen = (notedlg.m_note).GetLength();
	
	memset(buf,0,20);
	////////////////////////////////////////////////////////////////////////
   	CString sTemp,st,sResult;
	sTemp = notedlg.m_note;
	
	sResult = "";
	
	token = strtok(sTemp.GetBuffer(noteLen), seps );
	while( token != NULL )
    {
		/* While there are tokens in "string" */
		strcpy(buf,token);
		st.Format("%.2X",atoi(token));
		token = strtok( NULL, seps );
		sResult = sResult + st;
	}
	
	noteLen = sResult.GetLength(); 	
	
	//////////////////////////////////////////////////////////////////////////
	// 	strcpy(noteInfo,(char*)(LPCTSTR)(notedlg.m_note) );
	
	strcpy(noteInfo,(char*)(LPCTSTR)(sResult));
	
	for(i=0; i<noteLen; i++)
	{
		a = noteInfo[i];
		if(a >= '0' && a <= '9')
			noteTmp[validChar++] = a - '0';
		else if(a >= 'a' && a <= 'f')
			noteTmp[validChar++] = a - 'a' + 10;
		else if(a >= 'A' && a <= 'F')
			noteTmp[validChar++] = a - 'A' + 10;
	}
	
	memset(UserContent,0,sizeof(unsigned char)*32);
	/*
	for(i=0; i<validChar/2; i++)
	UserContent[i] = noteTmp[2*i]*16 + noteTmp[2*i+1];
	*/
	for(i=0; i<validChar/2; i++)
		UserContent[i] = noteTmp[2*i]*16 + noteTmp[2*i+1];	
	//д���±�
	if( PSWriteInfo(nDevAddr,(notedlg.m_notepage),UserContent) == PS_OK)
		if(glangid==0x0804)
			ShowInfomation("д���±��ɹ���",RGB(0,0,255));
		else
			ShowInfomation("Success to write notepad!",RGB(0,0,255));
		else
			if(glangid==0x0804)
				ShowInfomation("д���±�ʧ�ܣ�",RGB(255,0,0));
			else
				ShowInfomation("Fail to write notepad!",RGB(255,0,0));
			
}

void CGDDemoDlg::OnBtnRnote() 
{
	// TODO: Add your control notification handler code here
	CRNoteDlg dlgRNote;
	unsigned char UserContent[32];
	
 
	if(dlgRNote.DoModal() != IDOK)
			return;
	 
	 
}

void CGDDemoDlg::OnBtnRandom() 
{
	// TODO: Add your control notification handler code here
	unsigned char Random[4];
	CString strTemp;\
		CString strShow;
	int i;
	if(PSGetRandomData(nDevAddr,Random) != PS_OK)
		if(glangid==0x0804)
			ShowInfomation("��ȡ�����ʧ�ܣ�",RGB(255,0,0));
		else
			ShowInfomation("Fail to get random data!",RGB(255,0,0));
		else
		{
			if(glangid==0x0804)
				strShow = "��ȡ���������Ϊ��";
			else
				strShow="The random data is: ";
			for(i=0; i<4; i++)
			{
				strTemp.Format("%02x",Random[i]);
				strShow += strTemp;
			}
			ShowInfomation( strShow,RGB(0,0,255) );		
		}
}

void CGDDemoDlg::OnBtnRnum() 
{
	// TODO: Add your control notification handler code here
	int templetNum = 0;
	CString strShow;
	if(PSTemplateNum(nDevAddr,&templetNum)!= PS_OK)
		if(glangid==0x0804)
			ShowInfomation("����Чģ�����ʧ��",RGB(255,0,0));
		else
			ShowInfomation("Fail to read valid template number!",RGB(255,0,0));
		else
		{
			if(glangid==0x0804)
				strShow.Format("��Чģ�����Ϊ%d��",templetNum);
			else
				strShow.Format("Valid template number: %d",templetNum);
			ShowInfomation(strShow,RGB(0,0,255));		
		}
}


CString demoImageFile;
void CGDDemoDlg::ShowDemoImage(int Imagetype,CString sPath) 
{
	int ret;
	int ImgLen;
	unsigned char ImgData[IMAGE_SIZE];
	
	CString strFile = sPath;	
	
	EnableBtn(FALSE);
	
	ret= PSGetImgDataFromBMP((char*)(LPCTSTR)strFile,ImgData,&ImgLen);	//ͼ������װ�ص��ڴ�
	
    if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;		
	}
	
	if(glangid==0x0804)
		ShowInfo("��������ͼ��...");
	else
		ShowInfo("Downloading...");
	
	ret = PSDownImage(nDevAddr,ImgData,ImgLen);  //����ͼ��
	
	if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;		
	}
	
	//ͼ����
	ret = PSGenBinImage(nDevAddr,Imagetype);
	
	if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;		
	}
	if(glangid==0x0804)
		ShowInfo("����ͼ��ɹ��������ϴ�...");
	else
		ShowInfo("Success to get image,Transfering...");
	ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
		  
	if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;	
	}
	ret= PSImgData2BMP(ImgData,IMG_FILE);
	if(ret!=PS_OK)
	{
		ShowInfomation(PSErr2Str(ret),RGB(255,0,0));
		EnableBtn(true);
		return ;
		
	}
	if(glangid==0x0804)
		ShowInfo("������ɣ�");
	else
		ShowInfo("Complete!");
	
	
	//�ڽ�������ʾͼ��	  
	ShowImage(IMG_FILE);
	
	EnableBtn(TRUE);
}

void CGDDemoDlg::OnBtnBin() 
{
	// TODO: Add your control notification handler code here
	//	ShowDefaltImg();
	CString sPath("");
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_Path);
    pEdit->GetWindowText(sPath);
	if (sPath.IsEmpty())
	{
		if(glangid==0x0804)
			AfxMessageBox("����ѡ��ͼƬ");
		else
			AfxMessageBox("Please select the image");
		return;
	}
	ShowDemoImage(0,sPath);
}

void CGDDemoDlg::OnBtnThin() 
{
	// TODO: Add your control notification handler code here
	//	ShowDefaltImg();
	
	CString sPath("");
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_Path);
    pEdit->GetWindowText(sPath);
	if (sPath.IsEmpty())
	{
		if(glangid==0x0804)
			AfxMessageBox("����ѡ��ͼƬ");
		else
			AfxMessageBox("Please select the image");
		return;
	}
	ShowDemoImage(1,sPath);
	
}

void CGDDemoDlg::OnBtnTz() 
{
	// TODO: Add your control notification handler code here
	//	ShowDefaltImg();
	CString sPath("");
	UpdateData(FALSE);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_Path);
    pEdit->GetWindowText(sPath);
	if (sPath.IsEmpty())
	{	if(glangid==0x0804)
	AfxMessageBox("����ѡ��ͼƬ");	
	else
		AfxMessageBox("Please select the image");
	return;
	}
	ShowDemoImage(2,sPath);
	
}

void CGDDemoDlg::ShowDefaltImg() 
{
	
	// TODO: Add your control notification handler code here
	HBITMAP hBitmapFP;
	
	if (PathFileExists(szUserLogoPath))
		hBitmapFP  = (HBITMAP)LoadImage( NULL,szUserLogoPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	else
		hBitmapFP=LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_PREVIEW));
	
	((CStatic*)GetDlgItem(IDC_IMAGE))->SetBitmap(hBitmapFP);
	DeleteObject(hBitmapFP);
	
}

void CGDDemoDlg::ShowImage(char *filename) 
{
	// TODO: Add your control notification handler code here
	CString strFile;
	
	
	if(filename==NULL)
		strFile = IMG_FILE;
	else
		strcpy((char*)(LPCTSTR)strFile,filename);
	
    HBITMAP hBitmapFP;
	
    hBitmapFP = (HBITMAP)LoadImage( GetModuleHandle(NULL),(LPCTSTR)strFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	
	if (hBitmapFP  == NULL)
		hBitmapFP  = (HBITMAP)LoadImage( NULL,(LPCTSTR)strFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	((CStatic*)pMyDlg->GetDlgItem(IDC_IMAGE))->SetBitmap(hBitmapFP);
	
	DeleteObject(hBitmapFP);	
}

void CGDDemoDlg::OnBtnOribmp() 
{
	// TODO: Add your control notification handler code here
	//��Ӳ�̵�ͼ�����ص�ģ��
	
	//	CFileDialog fo(TRUE,"bmp",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||",NULL);
	//	if(fo.DoModal() != IDOK)
	//		return ;
	CString sPath;
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_Path);
    pEdit->GetWindowText(sPath);
	if (sPath.IsEmpty())
	{
		if(glangid==0x0804)
			AfxMessageBox("����ѡ��ͼƬ");
		else
			AfxMessageBox("Please select the image");
		return;
	}
	//�ڽ�������ʾͼ��	  
	ShowImage((char*)(LPCTSTR)sPath);
}

void CGDDemoDlg::OnBtnGetdb() 
{
	// TODO: Add your control notification handler code here
	CDlgFingerDB dlgFingerDbDlg;
	this->ShowWindow(FALSE);	//�ر����Ի���ֻ��ʾ�ɼ�ͼ��Ի���
	dlgFingerDbDlg.DoModal();
	this->ShowWindow(TRUE);		//��ʾ���Ի���
	this->ShowDefaltImg();
}

void CGDDemoDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
	
}

void CGDDemoDlg::OnPath() 
{
	// TODO: Add your control notification handler code here
	
	CString sPath;
	
	CFileDialog FileDlg(
		TRUE,
		"*.bmp",
		"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL
		); 
	
	if (FileDlg.DoModal()!=IDOK)
	{
		return;
	}
	
	
	sPath = FileDlg.GetPathName();
	if (sPath == "C:\\Finger.bmp")
	{
		if(glangid==0x0804)
			AfxMessageBox("��ͼƬ������ʹ�ã���ѡ����ͼƬ");
		else
			AfxMessageBox("The image is useing,please select another image!");
		return;
	}
    CEdit *pEdit = (CEdit *)GetDlgItem(IDC_Path);
	//  pEdit->GetWindowText(sPath);
	pEdit->SetWindowText(sPath);
	UpdateData(FALSE);
	
	ShowImage((char*)(LPCTSTR)sPath);
	
}


UINT GenImgCon(LPVOID pParam)
{
	
	int ret,i=0;
	int ImgLen;
	unsigned char ImgData[IMAGE_SIZE]; 
    clock_t start,finish;
	CString strinfo;
	gbCancel=false;
	pMyDlg->EnableBtn(false);
	pMyDlg->GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	//pMyDlg->GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(true);
	
	while (!gbCancel)
	{	
		
		//	pMyDlg->ShowDefaltImg();
		if(glangid==0x0804)
			pMyDlg->ShowInfo("�뽫��ָƽ���ڴ�������...");		
		else
			pMyDlg->ShowInfo("Please put your finger on sensor...");
		
		if (gbCancel) break;
		    	 
		start = clock();
		ret = PSGetImage(nDevAddr);  //��ȡͼ��  
		finish = clock();
		while ((ret==PS_NO_FINGER)&&(!gbCancel))
		{			
			if(gbCancel)
			{
				pMyDlg->EnableBtn(true);
				pMyDlg->GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(false);
				return 1;
			}
			else
			{
				start = clock();
				finish=start;
				ret = PSGetImage(nDevAddr);
				finish = clock();
			}
		}
		
		if(ret!=PS_OK)
		{
			pMyDlg->ShowInfo( PSErr2Str(ret) );
			pMyDlg->EnableBtn(true);			
			return 1;
		}
		
		
	//	Sleep(300);
		if (!gbCancel)  		
		{
			
			if(glangid==0x0804)
				strinfo="ͼ�������ϴ�...";
			else
				strinfo="Image transfering...";
			pMyDlg->ShowInfo(strinfo);
			ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //�ϴ�ͼ��
			
			memcpy(gImgData,ImgData,IMAGE_SIZE);
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);			
				return 1;
			}
			
			ret= PSImgData2BMP(ImgData,IMG_FILE);
			
			if(ret!=PS_OK)
			{
				pMyDlg->ShowInfo( PSErr2Str(ret) );
				pMyDlg->EnableBtn(true);
				
				return 1;
			}
			pMyDlg->ShowImage();
			if(glangid==0x0804)
				strinfo.Format("ͼ��¼��ɹ�!��ȡͼ���ʱ%d����",finish-start);
			else
				strinfo.Format("Success to get image!Get image used %d ms",finish-start);
			 
				pMyDlg->ShowInfo(strinfo);
			pMyDlg->GetDlgItem(IDC_BTN_SAVEBMP)->EnableWindow(true);
		}
		else
		{
			
			pMyDlg->ShowDefaltImg();
		}
		
		
		Sleep(1000);
		
	}
	pMyDlg->EnableBtn(true);
	
	return 0;
	
}

void CGDDemoDlg::OnGetImgCon() 
{
	// TODO: Add your control notification handler code here
	g_SaveMode = 2;   
	AfxBeginThread( GenImgCon,NULL);//��ʼִ���߳� 	
}


BOOL CGDDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam ==VK_ESCAPE) || (pMsg->wParam ==VK_RETURN))
		{
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CGDDemoDlg::OnUserdefine() 
{
	// TODO: Add your control notification handler code here
	CDLGUSERDEFINE DlgUserDefine;
	DlgUserDefine.DoModal();
}

void CGDDemoDlg::LoadUserDefine()
{
	TCHAR   szFilePath[256] = {0};   
    TCHAR   szTemp[256] = {0};   
	TCHAR   szExePath[256] = {0};
	
	TCHAR   szDrive[255];
    TCHAR   szDir[255];
	TCHAR   szFname[255];
    TCHAR   szExt[5];
	
	::GetModuleFileName(GetModuleHandle(NULL),szExePath,256);
	_splitpath(szExePath,szDrive,szDir,szFname,szExt) ;
	_tcscat(szDrive,szDir);
    _tcscpy(szUserLogoPath,szDrive);
	_tcscat(szUserLogoPath,"Logo.bmp");
	_tcscat(szDrive,"info.ini");
	_tcscpy(szFilePath,szDrive);
	
	if (PathFileExists(szFilePath))
	{
		::GetPrivateProfileString("UserInfo","Title","syno Demo",szTemp,20,szFilePath);   
		::SetWindowText(AfxGetMainWnd()->GetSafeHwnd(),szTemp);
		
		::GetPrivateProfileString("UserInfo","HardwareInfo","syno",szTemp,40,szFilePath); 

		::GetPrivateProfileString("UserInfo","ShowHard","0",szHard,20,szFilePath); 
		CString stInfo;
		if(glangid==0x0804)
			stInfo.Format("��ӭʹ��%s���Գ������ȴ��豸!",szTemp);
		else
			stInfo.Format("Welcome to use %s Demo, Please Open device first!",szTemp);
		m_sTip = stInfo; 
		UpdateData(FALSE);
	}
	return;
}
void CGDDemoDlg::InitWinText() 
{
	if(glangid==0x0804)
	{
		this->SetWindowText("ָ��ģ����ʾDemo");
		GetDlgItem(IDC_IMGPREVIEW)->SetWindowText("ָ��ͼ��Ԥ����");
		GetDlgItem(IDC_HDINFO)->SetWindowText("Ӳ����Ϣ");
		GetDlgItem(IDC_INIT)->SetWindowText("��ʼ��");
		GetDlgItem(IDC_DEVSETTING)->SetWindowText("�豸����");
		GetDlgItem(IDC_DB)->SetWindowText("���ݿ����");
		GetDlgItem(IDC_IMAGEMANAGE)->SetWindowText("ͼ�����");
		GetDlgItem(IDC_FINGERENROLL)->SetWindowText("ָ��¼��");
		
		GetDlgItem(IDC_SEARCH)->SetWindowText("�ȶ�");
		GetDlgItem(IDC_SPECULE)->SetWindowText("���⹦����");
		GetDlgItem(IDC_DOWITHIMG)->SetWindowText("ͼ������ʾ");
		GetDlgItem(IDC_CHKDEV)->SetWindowText("�ϴ�ͼ��");
		GetDlgItem(IDC_Preview)->SetWindowText("Ԥ��ͼ��");
		
		GetDlgItem(IDC_BANDRATE)->SetWindowText("����������");
		GetDlgItem(IDC_PACKAGESIZE)->SetWindowText("���ݰ���С");
		GetDlgItem(IDC_SECURELEVEL)->SetWindowText("��ȫ�ȼ�");
		
		
		GetDlgItem(IDC_BUTTON1)->SetWindowText("���豸(&O)");
		GetDlgItem(IDC_BUTTON9)->SetWindowText("ɾ��");
		GetDlgItem(IDC_BUTTON10)->SetWindowText("���");
		GetDlgItem(IDC_BUTTON6)->SetWindowText("ȡ����ǰ����");
		GetDlgItem(IDC_Exit)->SetWindowText("�˳�����");
		GetDlgItem(IDC_BUTTON3)->SetWindowText("��ȡͼ��");
		GetDlgItem(IDC_GetImgCon)->SetWindowText("������ȡͼ��");
		
		GetDlgItem(IDC_BTN_SAVEBMP)->SetWindowText("����ͼ��");
		GetDlgItem(IDC_BTN_DLBMP)->SetWindowText("����ͼ��");
		GetDlgItem(IDC_BUTTON4)->SetWindowText("¼��ģ��");
		GetDlgItem(IDC_BUTTON2)->SetWindowText("����¼��");
		GetDlgItem(IDC_BUTTON7)->SetWindowText("��һ�ȶ�(&C)");
		
		
		GetDlgItem(IDC_BUTTON8)->SetWindowText("����");
		GetDlgItem(IDC_BUTTON9)->SetWindowText("ɾ��");
		GetDlgItem(IDC_BUTTON5)->SetWindowText("��������");
		GetDlgItem(IDC_BTN_RNOTE)->SetWindowText("�����±�");
		GetDlgItem(IDC_BTN_WNOTE)->SetWindowText("д���±�");
		GetDlgItem(IDC_BTN_RANDOM)->SetWindowText("��ȡ�����");
		GetDlgItem(IDC_BTN_RNUM)->SetWindowText("����Чģ����");
		
		GetDlgItem(IDC_BTN_GETDB)->SetWindowText("�ɼ�ָ�ƿ�");
		GetDlgItem(IDC_USERDEFINE)->SetWindowText("�Զ�������");
		GetDlgItem(IDC_BUTTON13)->SetWindowText("·��");
		GetDlgItem(IDC_BTN_ORIBMP)->SetWindowText("ԭʼͼ��");
		GetDlgItem(IDC_BTN_BIN)->SetWindowText("��ֵͼ");
		
		GetDlgItem(IDC_BTN_THIN)->SetWindowText("ϸ��ͼ");
		GetDlgItem(IDC_BTN_TZ)->SetWindowText("������ϸ��ͼ");
		
		GetDlgItem(IDC_INFO)->SetWindowText("��ʾ��Ϣ...");
	}
	else
	{
		this->SetWindowText("Fingerprint Module Demo");
		GetDlgItem(IDC_IMGPREVIEW)->SetWindowText("Image Preview");
		GetDlgItem(IDC_HDINFO)->SetWindowText("Hardware Infomation");
		GetDlgItem(IDC_INIT)->SetWindowText("Initialization");
		GetDlgItem(IDC_DEVSETTING)->SetWindowText("Device Manage");
		GetDlgItem(IDC_DB)->SetWindowText("Template Database");
		GetDlgItem(IDC_IMAGEMANAGE)->SetWindowText("Image Manage");
		GetDlgItem(IDC_FINGERENROLL)->SetWindowText("Enroll");
		
		
		GetDlgItem(IDC_BANDRATE)->SetWindowText("Baudrate");
		GetDlgItem(IDC_PACKAGESIZE)->SetWindowText("Package Size");
		GetDlgItem(IDC_SECURELEVEL)->SetWindowText("Secure Level");
		
		
		GetDlgItem(IDC_SEARCH)->SetWindowText("Match");
		GetDlgItem(IDC_SPECULE)->SetWindowText("Special");
		GetDlgItem(IDC_DOWITHIMG)->SetWindowText("Deal with image");
		GetDlgItem(IDC_CHKDEV)->SetWindowText("Preview");
		GetDlgItem(IDC_Preview)->SetWindowText("Preview");
		
		
		GetDlgItem(IDC_BUTTON1)->SetWindowText("Open Device(&O)");
		GetDlgItem(IDC_BUTTON9)->SetWindowText("Delete");
		GetDlgItem(IDC_BUTTON10)->SetWindowText("Empty");
		GetDlgItem(IDC_BUTTON6)->SetWindowText("Cancel Operate");
		GetDlgItem(IDC_Exit)->SetWindowText("Exit");
		GetDlgItem(IDC_BUTTON3)->SetWindowText("Capture");
		GetDlgItem(IDC_GetImgCon)->SetWindowText("Con Capture");
		
		GetDlgItem(IDC_BTN_SAVEBMP)->SetWindowText("Save Image");
		GetDlgItem(IDC_BTN_DLBMP)->SetWindowText("Download Image");
		GetDlgItem(IDC_BUTTON4)->SetWindowText("Enroll");
		GetDlgItem(IDC_BUTTON2)->SetWindowText("Con Enroll");
		GetDlgItem(IDC_BUTTON7)->SetWindowText("Match");
		
		
		GetDlgItem(IDC_BUTTON8)->SetWindowText("Search");
		GetDlgItem(IDC_BUTTON9)->SetWindowText("Delete");
		GetDlgItem(IDC_BUTTON5)->SetWindowText("Con Search");
		GetDlgItem(IDC_BTN_RNOTE)->SetWindowText("Read Notepad");
		GetDlgItem(IDC_BTN_WNOTE)->SetWindowText("Write Notepad");
		GetDlgItem(IDC_BTN_RANDOM)->SetWindowText("Random");
		GetDlgItem(IDC_BTN_RNUM)->SetWindowText("Valid Template");
		
		GetDlgItem(IDC_BTN_GETDB)->SetWindowText("Capture Image DB");
		GetDlgItem(IDC_USERDEFINE)->SetWindowText("Define Command");
		GetDlgItem(IDC_BUTTON13)->SetWindowText("Path");
		GetDlgItem(IDC_BTN_ORIBMP)->SetWindowText("Source");
		GetDlgItem(IDC_BTN_BIN)->SetWindowText("Bin Image");
		
		GetDlgItem(IDC_BTN_THIN)->SetWindowText("Thin Image");
		GetDlgItem(IDC_BTN_TZ)->SetWindowText("Template Image");
		GetDlgItem(IDC_INFO)->SetWindowText("Info...");
	}
	LoadUserDefine();
}
void CGDDemoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
	InitWinText() ;

}

void CGDDemoDlg::InitTmpList()
{
	
	
}



void CGDDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_fingertable!=NULL)
	{
		delete m_fingertable;
		m_fingertable = NULL;
	}
	
	CDialog::OnClose();
}

void CGDDemoDlg::OnEditchangeComlang() 
{
	// TODO: Add your control notification handler code here
	
}

void CGDDemoDlg::OnSelchangeComlang() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Lang=="Chinese")
	{
		glangid=0x0804;
		InitWinText();
	}
	else
	{
		glangid=0x0001;
		InitWinText();
	}
}
