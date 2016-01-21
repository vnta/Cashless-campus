// GDDemo.h : main header file for the GDDEMO application
//

#if !defined(AFX_GDDEMO_H__F7E37AC7_B473_4811_80CA_239CC8FC69AE__INCLUDED_)
#define AFX_GDDEMO_H__F7E37AC7_B473_4811_80CA_239CC8FC69AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGDDemoApp:
// See GDDemo.cpp for the implementation of this class
//

extern LANGID glangid;

class CGDDemoApp : public CWinApp
{
public:
	CGDDemoApp();
    	HACCEL m_hMDIAccel;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGDDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDDEMO_H__F7E37AC7_B473_4811_80CA_239CC8FC69AE__INCLUDED_)
