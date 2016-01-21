// DlgFingerDB.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "DlgFingerDB.h"

#include "pathdialog.h"
#include "GDDemoDlg.h"
#include "protocol.h"

#include <shlwapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	  IMAGE_SIZE (256*288)
CDlgFingerDB *pFingerDBDlg;
//CGDDemoDlg *pDemoDlg;
extern nDevAddr;
extern TCHAR szUserLogoPath[255];
/////////////////////////////////////////////////////////////////////////////
// CDlgFingerDB dialog



CDlgFingerDB::CDlgFingerDB(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFingerDB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFingerDB)
	m_NumPFin = 5;
	m_Path = _T("c:\\");
	m_RunNum = _T("000000");
	m_SinNum = _T("000000");
	
	//}}AFX_DATA_INIT

}
 
void CDlgFingerDB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFingerDB)
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Text(pDX, IDC_EDIT_NUMPFIN, m_NumPFin);
	DDV_MinMaxInt(pDX, m_NumPFin, 1, 10);
	DDX_Text(pDX, IDC_EDIT_PATH, m_Path);
	DDX_Text(pDX, IDC_EDIT_RUN_NUM, m_RunNum);
	DDX_Text(pDX, IDC_EDIT_SIG_NUM, m_SinNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFingerDB, CDialog)
	//{{AFX_MSG_MAP(CDlgFingerDB)
	ON_BN_CLICKED(IDC_BTN_GETPATH, OnBtnGetpath)
	ON_BN_CLICKED(IDC_BTN_RUN, OnBtnRun)
	ON_BN_CLICKED(IDC_BTN_CANCEL_RUN, OnBtnCancelRun)
	ON_BN_CLICKED(IDC_BTN_SIG, OnBtnSig)
	ON_BN_CLICKED(IDC_BTN_CANCEL_SIG, OnBtnCancelSig)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFingerDB message handlers

void CDlgFingerDB::OnBtnGetpath() 
{
	// TODO: Add your control notification handler code here
	CString str1,str2;
		if(glangid==0x0804)
		{
			str1="浏览文件夹";
			str2="请选择一个文件夹";
		}
		else
		{
			str1="Browse folder";
			str2="Please select a folder";
		}
	CPathDialog pd(str1,str2,"c:\\",NULL);
	if(pd.DoModal()!=IDOK)
		return;
	SetDlgItemText(IDC_EDIT_PATH,pd.GetPathName());
}

void CDlgFingerDB::OnBtnRun() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	UpdateData(TRUE);

	if(m_NumPFin<0 || m_NumPFin>10 )
	{
			if(glangid==0x0804)
		AfxMessageBox("请输入正确的样本个数！");
			else
				AfxMessageBox("Please the correct number");
		return ;
	}
	if( m_Path == "")
	{
			if(glangid==0x0804)
		AfxMessageBox("请输入正确的指纹库目录！");
			else
				AfxMessageBox("Please select a fingerprint folder!");
		return;
	}
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_RUN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_SIG))->EnableWindow(FALSE);
	
	IsStopRun = FALSE;

	
 	AfxBeginThread( RunGenImg,NULL);
    
 
}

