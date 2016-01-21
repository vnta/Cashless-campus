// Com.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "Com.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCom dialog


CCom::CCom(CWnd* pParent /*=NULL*/)
	: CDialog(CCom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCom)
 
 
	//}}AFX_DATA_INIT
}


void CCom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCom)
 
	DDX_Control(pDX, IDC_COMBO1, m_Com);
 
 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCom, CDialog)
	//{{AFX_MSG_MAP(CCom)
 ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCom message handlers

void CCom::OnOK() 
{
    
	
	nCom=m_Com.GetCurSel()+1;
    
	CDialog::OnOK();
}

BOOL CCom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Com.SetCurSel(0);
 
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 
void CCom::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(glangid==0x0804)
	{
		this->SetWindowText("打开设备");
		GetDlgItem(IDC_SETTING)->SetWindowText("设置串口参数");
		GetDlgItem(IDC_COM)->SetWindowText("串口号:");
	 
		 
	}
	else
{
			this->SetWindowText("Open Device");
		GetDlgItem(IDC_SETTING)->SetWindowText("Select COM");
		GetDlgItem(IDC_COM)->SetWindowText("COM:");
	}
	
     
}
