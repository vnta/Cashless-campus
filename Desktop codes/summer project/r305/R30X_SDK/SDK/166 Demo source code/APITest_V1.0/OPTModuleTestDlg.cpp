// OPTModuleTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPTModuleTest.h"
#include "OPTModuleTestDlg.h"
#include "Protocol.h"
#include "math.h"
#include "shlwapi.h"
#include "BinImg.h"

#include "DownCharLib.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

int gSecureLevel,gBaud,gAddr,gPwd,gPacket;
CString gSaveFile;

/////////////////////////////////////////////////////////////////////////////
// COPTModuleTestDlg dialog
bool gbCancel=false;

COPTModuleTestDlg::COPTModuleTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COPTModuleTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COPTModuleTestDlg)  13819113589
	m_Pwd = _T("0000");
	m_Address = 0;
	m_DeviceType = _T("COM");
	m_AddrStr = _T("FFFFFFFF");
	m_SecureLevel = _T("3");
	m_InfoPage = 0;
	m_DelStart = 0;
	m_DelNum = 1;
	m_sInfo = _T("");
	m_bOpen = 0;
	m_NewMBID = 0;
	m_strBaud = _T("57600");
	m_strSetBaud = _T("57600");
	m_SysInfo = _T("");
	m_Path = _T("");
	m_ISPType = 0;
	m_StartMBID = 0;
	gSecureLevel=-1;
	gBaud=-1;
	gAddr=-1;
	gPwd=-1;
	gPacket=-1;
	m_ProgressName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 	pDlg = new CDlgContent();
	pDlg->Create(IDD_Content,this);
	blShowWin = FALSE;
	blDeviceOpen = FALSE;
}

COPTModuleTestDlg::~COPTModuleTestDlg()
{	
//	pDlg->DestroyWindow();
 	delete pDlg;
    pDlg = NULL;
}
void COPTModuleTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COPTModuleTestDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_COMBO7, m_PackSizeCmb);
	DDX_Control(pDX, IDC_COMBO4, m_Buffer);
	DDX_Control(pDX, IDC_COMBO3, m_BaudNum);
	DDX_Control(pDX, IDC_BITMAP, m_Finger);
	DDX_Control(pDX, IDC_COMBO2, m_Baud);
	DDX_Control(pDX, IDC_COMBO1, m_Com);
	DDX_Text(pDX, IDC_EDIT1, m_Pwd);
	DDX_Text(pDX, IDC_EDIT3, m_Address);
	DDX_CBString(pDX, IDC_COMBO5, m_DeviceType);
	DDX_Text(pDX, IDC_EDIT9, m_AddrStr);
	DDX_CBString(pDX, IDC_COMBO6, m_SecureLevel);
	DDX_Text(pDX, IDC_INFOPAGE, m_InfoPage);
	DDV_MinMaxUInt(pDX, m_InfoPage, 0, 99);
	DDX_Text(pDX, IDC_DELSTART, m_DelStart);
	DDV_MinMaxUInt(pDX, m_DelStart, 0, 9999);
	DDX_Text(pDX, IDC_DELNUM, m_DelNum);
	DDV_MinMaxUInt(pDX, m_DelNum, 1, 9999);
	DDX_Text(pDX, IDC_EDIT4, m_sInfo);
	DDX_Text(pDX, IDC_EDIT7, m_bOpen);
	DDX_Text(pDX, IDC_EDIT8, m_NewMBID);
	DDV_MinMaxUInt(pDX, m_NewMBID, 0, 1024);
	DDX_CBString(pDX, IDC_COMBO2, m_strBaud);
	DDX_CBString(pDX, IDC_COMBO3, m_strSetBaud);
	DDX_Text(pDX, IDC_SYSINFO, m_SysInfo);
	DDX_CBString(pDX, IDC_COMBO7, m_strPack);
	DDX_Text(pDX, IDC_EDIT10, m_Path);
	DDX_Text(pDX, IDC_ISPTYPE, m_ISPType);
	DDV_MinMaxUInt(pDX, m_ISPType, 0, 2);
	DDX_Text(pDX, IDC_ProgressName, m_ProgressName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COPTModuleTestDlg, CDialog)
	//{{AFX_MSG_MAP(COPTModuleTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnGDOpenCom)
	ON_BN_CLICKED(IDC_BUTTON3, OnVfyPwd)
	ON_BN_CLICKED(IDC_BUTTON2, OnSetPwd)
	ON_BN_CLICKED(IDC_BUTTON4, OnSetSecureLevel)
	ON_BN_CLICKED(IDC_BUTTON5, OnGDGetImage)
	ON_BN_CLICKED(IDC_BUTTON6, OnGDUpImage)
	ON_BN_CLICKED(IDC_BUTTON8, OnGDGetImage2BMP)
	ON_BN_CLICKED(IDC_BUTTON7, OnDownImage)
	ON_BN_CLICKED(IDC_BUTTON9, OnGetImgDataFromBMP)
	ON_BN_CLICKED(IDC_BUTTON12, OnSetBaud)
	ON_BN_CLICKED(IDC_BUTTON16, OnReadInfo)
	ON_BN_CLICKED(IDC_BUTTON17, OnWriteInfo)
	ON_BN_CLICKED(IDC_BUTTON14, OnReadParTable)
	ON_BN_CLICKED(IDC_BUTTON18, OnGenChar)
	ON_BN_CLICKED(IDC_BUTTON19, OnMatch)
	ON_BN_CLICKED(IDC_BUTTON20, OnSearch)
	ON_BN_CLICKED(IDC_BUTTON21, OnRegModule)
	ON_BN_CLICKED(IDC_BUTTON22, OnStoreChar)
	ON_BN_CLICKED(IDC_BUTTON23, OnLoadChar)
	ON_BN_CLICKED(IDC_BUTTON26, OnDelOneChar)
	ON_BN_CLICKED(IDC_BUTTON27, OnEmpty)
	ON_BN_CLICKED(IDC_BUTTON24, OnUpChar)
	ON_BN_CLICKED(IDC_BUTTON25, OnDownChar)
	ON_BN_CLICKED(IDC_BUTTON15, OnSetPktSize)
	ON_BN_CLICKED(IDC_BUTTON28, OnGDUpChar2File)
	ON_BN_CLICKED(IDC_BUTTON29, OnDownCharFromFile)
	ON_BN_CLICKED(IDC_BUTTON30, OnSetChipAddr)
	ON_BN_CLICKED(IDC_BUTTON10, OnGetRandomData)
	ON_BN_CLICKED(IDC_BUTTON32, OnPortControl)
	ON_BN_CLICKED(IDC_BUTTON31, OnReadInfPage)
	ON_BN_CLICKED(IDC_BUTTON11, OnEnroll)
	ON_BN_CLICKED(IDC_BUTTON13, OnIdenty)
	ON_BN_CLICKED(IDC_BUTTON33, OnHighSpeedSearch)
	ON_BN_CLICKED(IDC_BUTTON34, OnAutoOpen)
	ON_BN_CLICKED(IDC_BUTTON35, OnSelPath)
	ON_BN_CLICKED(IDC_TFRR, OnTFRR)
	ON_BN_CLICKED(IDC_TFAR, OnTFAR)
	ON_BN_CLICKED(IDC_BUTTON36, OnTCancel)
	ON_BN_CLICKED(IDC_GENTZ, OnGentz)
	ON_BN_CLICKED(IDC_BINIMG, OnBinimg)
	ON_BN_CLICKED(IDC_BUTTON37, OnISP)
	ON_BN_CLICKED(IDC_BUTTON38, OnTemplateNum)
	ON_BN_CLICKED(IDC_BUTTON39, OnEnrollLX)
	ON_BN_CLICKED(IDC_BUTTON40, OnIdentyLX)
	ON_BN_CLICKED(IDC_BUTTON41, OnDownMBLX)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON42, OnCloseWindow)
	ON_BN_CLICKED(IDC_BUTTON43, OnDownCharLib)
	ON_BN_CLICKED(IDC_BUTTON45, OnData2BMP)
	ON_BN_CLICKED(IDC_BUTTON46, OnShowData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPTModuleTestDlg message handlers
COPTModuleTestDlg *pMyDlg;
BOOL COPTModuleTestDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
//////////////////////////////////////////////////////////////////////////////////
 	m_tooltip.Create(this);
    m_tooltip.AddTool(GetDlgItem(IDC_BUTTON34),_T("Open device automaticallydd"),NULL);
 	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1),_T("Open Device"),NULL);
