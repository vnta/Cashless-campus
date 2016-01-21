#if !defined(AFX_DLGFINGERDB_H__0DE32708_2FF9_4DE1_BA26_31274EA8AFDD__INCLUDED_)
#define AFX_DLGFINGERDB_H__0DE32708_2FF9_4DE1_BA26_31274EA8AFDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFingerDB.h : header file
//

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CDlgFingerDB dialog

class CDlgFingerDB : public CDialog
{
public:
	void ShowDefaltImg(); 
	void ShowImage(); 
	void EnableBtn(BOOL bEnable);
	int  GetImage();
	BOOL IsStopRun;
	CString gstrFileName;
	CCriticalSection CriticalSection;	
// Construction
public:
	CDlgFingerDB(CWnd* pParent = NULL);   // standard constructor
    
// Dialog Data
	//{{AFX_DATA(CDlgFingerDB)
	enum { IDD = IDD_DLG_FingerDB };
	CStatic	m_image;
	int		m_NumPFin;
	CString	m_Path;
	CString	m_RunNum;
	CString	m_SinNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFingerDB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFingerDB)
	afx_msg void OnBtnGetpath();
	afx_msg void OnBtnRun();
	afx_msg void OnBtnCancelRun();
	afx_msg void OnBtnSig();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCancelSig();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
UINT RunGenImg(LPVOID pParam);
UINT SigGenImg(LPVOID pParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFINGERDB_H__0DE32708_2FF9_4DE1_BA26_31274EA8AFDD__INCLUDED_)
