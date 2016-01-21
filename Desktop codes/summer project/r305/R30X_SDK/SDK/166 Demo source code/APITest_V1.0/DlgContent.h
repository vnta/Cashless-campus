#if !defined(AFX_DLGCONTENT_H__A950ED30_FCDD_471C_B6E3_EB606B3B2092__INCLUDED_)
#define AFX_DLGCONTENT_H__A950ED30_FCDD_471C_B6E3_EB606B3B2092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgContent dialog

class CDlgContent : public CDialog
{
// Construction
public:
	CDlgContent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgContent)
	enum { IDD = IDD_Content };
	CButton	m_write;
	CButton	m_ok;
	CString	m_content;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgContent)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgContent)
	afx_msg void OnButton1();
	afx_msg void OnClose();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTENT_H__A950ED30_FCDD_471C_B6E3_EB606B3B2092__INCLUDED_)
