#if !defined(AFX_BINIMG_H__EB9536CD_5821_4F0C_A7BB_E75DB8E20A96__INCLUDED_)
#define AFX_BINIMG_H__EB9536CD_5821_4F0C_A7BB_E75DB8E20A96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinImg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BinImg dialog

class BinImg : public CDialog
{
private:
	void ShowBMP(int ID,CString strPath);
	void GenImg(int nType);
// Construction
public:
	BinImg(CWnd* pParent = NULL);   // standard constructor
    BOOL   SaveToFile(HBITMAP   hBitmap,   LPCTSTR   lpszFileName);  
// Dialog Data
	//{{AFX_DATA(BinImg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BinImg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BinImg)
	afx_msg void OnBinImg();
	afx_msg void OnGenBin();
	afx_msg void OnGenXH();
	afx_msg void OnGenXHTZ();
	virtual void OnOK();
	afx_msg void OnSaveToBmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINIMG_H__EB9536CD_5821_4F0C_A7BB_E75DB8E20A96__INCLUDED_)
