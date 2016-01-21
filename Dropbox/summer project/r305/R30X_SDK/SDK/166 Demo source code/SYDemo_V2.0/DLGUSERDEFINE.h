#if !defined(AFX_DLGUSERDEFINE_H__CE86464C_7DF9_4FA2_9BBD_120363F90679__INCLUDED_)
#define AFX_DLGUSERDEFINE_H__CE86464C_7DF9_4FA2_9BBD_120363F90679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGUSERDEFINE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGUSERDEFINE dialog

class CDLGUSERDEFINE : public CDialog
{
// Construction
public:
	CDLGUSERDEFINE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGUSERDEFINE)
	enum { IDD = IDD_USERDEFINE };
	CComboBox	m_STATE;
	CComboBox	m_GPIO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGUSERDEFINE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGUSERDEFINE)
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnSend();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERDEFINE_H__CE86464C_7DF9_4FA2_9BBD_120363F90679__INCLUDED_)
