#if !defined(AFX_PWD_H__BADDB2ED_6E45_4A4E_84A4_6CEB68F77FCA__INCLUDED_)
#define AFX_PWD_H__BADDB2ED_6E45_4A4E_84A4_6CEB68F77FCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPwd dialog

class CPwd : public CDialog
{
// Construction
public:
	CPwd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPwd)
	enum { IDD = IDD_DLGPWD};
	CString	m_Pwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPwd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PWD_H__BADDB2ED_6E45_4A4E_84A4_6CEB68F77FCA__INCLUDED_)