///////////////////////////////////////////////////////////////////////////////////////	
	// TODO: Add extra initialization here
	m_Com.SetCurSel(0);
	m_Baud.SetCurSel(3);
	m_BaudNum.SetCurSel(3);
	m_Buffer.SetCurSel(0);
    LoadPara(); 
	pMyDlg=this;

//////////////////////////////////////////////////////////////////////////
/* 	CClientDC dc(this);
 
 	CFont font;
     
 	VERIFY(font.CreatePointFont(160, _T("Arial"), &dc));
    
 	CStatic *pS = (CStatic *)GetDlgItem(IDC_Group2);
    pS->SetFont(&font);
*/
//////////////////////////////////////////////////////////////////////////
   // font.DeleteObject();

	CButton *pButton  = (CButton *)GetDlgItem(IDC_CHECK1);
	pButton->SetCheck(TRUE);
 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COPTModuleTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COPTModuleTestDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COPTModuleTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

unsigned char gpImageData[256*288];
int gnImageSize;

unsigned char gTzBuf[1024];
int gTzLen;


int strHexToInt(CString strSource,UINT *nVal)
{	
	int nTemp=0;
	
	CString strTemp;
	strTemp=strSource;
	for(char cc='G',dd='g';   cc<='Z',dd<='z';  cc++,dd++)    //判断输入的字符串是否合法
	{
		if(strTemp.Find(cc,0) !=-1  ||  strTemp.Find(dd,0) !=-1)
		{
			::MessageBox(NULL,"please input a valid hex data!","input error",MB_ICONEXCLAMATION);
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

void COPTModuleTestDlg::SavePara(CString sName,int nVal)
{
	char strDir[1024];
	int nLen=GetCurrentDirectory(1024,strDir);
	strcat(strDir,"\\Finger.ini");
	CString sVal;
	sVal.Format("%d",nVal);
	::WritePrivateProfileString("Syno Para",sName,sVal,strDir);
 	
}
void COPTModuleTestDlg::LoadPara()
{
	char strDir[1024];
	char pAddr[256];
	int nLen=GetCurrentDirectory(1024,strDir);
	strcat(strDir,"\\Finger.ini");
    int nBaud=GetPrivateProfileInt("Syno Para","Baud",3,strDir);
	int nPackSize=GetPrivateProfileInt("Syno Para","PackSize",2,strDir);
	GetPrivateProfileString("Syno Para","Addr","FFFFFFFF",pAddr,256,strDir);
	m_AddrStr.Format("%s",pAddr);
	m_Baud.SetCurSel(nBaud);
	m_BaudNum.SetCurSel(nBaud);
	m_PackSizeCmb.SetCurSel(nPackSize);
	UpdateData(TRUE);
	//UpdateData(TRUE);
    CString str;
	str="Original parameter when device opened :\n";  //上次打开设备参数为
	str+="Devcie Address: "+m_AddrStr;
	str+="  Baudrate:"+m_strBaud;
	str+="  Package Size:"+m_strPack;
	m_SysInfo=str;
    UpdateData(FALSE);
}

void COPTModuleTestDlg::OnGDOpenCom() 
{
	int iCom;
	int iBaud;

	UpdateData(TRUE);

	iCom = m_Com.GetCurSel()+1;
    iBaud = StrToInt(m_strBaud)/9600;
	m_Addr=0;
    int nRet=strHexToInt(m_AddrStr,&m_Addr);
	if(nRet==-1)
	{
		return;
	}
	
	PSCloseDevice();

	if(m_DeviceType=="USB")
	{
		if(!PSOpenDevice(DEVICE_USB,0,0))
		{
			AfxMessageBox("No USB Device!");
			return;
		}
	}
    else
	{
		unsigned int m_PackSize;
	    m_PackSize=m_PackSizeCmb.GetCurSel();
		if(!PSOpenDevice(DEVICE_COM,iCom, iBaud,m_PackSize))
		{
			AfxMessageBox("Initialize serial port error！\r\nplease check！");//串口初始化出错
			return;
		}
	}

	//读参数表,必须先验证密码；
    blDeviceOpen = TRUE;
    AfxMessageBox("Initialize device success");//设备初始化成功
	
}
void COPTModuleTestDlg::ShowPara()
{
	int ret;
	unsigned char iParTable[64];
	
	memset(iParTable, 0, 64);
	Sleep(200);
	
	ret = PSReadParTable(m_Addr,iParTable);
	if(ret!=PS_OK)
	{
	 
		return;
	}
	
	CString str;
	CString tmp;
	int i=0;
	
	str = "STATUS=: ";
	tmp.Format("0x%02x",(iParTable[0]<<8)+iParTable[1]);
	str += tmp;
	str += " ";
	
	str += "Sensor type: ";
	tmp.Format("0x%02x",(iParTable[2]<<8)+iParTable[3]);
	str += tmp;
	str += " ";
    
    str += "Library capacity: ";
	tmp.Format("%d",(iParTable[4]<<8)+iParTable[5]);
	str += tmp;
	str += " ";
	
	
	
	str += "Security Level: ";
	tmp.Format("0x%02x",(iParTable[6]<<8)+iParTable[7]);
	str += tmp;
	str += "\r\n";
	
	
	
	str += "Device address: 0x";
	for(i=8; i<8+4; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += " ";
	
	int nPackSize=(iParTable[12]<<8)+iParTable[13];
	
	str += "Package size: ";
	switch(nPackSize)
	{
	case 0:tmp.Format("32 bytes");break;
	case 1:tmp.Format("64 bytes");break;
	case 2:tmp.Format("128 bytes");break;
	case 3:tmp.Format("256 bytes");break;
	default:tmp.Format("error!");
		
	}
	str += tmp;
	str += " ";
	
	str += "Baudrate: ";
	
	int nBaud=(iParTable[14]<<8)+iParTable[15];
	
	tmp.Format("%d bps",nBaud*9600);
	str += tmp;
	m_SysInfo=str;
	UpdateData(FALSE);
}

void COPTModuleTestDlg::OnVfyPwd() 
{
 	UpdateData(TRUE);

	CString sPassword;
	sPassword = m_Pwd;
	if(sPassword.GetLength()!=4)
	{
		AfxMessageBox("Password size error!");
		return;
	}

	unsigned char szStrPwd[4];
	memcpy(szStrPwd, (LPCTSTR)m_Pwd, 4);
	unsigned char iPwd[4];
	unsigned char iHigh;
	for(int i=0;i<4;i++)
	{
		if ((szStrPwd[i]>='0')&&(szStrPwd[i]<='9')) 
			iHigh = szStrPwd[i]-'0';
		else if((szStrPwd[i]>='a')&&(szStrPwd[i]<='f')) 
			iHigh = szStrPwd[i]-'a'+10;
		else if((szStrPwd[i]>='A')&&(szStrPwd[i]<='F')) 
			iHigh = szStrPwd[i]-'A'+10;
		else
		{
			AfxMessageBox("Invalid character in password!");
			return;
		}
		iPwd[i] = iHigh;
	}

	int ret=PSVfyPwd(m_Addr,iPwd);
	if(ret!=PS_OK)
	{
		AfxMessageBox("Password Error!\r\n You have no right to use this module！");
		return;
	}
 
    ShowPara();	
	
    
	AfxMessageBox("Validate password success");	
	
}

void COPTModuleTestDlg::OnSetPwd() 
{
	UpdateData(TRUE);

	CString sPassword;
	sPassword = m_Pwd;
	if(sPassword.GetLength()!=4)
	{
		AfxMessageBox("Password size error");
		return;
	}

	unsigned char szStrPwd[4];
	memcpy(szStrPwd, (LPCTSTR)m_Pwd, 4);
	unsigned char iPwd[4];
	unsigned char iHigh;
	for(int i=0;i<4;i++)
	{
		if ((szStrPwd[i]>='0')&&(szStrPwd[i]<='9')) 
			iHigh = szStrPwd[i]-'0';
		else if((szStrPwd[i]>='a')&&(szStrPwd[i]<='f')) 
			iHigh = szStrPwd[i]-'a'+10;
		else if((szStrPwd[i]>='A')&&(szStrPwd[i]<='F')) 
			iHigh = szStrPwd[i]-'A'+10;
		else
		{
			AfxMessageBox("Invalid character in password!");
			return;
		}
		iPwd[i] = iHigh;
	}

	int ret = PSSetPwd(m_Addr,iPwd);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}

	AfxMessageBox("Set password success!");	
}

void COPTModuleTestDlg::OnSetSecureLevel() 
{
 	UpdateData(TRUE);
	int ret;
	unsigned int m_Level;
	strHexToInt(m_SecureLevel,&m_Level);
	ret = PSSetSecurLevel(m_Addr,m_Level);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	ShowPara();
	str.Format("Set Security Level %d success！", m_Level);
	AfxMessageBox(str);	
}




void COPTModuleTestDlg::OnGDUpImage() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
	int ret;
	ret = PSUpImage(m_Addr,gpImageData,&gnImageSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	 return;
     
	 ret=PSImgData2BMP(gpImageData,"C:\\test.bmp");
	if(ret!=0)
	{
		AfxMessageBox(pFail);
		return;
	}
	ShowBMP(IDC_BITMAP,"C:\\test.bmp");
	AfxMessageBox(pUploadSuccess);//图像上传成功
}

void COPTModuleTestDlg::ShowBMP(int ID, char *szPath)
{
	char szFilePath[MAX_PATH] = {0};
	if(szPath != NULL)
		strcpy(szFilePath, szPath);
	else
		strcpy(szFilePath, "C:\\test.bmp");
    CStatic *pStatic;
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)LoadImage( GetModuleHandle(NULL),szFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap  == NULL)
		hBitmap  = (HBITMAP)LoadImage( NULL,szFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	pStatic=(CStatic *)GetDlgItem( ID );
	pStatic->SetBitmap(hBitmap);//显示图像	
}


void COPTModuleTestDlg::OnGDGetImage2BMP() 
{UpdateData(TRUE);
	int ret=PSImgData2BMP(gpImageData,"C:\\test.bmp");
	if(ret!=0)
	{
		AfxMessageBox(pFail);//失败
		return;
	}
	ShowBMP(IDC_BITMAP,"C:\\test.bmp");
 	
}



void COPTModuleTestDlg::OnDownImage() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}	
	UpdateData(TRUE);
	int ret;
	ret=PSGetImgDataFromBMP("C:\\test.bmp",gpImageData,&gnImageSize)	;
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
//	if(gnImageSize!=IMAGE_X*IMAGE_Y/2)
//	{
//		AfxMessageBox("图像大小不对 ");
//		return;
//	}
	ret = PSDownImage(m_Addr,gpImageData,gnImageSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}

AfxMessageBox(pDownSuccess);  //下传图象成功！	
}

void COPTModuleTestDlg::OnGetImgDataFromBMP() 
{
	UpdateData(TRUE);
	int ret=PSGetImgDataFromBMP("C:\\test.bmp",gpImageData,&gnImageSize)	;
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
}


 

void COPTModuleTestDlg::OnSetBaud() 
{
    UpdateData(TRUE);
	int ret;
	unsigned char chBaud=StrToInt(m_strSetBaud)/9600;
	
	ret = PSSetBaud(m_Addr,chBaud);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	PSCloseDevice();
	if(m_DeviceType=="USB")
	{
		AfxMessageBox("USB can't set baudrate");
		return;
	}
	PSOpenDevice(DEVICE_COM,m_Com.GetCurSel()+1,chBaud);
	CString str;
	SavePara("Baud",m_BaudNum.GetCurSel());
	ShowPara();
	str.Format(" Set baudrate success");
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnReadInfo() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}	
    if (blShowWin)  return;
	UpdateData(TRUE);
	int ret;
	unsigned char iParTable[512];

	memset(iParTable, 0, 256);

	ret = PSReadInfo(m_Addr,m_InfoPage,iParTable);
	if(ret!=PS_OK)
	{
    	AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("%s",iParTable);
 
    if ((pDlg != NULL) && (!blShowWin))
	{
	//	BOOL ret = pDlg->Create(IDD_Content,this);
	//	if (!ret)  AfxMessageBox("Error creating content dialog");		
        
		pDlg->ShowWindow(SW_NORMAL);	
		pDlg->SetActiveWindow();
		//pDlg->GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		pDlg->m_content = iParTable;
		pDlg->UpdateData(FALSE);
		pDlg->GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
		pDlg->m_ok.SetFocus(); 
		blShowWin = TRUE;
	}
    else
	{
		return;
	}
    
//  pDlg->GetDlgItem(IDC_EDIT1)->SetWindowText(str);
 
//	AfxMessageBox(str);
}

void COPTModuleTestDlg::OnWriteInfo() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
//////////////////////////////////////////////////////////////////////////

   if ((pDlg != NULL) && (!blShowWin))
	{
	//	BOOL ret = pDlg->Create(IDD_Content,this);
	//	if (!ret)  AfxMessageBox("Error creating content dialog");		
        
		pDlg->ShowWindow(SW_NORMAL);	 
		pDlg->SetActiveWindow();
		//pDlg->GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	    pDlg->GetDlgItem(IDC_BUTTON2)->ShowWindow(true);
		pDlg->m_content = ""; 
		pDlg->UpdateData(FALSE);
		
		pDlg->GetDlgItem(IDC_EDIT1)->SetFocus(); 
		blShowWin = TRUE;
		
	}
    else
	{
		return;
	}

//////////////////////////////////////////////////////////////////////////
//	memset(iParTable, 0, 64);

// 	AfxMessageBox(str);
}

