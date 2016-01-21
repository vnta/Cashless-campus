// DLGUSERDEFINE.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "DLGUSERDEFINE.h"

#include "Protocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGUSERDEFINE dialog

extern int nDevAddr;

CDLGUSERDEFINE::CDLGUSERDEFINE(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGUSERDEFINE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGUSERDEFINE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGUSERDEFINE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGUSERDEFINE)
	DDX_Control(pDX, IDC_COMBO2, m_STATE);
	DDX_Control(pDX, IDC_COMBO1, m_GPIO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGUSERDEFINE, CDialog)
	//{{AFX_MSG_MAP(CDLGUSERDEFINE)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnSend)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGUSERDEFINE message handlers

void CDLGUSERDEFINE::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

BOOL CDLGUSERDEFINE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_STATE.SetCurSel(0);
	m_GPIO.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDLGUSERDEFINE::OnSend() 
{
	int iGPIO,iState;
	int ret;
	// TODO: Add your control notification handler code here
	if (m_GPIO.GetCurSel()==0)
	{
		iGPIO = 3;
	}
	else
	{
		iGPIO = 4;
	}
	iState = m_STATE.GetCurSel();
 
	ret = PSDoUserDefine(nDevAddr,iGPIO,iState);
	if (ret!=0)
	{
		AfxMessageBox(PSErr2Str(ret));	 
	}
	else
	{	if(glangid==0x0804)
		AfxMessageBox("发送成功");
	else
		AfxMessageBox("Send success");
	}
}

void CDLGUSERDEFINE::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

		if(glangid==0x0804)
	{
		this->SetWindowText("自定义命令发送");
		GetDlgItem(IDC_BUTTON1)->SetWindowText("发送");
		GetDlgItem(IDC_BUTTON2)->SetWindowText("退出");
		 
	}
	else
{
	this->SetWindowText("Send define command");
		GetDlgItem(IDC_BUTTON1)->SetWindowText("Send");
		GetDlgItem(IDC_BUTTON2)->SetWindowText("Exit");
	}
	
}
