// DBManager.cpp: implementation of the CDBManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------->>>
//全局函数：ascii_hex
//功能：将文本转换为十六进制
//参数：
//		ascii	：文本(char)指针
//		hex	    ：十六进制(BYTE)指针
//		nLength	：转换后，十六进制的个数
//返回：
//		0	：转换成功
//		-1  ：有除0-9和a-f的非法字符，转换失败
//-------------------------------------------------------------->>>
int ascii_hex(char * ascii,BYTE * hex,int nLength)
{
	int hiByte,loByte;
	for (int i=0;i<nLength;i++)
	{
      if ( (ascii[i*2]>47) && (ascii[i*2]<58) ) hiByte=ascii[i*2]-48;///it's a digital
	  else if ( (ascii[i*2]>64) && (ascii[i*2]<71) ) hiByte=ascii[i*2]-65+10;///it's a A--F    
         else if ( (ascii[i*2]>96) && (ascii[i*2]<103) ) hiByte=ascii[i*2]-97+10;///it's a a--f    
	           else  return -1;
			   ////
	      if ( (ascii[i*2+1]>47) && (ascii[i*2+1]<58) ) loByte=ascii[i*2+1]-48;///it's a digital
	  else if ( (ascii[i*2+1]>64) && (ascii[i*2+1]<71) ) loByte=ascii[i*2+1]-65+10;///it's a A--F    
         else if ( (ascii[i*2+1]>96) && (ascii[i*2+1]<103) ) loByte=ascii[i*2+1]-97+10;///it's a a--f    
	           else  return -1;
	  hex[i]=(BYTE)(hiByte*16+loByte);
	}
	return 0;
}
//-------------------------------------------------------------->>>
//全局函数：hex_ascii
//功能：将十六进制转换为文本
//参数：
//		ascii	：文本(char)指针
//		hex	    ：十六进制(BYTE)指针
//		nLength	：转换前，十六进制的个数
//返回：
//		0	：转换成功
//-------------------------------------------------------------->>>
int hex_ascii(BYTE *hex,char * ascii,int nLength)
{	int hiByte,loByte;
	for (int i=0;i<nLength;i++)
	{hiByte=hex[i]/16;
	 loByte=hex[i]%16;
	 if (hiByte<10) ascii[i*2]=(char )(hiByte+48);//it's a digital
	 else ascii[i*2]=(char)(hiByte+65-10);//convert to A--F

	 if (loByte<10) ascii[i*2+1]=(char)(loByte+48);//it's a digital
	 else ascii[i*2+1]=(char)(loByte+65-10);//convert to A--F
	}
	ascii[nLength*2]='\0';
return 0;
}



CDBManager::CDBManager()
{

}

CDBManager::~CDBManager()
{

}

int CDBManager::DBBeginTrans()
{
	return(m_DB.BeginTrans());
}

int CDBManager::DBCommitTrans()
{
	return(m_DB.CommitTrans());
}

int CDBManager::DBRollback()
{
	return(m_DB.Rollback());
}
//-------------------------------------------------------------->>>
//函数：DBConnect
//功能：连接ODBC数据库
//参数：
//		sName	：DSN的名称
//		sUser	：用户名称
//		sPassWord	：口令
//返回：
//		0	：连接成功
//		-1  ：连接失败
//-------------------------------------------------------------->>>
int CDBManager::DBConnect(CString sName, CString sUser, CString sPassWord)
{
	CString	sOdbc;
    TRY
	{
		sOdbc.Format("DSN=%s;UID=%s;PWD=%s", sName, sUser, sPassWord);
		if(m_DB.OpenEx(sOdbc, CDatabase::noOdbcDialog))		return 0;
	
	}
	CATCH(CDBException, e)
	{      
//		e->Delete();
//        CreateData();
		return 1;
	}
	END_CATCH;
/*	TRY
	{
		sOdbc.Format("DSN=%s;UID=%s;PWD=%s", sName, sUser, sPassWord);
		if(m_DB.OpenEx(sOdbc, CDatabase::noOdbcDialog))		return 0;
	}
	CATCH(CDBException, e)
	{      
		;
	}
	END_CATCH;
	try
    {
		if(!m_DB.OpenEx(sOdbc, CDatabase::forceOdbcDialog))
		{
			//连接数据库失败！退出系统
			m_ErrorMsg = "连接数据库失败！";
			return(-1);
		}
    }
	catch (CDBException)
	{
		return -1;
	}
	return(0);*/
	return 0;
}

void CDBManager::DBClose()
{
	m_DB.Close();
}
//-------------------------------------------------------------->>>
//函数：DBExecuteSQL
//功能：执行SQL语句
//参数：
//		sSQL	：SQL语句
//返回：
//		0	：执行成功
//		-1  ：执行失败或SQL语句错误
//-------------------------------------------------------------->>>
int CDBManager::DBExecuteSQL(CString sSQL)
{
	try
	{
		m_DB.ExecuteSQL(sSQL);
	}
	catch(CDBException)
	{
		m_ErrorMsg = "执行SQL语句失败！";
		return(-1);
	}

	return(0);
}
//-------------------------------------------------------------->>>
//函数：DBFindInfo
//功能：查找指定数据信息是否已存在,主要用于函数中。例如：
//           修改之前先判断记录是否已存在，然后采取相应动作。
//参数：
//		strSQL	:要执行的SQL语句
//返回：
//		0	：找到
//		1   ：未找到
//		-2：SQL语句错误
//-------------------------------------------------------------->>>
int CDBManager::DBFindInfo(CString sSQL)
{
    CRecordset	rSet(&m_DB);
	int		nReturn = -1;

	try
	{
		rSet.Open(CRecordset::forwardOnly, sSQL);
	}
	catch(CDBException)
	{
		m_ErrorMsg = "SQL语句错误！";
		return(-2);
	};

	if(!rSet.IsEOF())
	{
		nReturn = 0;
	}
	rSet.Close();

	return(nReturn);
}
//-------------------------------------------------------------->>>
//函数：DBOpenRecordset
//功能：执行 SQL 语句得到视图
//参数：
//		nOpenType	:返回的记录集类型
//			dynaset		= 0,uses SQLExtendedFetch, keyset driven cursor
//			snapshot	= 1,uses SQLExtendedFetch, static cursor
//			forwardOnly	= 2,uses SQLFetch
//			dynamic		= 3,uses SQLExtendedFetch, dynamic cursor
//		sSQL	:要执行的SQL语句
//返回：
//		CRecordset	：返回记录集,注：记录集用完要先关闭后删除.
//		NULL		：SQL语句错误
//-------------------------------------------------------------->>>
CRecordset * CDBManager::DBOpenRecordset(UINT nOpenType, CString sSQL)
{
CRecordset	*reSet;

	reSet = new(CRecordset);
	reSet->m_pDatabase = &m_DB;
	try
	{
		reSet->Open(nOpenType, sSQL);
	}
	catch(CDBException)
	{
		delete reSet;
		m_ErrorMsg = "SQL语句错误！";
		return(NULL);
	};
	return(reSet);
}
/*void CDBManager::CreateData()
{
	CString str="User";
	if(SQLCreateDataSource(m_hWnd,str))//m_pMainWnd->m_hWnd, str))
		dbStatus=pDatabase->OpenEx("DSN=User;uid=admin ");// Ms2101");
	else
		AfxMessageBox("fail!");

}*/