UINT RunGenImg(LPVOID pParam)
{	

	
	int FingerCode;	//手指编码
	int	SerialCode;	//用一个手指的序号编码
//	EnterCriticalSection(&);
//	pFingerDBDlg->CriticalSection.Lock();
 	while(!pFingerDBDlg->IsStopRun)
	{	
	    
		SerialCode = 1;
		 
		//计算需要保存的图像绝对路径
		
		SerialCode = atoi(pFingerDBDlg->m_RunNum)%10;
  		FingerCode = atoi(pFingerDBDlg->m_RunNum)/10;
		if(SerialCode < 0 || SerialCode > pFingerDBDlg->m_NumPFin)
		{
				if(glangid==0x0804)
			AfxMessageBox("错误的图像编号");
				else
					AfxMessageBox("The image number is error!");
			return 0;
		}
		
		pFingerDBDlg->gstrFileName.Format("%s\\%s.bmp",pFingerDBDlg->m_Path,pFingerDBDlg->m_RunNum);
		SerialCode ++; 
		if(pFingerDBDlg->GetImage()==0)
			return 0;
 		if(pFingerDBDlg->IsStopRun)
    		return 0;
	 
		if(SerialCode == pFingerDBDlg->m_NumPFin)
		{
			SerialCode = 0;
			FingerCode ++;	
			CString sSel;
				if(glangid==0x0804)
					sSel="请换手指！";
				else
				sSel="Please change a finger";

			if(AfxMessageBox(sSel,MB_OKCANCEL) == IDCANCEL)
				return 0;
		}
		
 		pFingerDBDlg->m_RunNum.Format("%05d%d",FingerCode,SerialCode);
		pFingerDBDlg->SetDlgItemText(IDC_EDIT_RUN_NUM,pFingerDBDlg->m_RunNum);

	}
//	pFingerDBDlg->CriticalSection.Unlock();

	return 1;
}

void CDlgFingerDB::OnBtnCancelRun() 
{
	// TODO: Add your control notification handler code here
	IsStopRun = TRUE;
}

void CDlgFingerDB::OnBtnCancelSig() 
{
	// TODO: Add your control notification handler code here
	IsStopRun = TRUE;	
}

void CDlgFingerDB::OnBtnSig() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	if( m_Path == "")
	{
			if(glangid==0x0804)
		AfxMessageBox("请输入正确的指纹库目录！");
			else
				AfxMessageBox("Please select a fingerprint folder");
		return;
	}
	//需要保存的图像绝对路径
	gstrFileName.Format("%s\\%s.bmp",m_Path,m_SinNum);
	
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_RUN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_SIG))->EnableWindow(TRUE);

	IsStopRun = FALSE;
	
	AfxBeginThread( SigGenImg,NULL);

}

UINT SigGenImg(LPVOID pParam)
{	
	return pFingerDBDlg->GetImage();
}

int CDlgFingerDB::GetImage() 
{ 
	/*/for test
	{
		unsigned char ImgData[IMAGE_SIZE]; 
		for(int j=0; j<10; j++)
		{
			if(IsStopRun)
			{
				EnableBtn(true);
				return 0;
			}
			Sleep(100);
		}
		Sleep(100);	
		PSImgData2BMP(ImgData,gstrFileName);
		EnableBtn(true);
		return 1;
	}//*/

	////////////////////////////////////////////////
	int ret,i=0;
	int ImgLen;
	unsigned char ImgData[IMAGE_SIZE]; 

		
	EnableBtn(false);
//	ShowDefaltImg();   //2007 kzf
//	ShowInfo("请将手指平放在传感器上...");
	
	IsStopRun=FALSE;
	ret = PSGetImage(nDevAddr);  //获取图象  
	
	while(ret==PS_NO_FINGER)
	{
		ret=PSGetImage(nDevAddr);
		if(IsStopRun)
		{
			EnableBtn(true);
			return 0;
		}
	}
	
	if(ret!=PS_OK)
	{
//		ShowInfo( PSErr2Str(ret) );
		AfxMessageBox( PSErr2Str(ret) );
		EnableBtn(true);
		return 0;
	}
	
//	ShowInfo("图像正在上传...");
	
	ret = PSUpImage(nDevAddr,ImgData,&ImgLen);  //上传图象
	
	if(ret!=PS_OK)
	{
//		ShowInfo( PSErr2Str(ret) );
		AfxMessageBox( PSErr2Str(ret) );
		EnableBtn(true);
		return 0;
	}
	
	ret= PSImgData2BMP(ImgData,gstrFileName);
	
    if(ret!=PS_OK)
	{
//		ShowInfo( PSErr2Str(ret) );
		AfxMessageBox( PSErr2Str(ret) );
		EnableBtn(true);
		return 0;
	}
	
	ShowImage();
	
//	ShowInfo("图像录入成功!");	
	
	EnableBtn(true);
	return 1;
}