void COPTModuleTestDlg::OnReadParTable() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
 
	int ret;
	unsigned char iParTable[64];

	memset(iParTable, 0, 64);

	ret = PSReadParTable(m_Addr,iParTable);
	if(ret!=PS_OK)
	{
    	AfxMessageBox( PSErr2Str(ret) );
		return;
	}

	CString str;
	CString tmp;
	int i=0;

	str = "STATUS:              ";
	tmp.Format("0x%02x",(iParTable[0]<<8)+iParTable[1]);
	str += tmp;
	str += "\r\n";

	str += "Sensor Type:       ";
	tmp.Format("0x%02x",(iParTable[2]<<8)+iParTable[3]);
	str += tmp;
	str += "\r\n";
    
    str += "Library Capacity: ";
	tmp.Format("%d",(iParTable[4]<<8)+iParTable[5]);
	str += tmp;
	str += "\r\n";


 
	str += "Security Level:     ";
	tmp.Format("0x%02x",(iParTable[6]<<8)+iParTable[7]);
	str += tmp;
	str += "\r\n";

	

	str += "Device Address:   0x";
	for(i=8; i<8+4; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	int nPackSize=(iParTable[12]<<8)+iParTable[13];

	str += "Package Size:       ";
	switch(nPackSize)
	{
		case 0:tmp.Format("32 bytes");break;
		case 1:tmp.Format("64 bytes");break;
		case 2:tmp.Format("128 bytes");break;
		case 3:tmp.Format("256 bytes");break;
		default:tmp.Format("error!");

	}
	str += tmp;
	str += "\r\n";

	str += "Baudrate:             ";
	
	int nBaud=(iParTable[14]<<8)+iParTable[15];
	
     tmp.Format("%d bps",nBaud*9600);
	 str += tmp;   
 
	AfxMessageBox(str,MB_ICONINFORMATION);	
}

