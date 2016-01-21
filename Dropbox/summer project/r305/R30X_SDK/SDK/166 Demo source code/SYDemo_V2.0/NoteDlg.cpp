// NoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "NoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog


CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNoteDlg)
	m_note = _T("");
	m_notepage = 0;
	//}}AFX_DATA_INIT
}


void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoteDlg)
	DDX_Text(pDX, IDC_Note, m_note);
	DDV_MaxChars(pDX, m_note, 96);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_notepage);
	DDV_MinMaxUInt(pDX, m_notepage, 0, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialog)
	//{{AFX_MSG_MAP(CNoteDlg)
	ON_EN_CHANGE(IDC_Note, OnChangeNote)
	ON_EN_CHANGE(IDC_EDIT_PAGE, OnChangeEditPage)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg message handlers

void CNoteDlg::OnChangeNote() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char noteList[100];
	int lenNote = m_note.GetLength();
	int i;
	char a;
	strcpy(noteList,(char*)(LPCSTR)m_note);
	for(i=0; i<lenNote; i++)
	{
		a = noteList[i];
		if( (a >= '0' && a <= '9')	//判断是否是非法字符
//			|| (a >= 'A' && a <= 'F') 
//			|| (a >= 'a' && a <= 'g') 
			|| ( a == ' ' || a == '-' || a==',' ) )	//检测非法字符
			continue;
		m_note = m_note.Left(i) + m_note.Right(lenNote-1-i);	//把非法字符删掉
		UpdateData(FALSE);
		//设置光标在的n个字符后面
		CEdit   *pEdit   =   (CEdit*)GetDlgItem(IDC_Note);   
		pEdit->SetSel(i,i);   
		break;
	}	
}



void CNoteDlg::OnOK() 
{
	// TODO: Add extra validation here
	//格式转换
	UpdateData(TRUE);
	char seps[]   = " ,-";
	char *token;
	char buf[20];
	int noteLen  = m_note.GetLength();
	token = strtok(m_note.GetBuffer(noteLen), seps );

	int iCount = 1;
    strcpy(buf,token);
	if (atoi(buf)>255)
	{
		   CString sCount;
		   sCount.Format("%d",iCount);
		   	if(glangid==0x0804)
		   AfxMessageBox("第"+sCount +"个数字大于255，请重新输入");
			else
				AfxMessageBox("The number of "+sCount+ " > 255 ,Please reinput!");
		   return;
	}  

	while( token != NULL )
    {
      /* While there are tokens in "string" */
	   
       strcpy(buf,token);
	   if (atoi(buf)>255)
	   {
		   CString sCount;
		   sCount.Format("%d",iCount);
		   	if(glangid==0x0804)
		   AfxMessageBox("第"+sCount +"个数字大于255，请重新输入");
			else
				AfxMessageBox("The number of "+sCount+ " > 255 ,Please reinput!");
	 
		   return;
	   }  
       token = strtok( NULL, seps );
	   iCount++;
	}
	CDialog::OnOK();
}

void CNoteDlg::OnChangeEditPage() 
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


void CNoteDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(glangid==0x0804)
	{
		this->SetWindowText("写记事本");
		GetDlgItem(IDC_PAGE)->SetWindowText("页码");
		GetDlgItem(IDOK)->SetWindowText("保存");
		GetDlgItem(IDCANCEL)->SetWindowText("退出");
	}
	else
	{
		this->SetWindowText("Write notepad");
		GetDlgItem(IDC_PAGE)->SetWindowText("Page");
		GetDlgItem(IDOK)->SetWindowText("Save");
		GetDlgItem(IDCANCEL)->SetWindowText("Exit");
	}
	
}
