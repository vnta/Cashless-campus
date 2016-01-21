// Pwd.cpp : implementation file
//

#include "stdafx.h"
#include "GDDemo.h"
#include "Pwd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPwd dialog


CPwd::CPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CPwd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPwd)
	m_Pwd = _T("0000");
	//}}AFX_DATA_INIT
}


void CPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPwd)
	DDX_Text(pDX, IDC_EDIT1, m_Pwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPwd, CDialog)
	//{{AFX_MSG_MAP(CPwd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPwd message handlers
