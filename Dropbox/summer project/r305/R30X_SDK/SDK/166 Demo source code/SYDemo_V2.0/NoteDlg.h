#if !defined(AFX_NOTEDLG_H__2C5D95BA_F48D_4C15_B548_CBD0DED6D069__INCLUDED_)
#define AFX_NOTEDLG_H__2C5D95BA_F48D_4C15_B548_CBD0DED6D069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog

class CNoteDlg : public CDialog
{
// Construction
public:
	CNoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoteDlg)
	enum { IDD = IDD_DLG_Note };
	CString	m_note;
	UINT	m_notepage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoteDlg)
	afx_msg void OnChangeNote();
	virtual void OnOK();
	afx_msg void OnChangeEditPage();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEDLG_H__2C5D95BA_F48D_4C15_B548_CBD0DED6D069__INCLUDED_)
