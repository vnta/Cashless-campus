// User.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "User.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUser dialog


CUser::CUser(CWnd* pParent /*=NULL*/)
	: CDialog(CUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUser)
	m_Addr = 0;
	m_UserInfo = _T("");
	//}}AFX_DATA_INIT
}


void CUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUser)
	DDX_Text(pDX, IDC_EDIT1, m_Addr);
	DDV_MinMaxInt(pDX, m_Addr, 0, 9999);
	DDX_Text(pDX, IDC_EDIT2, m_UserInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUser, CDialog)
	//{{AFX_MSG_MAP(CUser)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUser message handlers

void CUser::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(glangid==0x0804)
	{
		this->SetWindowText("设置用户地址");
		GetDlgItem(IDC_SETTING)->SetWindowText("设置");
		GetDlgItem(IDC_ADDR)->SetWindowText("存放地址");
		GetDlgItem(IDC_USERNAME)->SetWindowText("用户名");
		 
	}
	else
{
		this->SetWindowText("User address");
		GetDlgItem(IDC_SETTING)->SetWindowText("Setting");
		GetDlgItem(IDC_ADDR)->SetWindowText("Address");
		GetDlgItem(IDC_USERNAME)->SetWindowText("UserName");
	}
	
    if(bConEnroll)	
	{
			if(glangid==0x0804)
		GetDlgItem(IDC_ADDR)->SetWindowText("起始地址");
			else
				GetDlgItem(IDC_ADDR)->SetWindowText("Start Address");
		GetDlgItem(IDC_USERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	}
}
