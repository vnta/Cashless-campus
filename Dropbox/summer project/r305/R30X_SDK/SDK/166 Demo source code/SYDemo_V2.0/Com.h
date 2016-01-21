#if !defined(AFX_COM_H__1C26E862_5A66_445D_9490_325BB38F20F4__INCLUDED_)
#define AFX_COM_H__1C26E862_5A66_445D_9490_325BB38F20F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Com.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCom dialog

class CCom : public CDialog
{
public:
	int nCom,nBaud;
// Construction
public:
	CCom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCom)
	enum { IDD = IDD_DLGCOM };
 
	CComboBox	m_Com;
 


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCom)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COM_H__1C26E862_5A66_445D_9490_325BB38F20F4__INCLUDED_)