//*************************************************************************
// 指令代码：01H
// 从传感器上读入图像存于图像缓冲区 
//*************************************************************************
	
void COPTModuleTestDlg::OnGDGetImage() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
    int ret;
	ret = PSGetImage(m_Addr);
	if (ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
 	AfxMessageBox(pGetImageSuccess);	
}

//*************************************************************************
//  指令代码：02H
// 	功能：根据原始图像生成指纹特征存于CharBuffer1或CharBuffer2
//*************************************************************************
void COPTModuleTestDlg::OnGenChar() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
 	int ret;
	int iBufferID = 1;
//	unsigned char areaBorder[5]={0};

	iBufferID = m_Buffer.GetCurSel() + 1;
	ret = PSGenChar(m_Addr,iBufferID);
	if (ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
   	CString strBorder;
//	strBorder.Format("图象面积=%d%%\n\r图象上边距=%d，图象下边距=%d，\n\r图象左边距=%d，图象右边距=%d\n\r", areaBorder[0], areaBorder[1], areaBorder[2], areaBorder[3], areaBorder[4]);
	AfxMessageBox("Generate character success");
 
}
//*************************************************************************
// 	指令代码：03H
//  功能：精确比对CharBuffer1与CharBuffer2中的特征文件
//*************************************************************************
void COPTModuleTestDlg::OnMatch() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
 	int ret;
	int m_score;
	ret = PSMatch(m_Addr,&m_score);
	UpdateData(FALSE);

	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("比对命令执行成功！分数为%d",m_score);

	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnSearch() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
 	int ret;
	int nMaxMBNum;
	UpdateData(TRUE);

	unsigned char iParTable[100];
	memset(iParTable, 0, 100);
	
	ret=PSReadParTable(m_Addr,iParTable);

	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	nMaxMBNum = (iParTable[4]<<8)+iParTable[5];


	int iBufferID = 1;

	iBufferID = m_Buffer.GetCurSel() + 1;


	int iMyMb;
	CString msg;
    clock_t finish,start;
	start=clock();
	CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK1);
    
	if (pButton->GetCheck())
	{
		ret = PSSearch(m_Addr,iBufferID, 0, nMaxMBNum, &iMyMb);
	}
	else
	{
		ret = PSSearch(m_Addr,iBufferID, m_DelStart, m_DelNum, &iMyMb);
	}
	
//	ret = PSSearch(m_Addr,iBufferID, 0, nMaxMBNum, &iMyMb);
	finish=clock();
	CString str;
	if(ret!=PS_OK)
	{
		str = PSErr2Str(ret);
		str.Format(str + " , Time consumed:%d MSEL" , finish-start);
		AfxMessageBox(str );
		return;
	}
	
	str.Format("Execute search command success！\r\n Address :%d ,Time consumed:%d MSEL",iMyMb,finish-start);  //搜索命令执行成功
    AfxMessageBox(str);
}

void COPTModuleTestDlg::OnRegModule() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
 	int ret;
	ret = PSRegModule(m_Addr);
	if (ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}

	AfxMessageBox("Templet combined success ！");	
}

void COPTModuleTestDlg::OnStoreChar() 
{
 	int ret;

	UpdateData(TRUE);

	int iBufferID = 1;

	iBufferID = m_Buffer .GetCurSel() + 1;

	ret = PSStoreChar(m_Addr,iBufferID, m_Address);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("Store character success！\r\n Templet is stored on address：%d",m_Address); //特征存储成功
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnLoadChar() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
 	int ret;
	UpdateData(TRUE);

	int iBufferID = 1;

	iBufferID = m_Buffer .GetCurSel() + 1;

	ret = PSLoadChar(m_Addr,iBufferID,m_Address);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("Read character into ModelBuffer success！\r\n Templet address：%d ！", m_Address);
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnDelOneChar() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
 	int ret;
	UpdateData(TRUE);

	ret = PSDelChar(m_Addr,m_DelStart,m_DelNum);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("Delete character success！\r\n Templet address：%d,Templet number：%d",m_DelStart,m_DelNum);
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnEmpty() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
    int ret;
	ret = PSEmpty(m_Addr);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	AfxMessageBox("Clear success！");	
}

void COPTModuleTestDlg::OnUpChar() 
{

	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
 	int ret;
	ret = PSUpChar(m_Addr,m_Buffer.GetCurSel()+1,gTzBuf,&gTzLen);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}

	AfxMessageBox("success！");	
}

void COPTModuleTestDlg::OnDownChar() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}	
	UpdateData(TRUE);
 	int ret;
	ret = PSDownChar(m_Addr,m_Buffer.GetCurSel()+1,gTzBuf,gTzLen);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}

	AfxMessageBox("success！");	

}



