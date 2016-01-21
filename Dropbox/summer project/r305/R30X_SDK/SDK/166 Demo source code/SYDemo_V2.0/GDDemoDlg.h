// GDDemoDlg.h : header file
//

#if !defined(AFX_GDDEMODLG_H__2255EB6F_9AF3_4BF2_9B9D_32D51E2D2D9A__INCLUDED_)
#define AFX_GDDEMODLG_H__2255EB6F_9AF3_4BF2_9B9D_32D51E2D2D9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGDDemoDlg dialog

#include "FingerFileTabe.h" 
#include "SortListCtrl.h"
class CGDDemoDlg : public CDialog
{
private:
	BOOL AutoOpen();
	void ShowPara();
	void InitWinText() ;
// Construction
public:
	void ShowInfo(CString strInfo,int iFlag=0);
	void ShowCmdInfo(int ret);
	void Update();
	void EnableBtn(BOOL bEnable);
 
	void ShowInfomation(CString strInfo,COLORREF color);
	void ShowDemoImage(int Imagetype,CString sPath);
	void ShowDefaltImg(); 
	void ShowImage(char *filename=NULL);
    void ClearDataBase();//for
    void LoadUserDefine();
	void InitTmpList();
    
	 
	int		m_Addr;
	int     m_Type;
	CString strUser;
	BOOL bUsbComm;	//通讯方式为USB口
    char szHard[256];
    COLORREF   m_color;

	CFingerFileTable * m_fingertable;
public:
	CGDDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGDDemoDlg)
	enum { IDD = IDD_GDDEMO_DIALOG };
	CStatic	m_Tip;
	CStatic	m_TipInfo;
	CSortListCtrl	m_ListUser;
	CString	m_sTip;
	BOOL	m_bUpImg;
	int		m_ComPakageSize;
	int		m_ComBaud;
	int		m_ComLevel;
	BOOL	m_bPreImg;
	CString	m_Lang;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_HeadIcon;

	// Generated message map functions
	//{{AFX_MSG(CGDDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGenImg();
	afx_msg void OnOpenCom();
	afx_msg void OnEnroll();
	afx_msg void OnVerify();
	afx_msg void OnSearch();
	afx_msg void OnEmpty();
	afx_msg void OnDelete();
	afx_msg void OnClickListuser(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCancelOpt();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnrollCon();
	afx_msg void OnSearchCon();
	afx_msg void OnSelchangeComboBaud();
	afx_msg void OnSelchangeComboPakagesize();
	afx_msg void OnSelchangeComboLevel();
	afx_msg void OnSetfocusComboBaud();
	afx_msg void OnSetfocusComboPakagesize();
	afx_msg void OnSetfocusComboLevel();
	afx_msg void OnBtnSavebmp();
	afx_msg void OnBtnDlbmp();
	afx_msg void OnBtnWnote();
	afx_msg void OnBtnRnote();
	afx_msg void OnBtnRandom();
	afx_msg void OnBtnRnum();
	afx_msg void OnBtnBin();
	afx_msg void OnBtnThin();
	afx_msg void OnBtnTz();
	afx_msg void OnBtnOribmp();
	afx_msg void OnBtnGetdb();
	afx_msg void OnExit();
	afx_msg void OnPath();
	afx_msg void OnGetImgCon();
	afx_msg void OnUserdefine();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnEditchangeComlang();
	afx_msg void OnSelchangeComlang();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDDEMODLG_H__2255EB6F_9AF3_4BF2_9B9D_32D51E2D2D9A__INCLUDED_)
