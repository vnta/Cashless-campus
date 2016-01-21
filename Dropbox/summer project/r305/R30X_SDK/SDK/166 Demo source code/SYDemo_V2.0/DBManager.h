// DBManager.h: interface for the CDBMenager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMENAGER_H__AE81C6CD_748D_460C_8DE0_D1A77C21146B__INCLUDED_)
#define AFX_DBMENAGER_H__AE81C6CD_748D_460C_8DE0_D1A77C21146B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDBManager  
{
public:
	CRecordset* DBOpenRecordset(UINT nOpenType, CString sSQL);
	int DBFindInfo(CString sSQL);
	int DBExecuteSQL(CString sSQL);
	void DBClose();
	int DBConnect(CString sName,CString sUser,CString sPassWord);
	int DBRollback();
	int DBCommitTrans();
	int DBBeginTrans();
//    void CreateData();
	CDBManager();
	virtual ~CDBManager();
	CDatabase	m_DB;
	CString     m_ErrorMsg;

};

#endif // !defined(AFX_DBMENAGER_H__AE81C6CD_748D_460C_8DE0_D1A77C21146B__INCLUDED_)