void COPTModuleTestDlg::OnSetPktSize() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int ret;
	unsigned int m_PackSize;
	m_PackSize=m_PackSizeCmb.GetCurSel();
 	if((m_PackSize<0)||(m_PackSize>3))
	{
		AfxMessageBox( "Package size error！" );
		return;
	}
	ret = PSSetPacketSize(m_Addr,m_PackSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	SavePara("PackSize",m_PackSize);
	ShowPara();
	CString str;
	str.Format("Package size %d set success！", m_PackSize);
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnGDUpChar2File() 
{
    UpdateData(TRUE);
	int ret;
	CString strFile;
	CFileDialog fo(FALSE,"dat","FingerTz.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"char file(*.dat)|*.dat|all files(*.*)|*.*||",NULL);
	if(fo.DoModal() != IDOK)
		return ;
	strFile = fo.GetFileName();

	ret = PSUpChar2File(m_Addr,m_Buffer.GetCurSel()+1,strFile);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("success！");
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnDownCharFromFile() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
 	UpdateData(TRUE);
	int ret;
	CString strFile;
	CFileDialog fo(TRUE,"dat","FingerTz.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"char file(*.dat)|*.dat|all files(*.*)|*.*||",NULL);
	if(fo.DoModal() != IDOK)
		return ;
	strFile = fo.GetFileName();
	ret = PSDownCharFromFile(m_Addr,m_Buffer.GetCurSel()+1,strFile);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("Download character success！");//特征下载成功
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnSetChipAddr() 
{
	UpdateData(TRUE);
	int ret;
	unsigned char pAddr[4];
	unsigned int nAddr;

    int nRet=strHexToInt(m_AddrStr,&nAddr);
	if(nRet==-1)
	{
		return;
	}
	pAddr[0]=(nAddr>>24)&0xff;
	pAddr[1]=(nAddr>>16)&0xff;
	pAddr[2]=(nAddr>>8)&0xff;
	pAddr[3]=nAddr&0xff;

	ret = PSSetChipAddr(m_Addr,pAddr);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	m_Addr=nAddr;
	char strDir[1024];
	int nLen=GetCurrentDirectory(1024,strDir);
	strcat(strDir,"\\Finger.ini");
 
	::WritePrivateProfileString("Syno Para","Addr",m_AddrStr,strDir);
	ShowPara();
	CString str;
	str.Format("success！");
	AfxMessageBox(str);	
	
}

void COPTModuleTestDlg::OnGetRandomData() 
{
	UpdateData(TRUE);
	int ret;
	int nRandom;
	ret = PSGetRandomData(m_Addr,(unsigned char*)&nRandom);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("success！Random=%08x",nRandom);
	AfxMessageBox(str);	
}

void COPTModuleTestDlg::OnPortControl() 
{
	UpdateData(TRUE);
	int ret;
 
	unsigned int nAddr;
 
	
	ret = PSPortControl(m_Addr,m_bOpen);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	m_Addr=nAddr;
	CString str;
	if(m_bOpen)
		str.Format("Open port success！");
	else
		str.Format("Close port success");
	AfxMessageBox(str);		// TODO: Add your control notification handler code here
	
}

void COPTModuleTestDlg::OnReadInfPage() 
{
	if (!blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	UpdateData(TRUE);
	int ret;
	unsigned char iParTable[512];
	
	memset(iParTable, 0, 512);
	
	ret = PSReadInfPage(m_Addr,iParTable);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	 
	CString tmp;
	int i=0;

	str = "STATUS=: ";
	tmp.Format("0x%02x",(iParTable[0]<<8)+iParTable[1]);
	str += tmp;
	str += "\r\n";

	str += "Sensor Type: ";
	tmp.Format("0x%02x",(iParTable[2]<<8)+iParTable[3]);
	str += tmp;
	str += "\r\n";
    
    str += "Library Capacity: ";
	tmp.Format("%d",(iParTable[4]<<8)+iParTable[5]);
	str += tmp;
	str += "\r\n";



	str += "Security Level: ";
	tmp.Format("0x%02x",(iParTable[6]<<8)+iParTable[7]);
	str += tmp;
	str += "\r\n";

	

	str += "Device Address: 0x";
	for(i=8; i<8+4; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	int nPackSize=(iParTable[12]<<8)+iParTable[13];

	str += "Package Size: ";
	switch(nPackSize)
	{
		case 0:tmp.Format("32 bytes");break;
		case 1:tmp.Format("64 bytes");break;
		case 2:tmp.Format("128 bytes");break;
		case 3:tmp.Format("256 bytes");break;
		default:tmp.Format("error!");

	}
	str += tmp;
	str += "\r\n";

	str += "Baudrate: ";
	
	int nBaud=(iParTable[14]<<8)+iParTable[15];
	
     tmp.Format("%d bps",nBaud*9600);
	    
	str += tmp;
	str += "\r\n";

	str += "Product Type: ";
	for(i=28; i<28+8; i++ )
	{
		tmp.Format("%c",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";
	

    str += "Software Version: ";
	for(i=36; i<36+8; i++ )
	{
		tmp.Format("%c",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	str += "Sensor Name: ";
	for(i=52; i<52+8; i++ )
	{
		tmp.Format("%c",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";
 
	str += "manufacturer: ";  //厂家名称
	for(i=44; i<44+8; i++ )
	{
		tmp.Format("%c",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";
	
	str += "Password: 0x";
	for(i=60; i<60+4; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	str += "JTAG locked label: 0x";    //JTAG锁定标记
	for(i=64; i<64+4; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	str += "Entrance of initialization program: 0x";   //初始化程序入口
	for(i=68; i<68+2; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";

	str += "Entrance of image input : 0x"; // 录入图像入口
	for(i=70; i<70+2; i++ )
	{
		tmp.Format("%02x",iParTable[i]);
		str += tmp;
	}
	str += "\r\n";
	AfxMessageBox(str,MB_ICONINFORMATION);	
}

void COPTModuleTestDlg::OnEnroll() 
{
	UpdateData(TRUE);
	int ret;
	 
	
	ret = PSEnroll(m_Addr,(int*)&m_NewMBID);
	if (ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("Enroll success!user is stored at%d",m_NewMBID);//录入成功!用户存储在
   	AfxMessageBox(str);
}

void COPTModuleTestDlg::OnIdenty() 
{
	int ret;
 
	UpdateData(TRUE);
	
	int iMyMb;
	
	ret = PSIdentify(m_Addr,&iMyMb);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	CString str;
	str.Format("Execute search command success！\r\n Address :%d ",iMyMb);
    AfxMessageBox(str);	 
}

void COPTModuleTestDlg::OnHighSpeedSearch() 
{
	int ret;
	int nMaxMBNum;
	UpdateData(TRUE);
	
	unsigned char iParTable[100];
	memset(iParTable, 0, 100);
	
	ret=PSReadParTable(m_Addr,iParTable);
	
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	nMaxMBNum = (iParTable[4]<<8)+iParTable[5];	
	
	int iBufferID = 1;
	
	iBufferID = m_Buffer.GetCurSel() + 1;
		
	int iMyMb;
	clock_t finish,start;
	start=clock();
	CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK1);
    
	if (pButton->GetCheck())
	{
		ret = PSHighSpeedSearch(m_Addr,iBufferID, 0, nMaxMBNum, &iMyMb);
	}
	else
	{
		ret = PSHighSpeedSearch(m_Addr,iBufferID, m_DelStart, m_DelNum, &iMyMb);
	}
	
	finish=clock();
	CString str;
	if(ret!=PS_OK)
	{
		str = PSErr2Str(ret);
		str.Format(str + " , Time consumed:%d MSEL" , finish-start);
		AfxMessageBox(str);
		return;
	}
	
	str.Format("Execute Highspeed search command success！\r\n Address :%d ,Time consumed:%d MSEL",iMyMb,finish-start);  //搜索命令执行成功

    AfxMessageBox(str);
}

void COPTModuleTestDlg::OnAutoOpen() 
{
	CString sPassword;	
	unsigned char iPwd[4];
	unsigned char iHigh;
	int iCom,nRet;
	unsigned char szStrPwd[4];

	sPassword = m_Pwd;
	if(sPassword.GetLength()!=4)
	{
		AfxMessageBox("Password size error!");
		return;
	}
		
	memcpy(szStrPwd, (LPCTSTR)m_Pwd, 4);

	for(int i=0;i<4;i++)
	{
		if ((szStrPwd[i]>='0')&&(szStrPwd[i]<='9')) 
			iHigh = szStrPwd[i]-'0';
		else if((szStrPwd[i]>='a')&&(szStrPwd[i]<='f')) 
			iHigh = szStrPwd[i]-'a'+10;
		else if((szStrPwd[i]>='A')&&(szStrPwd[i]<='F')) 
			iHigh = szStrPwd[i]-'A'+10;
		else
		{
			AfxMessageBox("Invalid character in password!");
			return;
		}
		iPwd[i] = iHigh;
	}
	
	m_Addr=0;
    nRet=strHexToInt(m_AddrStr,&m_Addr);
	PSCloseDevice();
    if(PSOpenDevice(DEVICE_USB,0,0))
	{    
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;

	}
	 
	iCom = m_Com.GetCurSel()+1;
   
	if(nRet==-1)
	{
		return;
	}
	if(PSOpenDevice(DEVICE_COM,iCom,57600/9600))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;

	}
	PSCloseDevice();
	if(PSOpenDevice(DEVICE_COM,iCom,115200/9600))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;
		
	}
	PSCloseDevice();
	if(PSOpenDevice(DEVICE_COM,iCom,38400/9600))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;
		
	}
	PSCloseDevice();
	if(PSOpenDevice(DEVICE_COM,iCom,19200/9600))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;
		
	}
	PSCloseDevice();
	if(PSOpenDevice(DEVICE_COM,iCom,9600/9600))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) goto OPENOK;
		
	}
	AfxMessageBox("Open device failed，please check password and device address");  //请检查密码和设备地址是否正确
	return;
	
OPENOK:
	ShowPara();
	AfxMessageBox("Open device sucess");
	blDeviceOpen = TRUE;
	 
 
}

void COPTModuleTestDlg::EnableBtn(bool bEnable)
{
	((CButton*)GetDlgItem(IDC_GENTZ))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_TFAR))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_TFRR))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON39))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON40))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_BUTTON41))->EnableWindow(bEnable);
}

void COPTModuleTestDlg::OnSelPath() 
{
	BROWSEINFO bi;            //BROWSEINFO结构体
	TCHAR Buffer[512]="";
	TCHAR FullPath[512]="";
	bi.hwndOwner = m_hWnd;   //m_hWnd你的程序主窗口
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer; //返回选择的目录名的缓冲区
	bi.lpszTitle = "Please select path:"; //弹出的窗口的文字提示
	bi.ulFlags = BIF_RETURNONLYFSDIRS ; //只返回目录。其他标志看MSDN
	bi.lpfn = NULL;                         //回调函数，有时很有用
	bi.lParam = 0;
	bi.iImage = 0;
	ITEMIDLIST* pidl = ::SHBrowseForFolder (&bi); //显示弹出窗口，ITEMIDLIST很重要
	if(::SHGetPathFromIDList (pidl,FullPath))     //在ITEMIDLIST中得到目录名的整个路径
	{
		
		m_Path=FullPath;
		
		UpdateData(false);
	}		// TODO: Add your control notification handler code here
	
}

int COPTModuleTestDlg::OpenDev()
{
	CString sPassword;	
	unsigned char iPwd[4];
	unsigned char iHigh;
	int nRet;
	unsigned char szStrPwd[4];

	sPassword = m_Pwd;
	if(sPassword.GetLength()!=4)
	{
		AfxMessageBox("Password size error!");
		return 0;
	}
	
	memcpy(szStrPwd, (LPCTSTR)m_Pwd, 4);

	for(int i=0;i<4;i++)
	{
		if ((szStrPwd[i]>='0')&&(szStrPwd[i]<='9')) 
			iHigh = szStrPwd[i]-'0';
		else if((szStrPwd[i]>='a')&&(szStrPwd[i]<='f')) 
			iHigh = szStrPwd[i]-'a'+10;
		else if((szStrPwd[i]>='A')&&(szStrPwd[i]<='F')) 
			iHigh = szStrPwd[i]-'A'+10;
		else
		{
			AfxMessageBox("Invalid character in password!");
			return 0;
		}
		iPwd[i] = iHigh;
	}
	
	m_Addr=0;
    nRet=strHexToInt(m_AddrStr,&m_Addr);
	PSCloseDevice();
    if(PSOpenDevice(DEVICE_USB,0,0))
	{ 
		if(PSVfyPwd(m_Addr,iPwd)==PS_OK) return 1;

	}
	 
    return 0;
}
int GetFileCount(CString sDir,char *pExt)
{
	BOOL ans; 
	CFileFind find; 
	int nCnt=0;
	
	ans = find.FindFile(sDir+"\\*.*"); 
	while(ans) 
	{ 
		ans = find.FindNextFile(); // 查找下一个文件 
		// 查找到的如果是目录并且不是 . 或 .. 
		if((find.IsDirectory() == TRUE) && (find.IsDots() != TRUE)) 
		{ 
			continue;
		} 
		
		if(strstr(find.GetFileName(),pExt)!=NULL)
			nCnt++;
	}
	find.Close();
	return nCnt;
}

//拒真测试:0000和0001-0009比对
UINT FRR(LPVOID pParam)
{ 	
	int  ret=1;	
    pMyDlg->EnableBtn(false);		
	gbCancel=false;	
		
	CFileFind find; 
		
	CString sDir;
	int iScore = 0;
	sDir=pMyDlg->m_Path;
    CString sSelf,sOther;
	CFile fp(gSaveFile,CFile::modeCreate|CFile::modeReadWrite);
	
	for(int i=0;i<999;i++)
	{ 
		pMyDlg->m_Progress.SetPos(i);
		if(gbCancel) break;
		for(int j=0;j<10;j++)
		{
            sSelf.Format("%05d%d.dat",i,j);
			if(!find.FindFile(sDir+"\\"+sSelf))	continue;			  
 
		 	pMyDlg->GetDlgItem(IDC_ProgressName)->SetWindowText(sDir + "\\" + sSelf);
			for(int m=j+1;m<10;m++)
			{
				sOther.Format("%05d%d.dat",i,m);
				if(!find.FindFile(sDir+"\\"+sOther)) continue;
				
				ret=PSDownCharFromFile(pMyDlg->m_Addr,CHAR_BUFFER_A,sDir+"\\"+sSelf);
				
				if(ret!=PS_OK) continue;
								
				ret=PSDownCharFromFile(pMyDlg->m_Addr,CHAR_BUFFER_B,sDir+"\\"+sOther);
								
				if(ret!=PS_OK)	continue;
				
				iScore = 0;
				
				ret=PSMatch(pMyDlg->m_Addr,&iScore);
				
				fp.Write(sSelf,sSelf.GetLength());
				fp.Write(" ",1);
				fp.Write(sOther,sOther.GetLength());
				fp.Write(" ",1);
				if(ret==PS_OK)
					fp.Write("OK ",3);
				else
					fp.Write("OK ",3);
				float fs=0;
				if(iScore>=100)
					fs = 1;
				else
					fs = iScore / 100.0;
				CString str;
			str.Format("%.2f",fs);
			fp.Write(str,str.GetLength());
			char ch=0x0D;
			fp.Write(&ch,1);
			ch=0x0A;
			fp.Write(&ch,1);
		 
			}
			
		}
	}
	   
	pMyDlg->m_Progress.SetPos(1000);		
	 
	AfxMessageBox("finish");
	pMyDlg->GetDlgItem(IDC_ProgressName)->SetWindowText("");
    fp.Close();
	find.Close();		
	pMyDlg->EnableBtn(true);
	return 1;
}
 
//认假测试,本身和其它所有的进行比对
UINT TFAR(LPVOID pParam)
{ 
	
	int  ret=1;
	
    pMyDlg->EnableBtn(false);	
	
	gbCancel=false;		
 
	CFileFind find; 
 	
	CString sDir;
	int iScore = 0;
	sDir=pMyDlg->m_Path;
    CString sSelf,sOther;
	CFile fp(gSaveFile,CFile::modeCreate|CFile::modeReadWrite);
	
	for(int i=0;i<1000;i++)
	{ 
		pMyDlg->m_Progress.SetPos(i);
		if(gbCancel) break;
		sSelf.Format("%05d0.dat",i);
		if(!find.FindFile(sDir+"\\"+sSelf)) continue;
  	    pMyDlg->GetDlgItem(IDC_ProgressName)->SetWindowText(sDir + "\\" + sSelf); 
		for(int j=i+1;j<1000;j++)
		{       			 
			sOther.Format("%05d0.dat",j);
			if(!find.FindFile(sDir+"\\"+sOther))	continue; 
			 			
			ret=PSDownCharFromFile(pMyDlg->m_Addr,CHAR_BUFFER_A,sDir+"\\"+sSelf);
			
			if(ret!=PS_OK)	continue;	
			
		    ret=PSDownCharFromFile(pMyDlg->m_Addr,CHAR_BUFFER_B,sDir+"\\"+sOther);
			
			if(ret!=PS_OK)	continue;
						
			iScore = 0;
			
			ret=PSMatch(pMyDlg->m_Addr,&iScore);
			
			fp.Write(sSelf,sSelf.GetLength());
			fp.Write(" ",1);
			fp.Write(sOther,sOther.GetLength());
			fp.Write(" ",1);
			if(ret==PS_OK)
				fp.Write("OK ",3);
			else
				fp.Write("OK ",3);
			float fs=0;
			if(iScore>=100)
				fs=1;
			else
				fs=iScore/100.0;
			CString str;
			str.Format("%.2f",fs);
			fp.Write(str,str.GetLength());
			char ch=0x0D;
			fp.Write(&ch,1);
			ch=0x0A;
			fp.Write(&ch,1);

			
		}
	}
	   
	pMyDlg->m_Progress.SetPos(1000);		
	pMyDlg->GetDlgItem(IDC_ProgressName)->SetWindowText("");
	AfxMessageBox("finish");
	
    fp.Close();
	find.Close();		
	pMyDlg->EnableBtn(true);
	return 1;
}
 
//据真
void COPTModuleTestDlg::OnTFRR() 
{
	UpdateData(TRUE);
	if(!OpenDev())
	{
		AfxMessageBox("Open device error");
		return;
	}
	if(m_Path=="")
	{
		//please select the directory which finger print in
		AfxMessageBox("please select the directory which finger print in!");  //请选择指纹图像所在目录
		return;
	}
	if(GetFileCount(m_Path,".dat")==0)
	{
		AfxMessageBox("No file，Please select path again");
		return;
	} 
	m_Progress.SetRange(0,1000);
	m_Progress.SetPos(0);
	CFileDialog fDlg(FALSE,".txt","FRR.txt");
	if(fDlg.DoModal())
	{
		gSaveFile=fDlg.GetPathName();
	}
	else
		return;
	AfxBeginThread( FRR,NULL );		// TODO: Add your control notification handler code here
	
}
//认假
void COPTModuleTestDlg::OnTFAR() 
{
	UpdateData(TRUE);
	if(!OpenDev())
	{
		AfxMessageBox("Open device error ");
		return;
	}
	if(m_Path=="")
	{
		AfxMessageBox("please select the directory which finger print in!");
		return;
	}
	if(GetFileCount(m_Path,".dat")==0)
	{
		AfxMessageBox("No file，Please select path again");
		return;
	}
	m_Progress.SetRange(0,1000);
	m_Progress.SetPos(0);
	CFileDialog fDlg(FALSE,".txt","FAR.txt");
	if(fDlg.DoModal())
	{
		gSaveFile=fDlg.GetPathName();
	}
	else
		return;
	AfxBeginThread( TFAR,NULL );		// TODO: Add your control notification handler code here
	
}
 
 

void COPTModuleTestDlg::OnTCancel() 
{
	gbCancel=true;
//	EnableBtn(TRUE);	// TODO: Add your control notification handler code here
	
}

//认假测试,本身和其它所有的进行比对
UINT GenTZ(LPVOID pParam)
{ 	
	int  ret=1;
	
    pMyDlg->EnableBtn(false);	
	
	gbCancel=false;	
 
	CFileFind find; 
 
	int nImgLen;
	nImgLen=256*288;  
	
	CString sDir,strs;
 
	sDir=pMyDlg->m_Path;
    CString sSelf,sOther;
	int nErrorNum=0;
 	
	for(int i=0;i<999;i++)
	{ 
		pMyDlg->m_Progress.SetPos(i);
		if(gbCancel) break;
		for(int j=0;j<10;j++)
		{
            sSelf.Format("%05d%d.bmp",i,j);
			if(!find.FindFile(sDir+"\\"+sSelf))
			{
				sSelf.Format("%03d%d.bmp",i,j);
				if(!find.FindFile(sDir+"\\"+sSelf))
				{
					sSelf.Format("%04d%d.bmp",i,j);
					if(!find.FindFile(sDir+"\\"+sSelf))
						continue;
				}
			}			 
		    sOther.Format("%05d%d.dat",i,j);
			
			ret=PSGetImgDataFromBMP(sDir+"\\"+sSelf,gpImageData,&nImgLen);
			
			if(ret!=PS_OK)
			{
				continue;
			}
			
			ret=PSDownImage(pMyDlg->m_Addr,gpImageData,nImgLen);
            if (ret != PS_OK)
			{
				continue;
			}
			
			ret = PSGenChar(pMyDlg->m_Addr,CHAR_BUFFER_A);  //生成模板
			
			if (ret != PS_OK)
			{
				nErrorNum++;
				continue;
			}		
			
		   ret=PSUpChar2File(pMyDlg->m_Addr,CHAR_BUFFER_A,sDir+"\\"+sOther);	 
					   			
		}
	}
	   
	pMyDlg->m_Progress.SetPos(1000);		
	strs.Format("图像特征生成完成，特征文件和图像文件存放在一起，后缀为dat\n特征提取错误数为：%d",nErrorNum);
	AfxMessageBox(strs);
	//AfxMessageBox("图像特征生成完成，特征文件和图像文件存放在一起，后缀为dat\n特征提取错误数为：%d",nErrorNum);
 
	find.Close();		
	pMyDlg->EnableBtn(true);
	return 1;
}
 
void COPTModuleTestDlg::OnGentz() 
{ 
	UpdateData(TRUE);
	if(!OpenDev())
	{
		AfxMessageBox(pOpenError);
		return;
	}
	if(m_Path=="")
	{
		AfxMessageBox("please select the directory which finger print in!");
		return;
	}
	if(GetFileCount(m_Path,".bmp")==0)
	{
		AfxMessageBox("No file，Please select path again");
		return;
	}
 
	m_Progress.SetRange(0,1000);
	m_Progress.SetPos(0);
 
	AfxBeginThread( GenTZ,NULL );		// TODO: Add your control notification handler code here
	
}

void COPTModuleTestDlg::OnBinimg() 
{
	BinImg BinDlg;
	BinDlg.DoModal();
}

void COPTModuleTestDlg::OnISP() 
{
	UpdateData(TRUE);
   CFileDialog fDlg(TRUE);
   if(!fDlg.DoModal()) return;
   CFile fp(fDlg.GetPathName(),CFile::modeRead);
   if(fp==NULL) return;
   unsigned char *pData;
   int nFileSize=fp.GetLength();
   pData=new unsigned char[nFileSize];
   fp.Read(pData,nFileSize);
  	int ret = PSBurnCode(m_Addr,m_ISPType,pData,nFileSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	AfxMessageBox("update online success ");
	
}

void COPTModuleTestDlg::OnTemplateNum() 
{
	int nNum;
	int ret = PSTemplateNum(m_Addr,&nNum);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format("templet number:%d",nNum);
	AfxMessageBox(str);
	
}
 
UINT EnrollLX(LPVOID pParam)
{
	
	int ret;
	int nID;
	CString str;
	pMyDlg->EnableBtn(false);
	while(1)
	{
		if(gbCancel) break;
		pMyDlg->GetDlgItem(IDC_INFO)->SetWindowText("please press finger...");
		
		ret = PSEnroll(pMyDlg->m_Addr,(int*)&nID);
		if (ret!=PS_OK)
		{
			str= PSErr2Str(ret) ;
			
		}
		else	 
			str.Format("Enroll success !user is stored at %d",nID);
		pMyDlg->GetDlgItem(IDC_INFO)->SetWindowText(str);
		Sleep(2000);
	}
	pMyDlg->EnableBtn(true);
	return 1;
	
}

void COPTModuleTestDlg::OnEnrollLX() 
{
	UpdateData(TRUE);
	gbCancel=false;
	if(!OpenDev())
	{
		AfxMessageBox(pOpenError);
		return;
	} 
	AfxBeginThread( EnrollLX,NULL );		// TODO: Add your control notification handler code here	// TODO: Add your control notification handler code here
	
}
UINT IdEntifyLX(LPVOID pParam)
{
	int ret;
	int nID;
	CString str;
	pMyDlg->EnableBtn(false);
	while(1)
	{
		if(gbCancel) break;
		pMyDlg->GetDlgItem(IDC_INFO)->SetWindowText("Please press finger...");
		
		
			ret = PSIdentify(pMyDlg->m_Addr,&nID);
		if (ret!=PS_OK)
		{
			str= PSErr2Str(ret) ;
			
		}
		else	 
			str.Format("User Finded：%d",nID);
		pMyDlg->GetDlgItem(IDC_INFO)->SetWindowText(str);
		Sleep(2000);
	}
	pMyDlg->EnableBtn(true);
	return 1;
}
void COPTModuleTestDlg::OnIdentyLX() 
{
	 
	UpdateData(TRUE);
	gbCancel=false;
	if(!OpenDev())
	{
		AfxMessageBox(pOpenError);
		return;
	}
    
	
	AfxBeginThread( IdEntifyLX,NULL );		// TODO: Add your control notification handler code here	// TODO: Add your control notification handler code here
	
}
UINT DownMBLX(LPVOID pParam)
{ 
	
	int  ret=1;
	
    pMyDlg->EnableBtn(false);	
	
	gbCancel=false;	
	
	
	CFileFind find; 
	
	
	CString sDir;
	int iScore = 0;
	sDir=pMyDlg->m_Path;
    CString sSelf;
 
	int m_Address=0;
	CString strError;
	for(int i=0;i<999;i++)
	{ 
		pMyDlg->m_Progress.SetPos(i);
		if(gbCancel) break;
		for(int j=0;j<10;j++)
		{
            sSelf.Format("%05d%d.dat",i,j);
			if(!find.FindFile(sDir+"\\"+sSelf))
			{
				
				continue;
				
			}
			
			
			ret=PSDownCharFromFile(pMyDlg->m_Addr,CHAR_BUFFER_A,sDir+"\\"+sSelf);
			
			if(ret!=PS_OK)
			{
				continue;
			}
			
			ret = PSStoreChar(pMyDlg->m_Addr,CHAR_BUFFER_A, m_Address);
			if(ret!=PS_OK)
			{
				strError.Format("error：%s,Do you want to continue?",PSErr2Str(ret));
			   if(MessageBox(NULL,strError,"prompt",MB_OKCANCEL)==IDNO)
			   
				   goto DoERROR;
			}
			else
				m_Address++;
			
			
		}
		
	}
 
	   
DoERROR:
	pMyDlg->m_Progress.SetPos(1000);		
	
	AfxMessageBox("finish");
	
  
	find.Close();		
	pMyDlg->EnableBtn(true);
	return 1;
}

void COPTModuleTestDlg::OnDownMBLX() 
{
	UpdateData(TRUE);
	if(!OpenDev())
	{
		AfxMessageBox(pOpenError);
		return;
	}
	if(m_Path=="")
	{
		AfxMessageBox("please select the directory which finger print in!");
		return;
	}
	if(GetFileCount(m_Path,".dat")==0)
	{
		AfxMessageBox("No file，Please select path again");
		return;
	} 
	m_Progress.SetRange(0,1000);
	m_Progress.SetPos(0);
 
	AfxBeginThread( DownMBLX,NULL );		// TODO: Add your control notification handler code here
	
}

HBRUSH COPTModuleTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
   HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
   if(pWnd->GetDlgCtrlID() == IDC_Group2)
   {
      pDC->SetTextColor(RGB(0, 255, 0));
   }
     
  //   TODO:   Return   a   different   brush   if   the   default   is   not   desired   
     return   hbr;    
}

BOOL COPTModuleTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg);   
	return CDialog::PreTranslateMessage(pMsg);
}

void COPTModuleTestDlg::OnCloseWindow() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}

void COPTModuleTestDlg::OnDownCharLib() 
{
	// TODO: Add your control notification handler code here
	CDownCharLib DlgDownChar; 
	DlgDownChar.DoModal();	
}

  
void COPTModuleTestDlg::OnData2BMP() 
{
	// TODO: Add your control notification handler code here
	unsigned char *pBMP;
    int nLen;
	if(PSFingerData2BMPData(NULL,NULL,&nLen)!=PS_OK)
		return ;
	pBMP=new unsigned char[nLen];
	int nRet;
	nRet=PSFingerData2BMPData(gpImageData,pBMP,&nLen);
    delete[] pBMP;
		AfxMessageBox( PSErr2Str(nRet) );
		return;
 
}

void COPTModuleTestDlg::OnShowData() 
{
    unsigned char *pBMP;
    int nLen;
	 
	int nRet;
	nRet=PSShowFingerData(GetDlgItem(IDC_BITMAP)->m_hWnd,gpImageData);
 
		AfxMessageBox( PSErr2Str(nRet) );
		return;	
}
