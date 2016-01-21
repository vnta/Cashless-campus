#if !defined(AFX_USER_H__C44FB35C_B3DF_4F3D_B2A2_38DECDED6BD6__INCLUDED_)
#define AFX_USER_H__C44FB35C_B3DF_4F3D_B2A2_38DECDED6BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// User.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUser dialog

class CUser : public CDialog
{
// Construction
public:
	CUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUser)
	enum { IDD = IDD_DLGUSER };
	int		m_Addr;
	CString	m_UserInfo;
	bool bConEnroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUser)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USER_H__C44FB35C_B3DF_4F3D_B2A2_38DECDED6BD6__INCLUDED_)
