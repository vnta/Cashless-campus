#if !defined(AFX_DOWNCHARLIB_H__D082BAC9_1E93_4421_8C9B_A9C8F094AB81__INCLUDED_)
#define AFX_DOWNCHARLIB_H__D082BAC9_1E93_4421_8C9B_A9C8F094AB81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownCharLib.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDownCharLib dialog

class CDownCharLib : public CDialog
{
// Construction
public:
	void BrowseDir(CString strDir);
	CDownCharLib(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDownCharLib)
	enum { IDD = IDD_DLGDOWNLIB };
	int		m_TempId;
	int		m_DownTimes;
	int		m_PathTempId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownCharLib)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDownCharLib)
	afx_msg void OnSelectPath();
	afx_msg void OnSelectPath1();
	afx_msg void OnLoopDown();
	virtual BOOL OnInitDialog();
	afx_msg void OnPathDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNCHARLIB_H__D082BAC9_1E93_4421_8C9B_A9C8F094AB81__INCLUDED_)
