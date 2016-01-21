// OPTModuleTest.h : main header file for the OPTMODULETEST application
//

#if !defined(AFX_OPTMODULETEST_H__1FA4EB8C_178D_4872_957D_03B033571E97__INCLUDED_)
#define AFX_OPTMODULETEST_H__1FA4EB8C_178D_4872_957D_03B033571E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COPTModuleTestApp:
// See OPTModuleTest.cpp for the implementation of this class
//

class COPTModuleTestApp : public CWinApp
{
public:
	COPTModuleTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPTModuleTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COPTModuleTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTMODULETEST_H__1FA4EB8C_178D_4872_957D_03B033571E97__INCLUDED_)
