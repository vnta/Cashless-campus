// RNoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "Protocol.h"
#include "RNoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRNoteDlg dialog


CRNoteDlg::CRNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRNoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRNoteDlg)
	m_notepage = 0;
	m_note = _T("");
	//}}AFX_DATA_INIT
}


void CRNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRNoteDlg)
	DDX_Text(pDX, IDC_EDIT_PAGE, m_notepage);
	DDV_MinMaxUInt(pDX, m_notepage, 0, 16);
	DDX_Text(pDX, IDC_Note, m_note);
	DDV_MaxChars(pDX, m_note, 96);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRNoteDlg, CDialog)
	//{{AFX_MSG_MAP(CRNoteDlg)
	ON_EN_CHANGE(IDC_EDIT_PAGE, OnChangeEditPage)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRNoteDlg message handlers

void CRNoteDlg::OnChangeEditPage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_notepage < 0 || m_notepage > 16)
	{
		m_notepage = 0;
		UpdateData(FALSE);		
	}
	
}
/*
void CRNoteDlg::OnBtnShownote() 
{
	// TODO: Add your control notification handler code here
	
	unsigned char UserContent[32];
	
	UpdateData(TRUE);
	if(m_notepage < 0 || m_notepage > 16)
	{
		if(glangid==0x0804)
			AfxMessageBox("页码非法!");
		else
			AfxMessageBox("Pate is error!");
		return;
	}
	
	读记事本
	if( PSReadInfo(nDevAddr,(m_notepage),UserContent) != PS_OK)
	{
	AfxMessage("读记事本失败!");
	return ;
	}
	memset(UserContent,255,32);
	//显示记事本内容
	CString strTemp;
	m_note = "";
	for(int i=0; i<32; i++)
	{
		strTemp.Format("%02x ",UserContent[i]);
		m_note = m_note + strTemp;
	}
	UpdateData(FALSE);
}*/
void CRNoteDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(glangid==0x0804)
	{
		this->SetWindowText("读记事本");
		GetDlgItem(IDC_PAGE)->SetWindowText("页码");
		GetDlgItem(IDOK)->SetWindowText("显示");
		GetDlgItem(IDCANCEL)->SetWindowText("退出");
	}
	else
	{
		this->SetWindowText("Read notepad");
		GetDlgItem(IDC_PAGE)->SetWindowText("Page");
		GetDlgItem(IDOK)->SetWindowText("Show");
		GetDlgItem(IDCANCEL)->SetWindowText("Exit");
	}
}
extern int nDevAddr;
void CRNoteDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	unsigned char UserContent[32];
	
	UpdateData(TRUE);
	if(m_notepage < 0 || m_notepage > 16)
	{
		if(glangid==0x0804)
			AfxMessageBox("页码非法!");
		else
			AfxMessageBox("Pate is error!");
		return;
	}
	memset(UserContent,255,32);
		//读记事本
		if( PSReadInfo(nDevAddr,m_notepage,UserContent) != PS_OK)
		{
			if(glangid==0x0804)
				AfxMessageBox("读记事本失败！",RGB(255,0,0));
			else
				AfxMessageBox("Fail to read notepad",RGB(255,0,0));
			return ;
		}//*/
 
	
	//显示记事本内容
	CString strTemp;
	m_note = "";
	for(int i=0; i<32; i++)
	{
		strTemp.Format("%02x ",UserContent[i]);
		m_note = m_note + strTemp;
	}
	UpdateData(FALSE);
}
