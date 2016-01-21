// DownCharLib.cpp : implementation file
//

#include "stdafx.h"
#include "OPTModuleTest.h"
#include "DownCharLib.h"
#include "OPTModuleTestDlg.h"
#include "Protocol.h"
#include "PathDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownCharLib dialog

static unsigned char gCharBuf[1024];
static int gCharLen;

CDownCharLib::CDownCharLib(CWnd* pParent /*=NULL*/)
	: CDialog(CDownCharLib::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownCharLib)
	m_TempId = 0;
	m_DownTimes = 0;
	m_PathTempId = 0;
	//}}AFX_DATA_INIT
}


void CDownCharLib::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownCharLib)
	DDX_Text(pDX, IDC_EDIT2, m_TempId);
	DDV_MinMaxInt(pDX, m_TempId, 0, 999);
	DDX_Text(pDX, IDC_EDIT13, m_DownTimes);
	DDV_MinMaxInt(pDX, m_DownTimes, 0, 999);
	DDX_Text(pDX, IDC_EDIT12, m_PathTempId);
	DDV_MinMaxInt(pDX, m_PathTempId, 0, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDownCharLib, CDialog)
	//{{AFX_MSG_MAP(CDownCharLib)
	ON_BN_CLICKED(IDC_BUTTON2, OnSelectPath)
	ON_BN_CLICKED(IDC_BUTTON4, OnSelectPath1)
	ON_BN_CLICKED(IDC_BUTTON1, OnLoopDown)
	ON_BN_CLICKED(IDC_BUTTON44, OnPathDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownCharLib message handlers

void CDownCharLib::OnSelectPath() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strPath;
 
	CFileDialog fo(TRUE,"Dat","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"位图文件(*.Dat)|*.Dat|所有文件(*.*)|*.*||",NULL);
	 
	if(fo.DoModal() != IDOK)
		return ;
	strFile = fo.GetFileName();
	strPath = fo.GetPathName();
	SetDlgItemText(IDC_EDIT1,strPath);

    CFile file(strPath,CFile::modeRead);
 
	gCharLen = file.GetLength();

	if (gCharLen > 1024 ) 
	{
		AfxMessageBox("file size must small than 1024");
		file.Close();
		return;
	}
	
	file.Read(gCharBuf,gCharLen);
	file.Close();
}

void CDownCharLib::OnSelectPath1() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strPath;
	CPathDialog pd("浏览文件夹","请选择一个文件夹","c:\\",NULL);
	if(pd.DoModal()!=IDOK)
		return;
	strPath = pd.GetPathName();
	SetDlgItemText(IDC_EDIT11,strPath);
 
	
 
 
}

void CDownCharLib::OnLoopDown() 
{
	// TODO: Add your control notification handler code here

	COPTModuleTestDlg *pTestDlg = (COPTModuleTestDlg*)AfxGetMainWnd();
	if (!pTestDlg->blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
			
	UpdateData(TRUE);
	CString tmp;
	GetDlgItemText(IDC_EDIT1,tmp);
	if (tmp.IsEmpty())
	{
		AfxMessageBox("Please open a char file first");
		return;
	}
 

 	int ret;
	for (int i = 0; i< m_DownTimes; i++)
	{
		ret = PSDownChar(pTestDlg->m_Addr,1,gCharBuf,gCharLen);
		
		if(ret!=PS_OK)
		{
			AfxMessageBox( PSErr2Str(ret) );
			return;
		}
		ret = PSStoreChar(pTestDlg->m_Addr,1, m_TempId++);
		if(ret!=PS_OK)
		{
			AfxMessageBox( PSErr2Str(ret) );
			return;
		}

	}

	AfxMessageBox("all down success");
 	
}

BOOL CDownCharLib::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ZeroMemory(gCharBuf,1024);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDownCharLib::OnPathDown() 
{
	// TODO: Add your control notification handler code here
	COPTModuleTestDlg *pTestDlg = (COPTModuleTestDlg*)AfxGetMainWnd();

	if (!pTestDlg->blDeviceOpen)
	{
		AfxMessageBox("Please open device first");
		return;
	}
	
	UpdateData(TRUE);
	CString tmp;
	GetDlgItemText(IDC_EDIT11,tmp);

	if (tmp.IsEmpty())
	{
		AfxMessageBox("Please open a char file first");
		return;
	}
 
	BrowseDir(tmp);
	AfxMessageBox("all down success");
 	
}

void CDownCharLib::BrowseDir(CString strDir)
{
	CFileFind ff;
	CString szDir = strDir;
	HTREEITEM	hSubItem;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	COPTModuleTestDlg *pTestDlg = (COPTModuleTestDlg*)AfxGetMainWnd();	

	UpdateData(TRUE);


	BOOL res = ff.FindFile(szDir);
	while( res )
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			CString strPath = ff.GetFilePath();
			CString strTitle = ff.GetFileTitle();

			BrowseDir( strPath );
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			CString strTitle = ff.GetFileName();
			CString strPath = ff.GetFilePath();
			
			CString tmp(strTitle.Right(4));
			tmp.MakeLower();
            if (tmp==".dat")   //是dat文件
            {
				
				CFile file(strPath,CFile::modeRead);
				gCharLen = file.GetLength();
				if (gCharLen > 1024 ) 
				{
					AfxMessageBox("file size must small than 1024");
					file.Close();
					return;
				}
				file.Read(gCharBuf,file.GetLength());
				gCharLen = file.GetLength();
				
				int ret;				
				ret = PSDownChar(pTestDlg->m_Addr,1,gCharBuf,gCharLen);
				if(ret!=PS_OK)
				{
					AfxMessageBox( PSErr2Str(ret) );
					return;
				}
				ret = PSStoreChar(pTestDlg->m_Addr,1, m_PathTempId++);
				if(ret!=PS_OK)
				{
					AfxMessageBox( PSErr2Str(ret) );
					return;
				}
				file.Close();
            }
			
			 
		}
	}
	ff.Close();
}
