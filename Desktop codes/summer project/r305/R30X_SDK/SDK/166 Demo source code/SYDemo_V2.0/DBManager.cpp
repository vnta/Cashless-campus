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
//ȫ�ֺ�����ascii_hex
//���ܣ����ı�ת��Ϊʮ������
//������
//		ascii	���ı�(char)ָ��
//		hex	    ��ʮ������(BYTE)ָ��
//		nLength	��ת����ʮ�����Ƶĸ���
//���أ�
//		0	��ת���ɹ�
//		-1  ���г�0-9��a-f�ķǷ��ַ���ת��ʧ��
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
//ȫ�ֺ�����hex_ascii
//���ܣ���ʮ������ת��Ϊ�ı�
//������
//		ascii	���ı�(char)ָ��
//		hex	    ��ʮ������(BYTE)ָ��
//		nLength	��ת��ǰ��ʮ�����Ƶĸ���
//���أ�
//		0	��ת���ɹ�
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
//������DBConnect
//���ܣ�����ODBC���ݿ�
//������
//		sName	��DSN������
//		sUser	���û�����
//		sPassWord	������
//���أ�
//		0	�����ӳɹ�
//		-1  ������ʧ��
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
			//�������ݿ�ʧ�ܣ��˳�ϵͳ
			m_ErrorMsg = "�������ݿ�ʧ�ܣ�";
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
//������DBExecuteSQL
//���ܣ�ִ��SQL���
//������
//		sSQL	��SQL���
//���أ�
//		0	��ִ�гɹ�
//		-1  ��ִ��ʧ�ܻ�SQL������
//-------------------------------------------------------------->>>
int CDBManager::DBExecuteSQL(CString sSQL)
{
	try
	{
		m_DB.ExecuteSQL(sSQL);
	}
	catch(CDBException)
	{
		m_ErrorMsg = "ִ��SQL���ʧ�ܣ�";
		return(-1);
	}

	return(0);
}
//-------------------------------------------------------------->>>
//������DBFindInfo
//���ܣ�����ָ��������Ϣ�Ƿ��Ѵ���,��Ҫ���ں����С����磺
//           �޸�֮ǰ���жϼ�¼�Ƿ��Ѵ��ڣ�Ȼ���ȡ��Ӧ������
//������
//		strSQL	:Ҫִ�е�SQL���
//���أ�
//		0	���ҵ�
//		1   ��δ�ҵ�
//		-2��SQL������
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
		m_ErrorMsg = "SQL������";
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
//������DBOpenRecordset
//���ܣ�ִ�� SQL ���õ���ͼ
//������
//		nOpenType	:���صļ�¼������
//			dynaset		= 0,uses SQLExtendedFetch, keyset driven cursor
//			snapshot	= 1,uses SQLExtendedFetch, static cursor
//			forwardOnly	= 2,uses SQLFetch
//			dynamic		= 3,uses SQLExtendedFetch, dynamic cursor
//		sSQL	:Ҫִ�е�SQL���
//���أ�
//		CRecordset	�����ؼ�¼��,ע����¼������Ҫ�ȹرպ�ɾ��.
//		NULL		��SQL������
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
		m_ErrorMsg = "SQL������";
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