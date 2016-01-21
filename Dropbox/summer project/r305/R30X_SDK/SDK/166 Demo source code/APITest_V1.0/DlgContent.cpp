// DlgContent.cpp : implementation file
//

#include "stdafx.h"
#include "OPTModuleTest.h"
#include "DlgContent.h"
#include "OPTModuleTestDlg.h"
#include "Protocol.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgContent dialog


CDlgContent::CDlgContent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgContent)
	m_content = _T("");
	//}}AFX_DATA_INIT
}


void CDlgContent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgContent)
	DDX_Control(pDX, IDC_BUTTON2, m_write);
	DDX_Control(pDX, IDC_BUTTON1, m_ok);
	DDX_Text(pDX, IDC_EDIT1, m_content);
	DDV_MaxChars(pDX, m_content, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgContent, CDialog)
	//{{AFX_MSG_MAP(CDlgContent)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgContent message handlers

BOOL CDlgContent::PreTranslateMessage(MSG* pMsg) 
{
	CButton *pbtn;
	pbtn = (CButton *)GetDlgItem(IDC_BUTTON2);
	// TODO: Add your specialized code here and/or call the base class
	if ((pMsg->message == WM_KEYDOWN) && ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))) //ÆÁ±Î»Ø³µºÍesc¼ü
	{
		if ((pMsg->wParam == VK_RETURN) && (pbtn->IsWindowVisible()))
		{
			CDlgContent::OnButton2();
		}
		return true;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgContent::OnButton1() 
{
	// TODO: Add your control notification handler code here
   COPTModuleTestDlg *pMain =(COPTModuleTestDlg *)AfxGetMainWnd();  
   pMain->blShowWin = false;
   CDialog::OnOK();
}

void CDlgContent::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
   COPTModuleTestDlg *pMain =(COPTModuleTestDlg *)AfxGetMainWnd();  
   pMain->blShowWin = false;
   CDialog::OnClose();
}

void CDlgContent::OnButton2() 
{
	// TODO: Add your control notification handler code here
	COPTModuleTestDlg *pMain =(COPTModuleTestDlg *)AfxGetMainWnd(); 
	UpdateData(TRUE);
 	int ret;
	unsigned char iParTable[256]={0};//="our test info...";
	strcpy((char*)iParTable,m_content);

	ret = PSWriteInfo(pMain->m_Addr,pMain->m_InfoPage,iParTable);
	if(ret!=PS_OK)
	{
    	AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	CString str;
	str.Format(pWriteSuccess);
	AfxMessageBox(str);
	pMain->blShowWin = false;
	CDialog::OnOK();
}
