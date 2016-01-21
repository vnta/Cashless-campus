#if !defined(AFX_RNOTEDLG_H__BD40E1A6_726C_43BB_BD5C_7EC5D16D241D__INCLUDED_)
#define AFX_RNOTEDLG_H__BD40E1A6_726C_43BB_BD5C_7EC5D16D241D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RNoteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRNoteDlg dialog

class CRNoteDlg : public CDialog
{
// Construction
public:
	CRNoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRNoteDlg)
	enum { IDD = IDD_DLG_RNote };
	UINT	m_notepage;
	CString	m_note;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRNoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRNoteDlg)
	afx_msg void OnChangeEditPage();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RNOTEDLG_H__BD40E1A6_726C_43BB_BD5C_7EC5D16D241D__INCLUDED_)