void CDlgFingerDB::EnableBtn(BOOL bEnable)
{
 	((CButton*)GetDlgItem(IDC_BTN_SIG))->EnableWindow(bEnable);
    ((CButton*)GetDlgItem(IDC_BTN_RUN))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDCANCEL))->EnableWindow(bEnable);
}

void CDlgFingerDB::ShowDefaltImg() 
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

void CDlgFingerDB::ShowImage() 
{
	// TODO: Add your control notification handler code here
	

	HBITMAP hBitmapFP = (HBITMAP)LoadImage( GetModuleHandle(NULL),(LPCTSTR)gstrFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmapFP  == NULL)
		hBitmapFP  = (HBITMAP)LoadImage( NULL,(LPCTSTR)gstrFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
   ((CStatic*)GetDlgItem(IDC_IMAGE))->SetBitmap(hBitmapFP);
	DeleteObject(hBitmapFP);
	
}

BOOL CDlgFingerDB::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
 	pFingerDBDlg = this;
	 
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_SIG))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BTN_CANCEL_RUN))->EnableWindow(FALSE);
    IsStopRun=FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFingerDB::OnCancel() 
{
	// TODO: Add extra cleanup here
   
//   CriticalSection.Lock();
//   IsStopRun=true;  
//   CriticalSection.Unlock();
   
//   EnterCriticalSection(&CriticalSection)  ;
   CDialog::OnCancel();
}

void CDlgFingerDB::OnButton1() 
{
	// TODO: Add your control notification handler code here

}

void CDlgFingerDB::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    if (!IsStopRun)
    {
		ShowDefaltImg(); 
    }
    
 
		
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgFingerDB::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
		if(glangid==0x0804)
		{
			this->SetWindowText("采集样本");
             GetDlgItem(IDC_FINGERNUM)->SetWindowText("每根手指样本个数:");
             GetDlgItem(IDC_FINGERPATH)->SetWindowText("指纹库目录:");
			 GetDlgItem(IDC_BTN_GETPATH)->SetWindowText("选择路径");
			 GetDlgItem(IDC_GETIMAGCON)->SetWindowText("连续采集图像");
			 GetDlgItem(IDC_IMAGENUM1)->SetWindowText("图像编号");
			 GetDlgItem(IDC_IMAGENUM2)->SetWindowText("图像编号");
			 GetDlgItem(IDC_BTN_RUN)->SetWindowText("开始采集");

			 GetDlgItem(IDC_BTN_CANCEL_RUN)->SetWindowText("取消");
             GetDlgItem(IDC_GETONE)->SetWindowText("采集单枚图像");
			 GetDlgItem(IDC_BTN_SIG)->SetWindowText("采集");
			 GetDlgItem(IDC_BTN_CANCEL_SIG)->SetWindowText("取消");
			 GetDlgItem(IDCANCEL)->SetWindowText("退出");
			 
		}
		else
			{
			this->SetWindowText("Capture fingerprint");
             GetDlgItem(IDC_FINGERNUM)->SetWindowText("Number of one finger:");
             GetDlgItem(IDC_FINGERPATH)->SetWindowText("Fingerprint folder:");
			 GetDlgItem(IDC_BTN_GETPATH)->SetWindowText("Path");
			 GetDlgItem(IDC_GETIMAGCON)->SetWindowText("Continuous Capture");
			 GetDlgItem(IDC_IMAGENUM1)->SetWindowText("Number");
			 GetDlgItem(IDC_IMAGENUM2)->SetWindowText("Number");
			 GetDlgItem(IDC_BTN_RUN)->SetWindowText("Capture");

			 GetDlgItem(IDC_BTN_CANCEL_RUN)->SetWindowText("Cancel");
             GetDlgItem(IDC_GETONE)->SetWindowText("Capture one");
			 GetDlgItem(IDC_BTN_SIG)->SetWindowText("Capture");
			 GetDlgItem(IDC_BTN_CANCEL_SIG)->SetWindowText("Cancel");
			 GetDlgItem(IDCANCEL)->SetWindowText("Exit");
			 
		}
}
