// OPTModuleTestDlg.h : header file
//

#if !defined(AFX_OPTMODULETESTDLG_H__84BC4896_77D6_41DF_A0AC_D35FE7DC5B96__INCLUDED_)
#define AFX_OPTMODULETESTDLG_H__84BC4896_77D6_41DF_A0AC_D35FE7DC5B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 
#include "infotip/XInfoTip.h"
#include "DlgContent.h"
#include <tchar.h>


/////////////////////////////////////////////////////////////////////////////
// COPTModuleTestDlg dialog

static const TCHAR *pWriteSuccess = _T("Write data successfully");
static const TCHAR *pDownSuccess = _T("Download image successfully"); //下传图象成功！
static const TCHAR *pUploadSuccess = _T("Upload image successfully"); //上传图象成功！
static const TCHAR *pGetImageSuccess = _T("Get image successfully");//获取图象成功
static const TCHAR *pOpenError = _T("Open device error");//打开设备失败
static const TCHAR *pFail = _T("Failed"); //失败！

class COPTModuleTestDlg : public CDialog
{
private:
	
	void SavePara(CString sName,int nVal);
	void LoadPara();
	void ShowPara();
 
	
// Construction
public:
	COPTModuleTestDlg(CWnd* pParent = NULL);	// standard constructor
	~COPTModuleTestDlg();
    void EnableBtn(bool bEnable);	
	int OpenDev();	
	void    ShowBMP(int ID, char *szPath);

	BOOLEAN  blShowWin;   //用于判断显示内容窗体是否重复打开
	BOOLEAN  blDeviceOpen;
// Dialog Data
	//{{AFX_DATA(COPTModuleTestDlg)
	enum { IDD = IDD_OPTMODULETEST_DIALOG };
	CProgressCtrl	m_Progress;
	CComboBox	m_PackSizeCmb;
	CComboBox	m_Buffer;
	CComboBox	m_BaudNum;
	CStatic	m_Finger;
	CComboBox	m_Baud;
	CComboBox	m_Com;
	CString	m_Pwd;
	int		m_Address;
	CString	m_DeviceType;
	CString	m_AddrStr;
	UINT  m_Addr;
	CString	m_SecureLevel;
	UINT	m_InfoPage;
	UINT	m_DelStart;
	UINT	m_DelNum;
	CString	m_sInfo;
	UINT	m_bOpen;
	UINT	m_NewMBID;
	CString	m_strBaud;
	CString	m_strSetBaud;
	CString	m_SysInfo;
	CString	m_strPack;
	CString	m_Path;
	UINT	m_ISPType;
	UINT	m_StartMBID;
	CString	m_ProgressName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPTModuleTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CXInfoTip	m_tooltip;
 	CDlgContent *pDlg;
	// Generated message map functions
	//{{AFX_MSG(COPTModuleTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGDOpenCom();
	afx_msg void OnVfyPwd();
	afx_msg void OnSetPwd();
	afx_msg void OnSetSecureLevel();
	afx_msg void OnGDGetImage();
	afx_msg void OnGDUpImage();
	afx_msg void OnGDGetImage2BMP();
	afx_msg void OnDownImage();
	afx_msg void OnGetImgDataFromBMP();
	afx_msg void OnSetBaud();
	afx_msg void OnReadInfo();
	afx_msg void OnWriteInfo();
	afx_msg void OnReadParTable();
	afx_msg void OnGenChar();
	afx_msg void OnMatch();
	afx_msg void OnSearch();
	afx_msg void OnRegModule();
	afx_msg void OnStoreChar();
	afx_msg void OnLoadChar();
	afx_msg void OnDelOneChar();
	afx_msg void OnEmpty();
	afx_msg void OnUpChar();
	afx_msg void OnDownChar();
	afx_msg void OnSetPktSize();
	afx_msg void OnGDUpChar2File();
	afx_msg void OnDownCharFromFile();
	afx_msg void OnSetChipAddr();
	afx_msg void OnGetRandomData();
	afx_msg void OnPortControl();
	afx_msg void OnReadInfPage();
	afx_msg void OnEnroll();
	afx_msg void OnIdenty();
	afx_msg void OnHighSpeedSearch();
	afx_msg void OnAutoOpen();
	afx_msg void OnSelPath();
	afx_msg void OnTFRR();
	afx_msg void OnTFAR();
	afx_msg void OnTCancel();
	afx_msg void OnGentz();
	afx_msg void OnBinimg();
	afx_msg void OnISP();
	afx_msg void OnTemplateNum();
	afx_msg void OnEnrollLX();
	afx_msg void OnIdentyLX();
	afx_msg void OnDownMBLX();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCloseWindow();
	afx_msg void OnDownCharLib();
	afx_msg void OnData2BMP();
	afx_msg void OnShowData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern COPTModuleTestDlg *pMyDlg;
extern unsigned char gpImageData[256*288];
extern int gnImageSize;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTMODULETESTDLG_H__84BC4896_77D6_41DF_A0AC_D35FE7DC5B96__INCLUDED_)
