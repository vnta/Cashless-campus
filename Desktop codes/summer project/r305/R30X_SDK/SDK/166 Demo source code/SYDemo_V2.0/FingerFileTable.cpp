#include "stdafx.h"

#include "FingerFileTabe.h"
#include "Shlwapi.h"
#include <iso646.h>

int CFingerFileTable::TableCount = 0 ;

CFingerFileTable::CFingerFileTable()
{
	TCHAR filepath[256];
	GetCurrExePath(filepath);
	_tcscat(filepath,"FTmpelet.dat");
    if (PathFileExists(filepath))  //打开已经存在的
	{
		m_CurHandle = CreateFile(filepath,    // file to open
			GENERIC_READ | GENERIC_WRITE,          // open for reading
			0,       // don't share  
			NULL,                  // default security
			OPEN_EXISTING,         // existing file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);                 
		
	}
	else   //创建新的文件
	{
		m_CurHandle = CreateFile(filepath,     
			GENERIC_WRITE | GENERIC_READ,          
			0,                       
			NULL,                    
			CREATE_ALWAYS,          
			FILE_ATTRIBUTE_NORMAL |  
			FILE_FLAG_OVERLAPPED,    
			NULL);   
		Sleep(300);
		if (m_CurHandle!=INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_CurHandle);
		}
		m_CurHandle = CreateFile(filepath,    // file to open
			GENERIC_READ | GENERIC_WRITE,          // open for reading
			0,       // don't share  
			NULL,                  // default security
			OPEN_EXISTING,         // existing file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);   		
	}	
}

CFingerFileTable::CFingerFileTable(LPCTSTR filepath)
{
    if (PathFileExists(filepath))  //打开已经存在的
	{
		m_CurHandle = CreateFile(filepath,    // file to open
			GENERIC_READ | GENERIC_WRITE,          // open for reading
			0,       // don't share  
			NULL,                  // default security
			OPEN_EXISTING,         // existing file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);                 
		
	}
	else   //创建新的文件
	{
		m_CurHandle = CreateFile(filepath,     
			GENERIC_WRITE | GENERIC_READ,          
			0,                       
			NULL,                    
			CREATE_ALWAYS,          
			FILE_ATTRIBUTE_NORMAL |  
			FILE_FLAG_OVERLAPPED,    
			NULL);  
		if (m_CurHandle!=INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_CurHandle);
		}
		m_CurHandle = CreateFile(filepath,    // file to open
			GENERIC_READ | GENERIC_WRITE,          // open for reading
			0,       // don't share  
			NULL,                  // default security
			OPEN_EXISTING,         // existing file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);   

		
	}

}

CFingerFileTable::CFingerFileTable(const CFingerFileTable &filetable)
{

}

CFingerFileTable::~CFingerFileTable()
{
	if (m_CurHandle!=INVALID_HANDLE_VALUE)
	{
		 CloseHandle (m_CurHandle);
	}
}

BOOL CFingerFileTable::DelAllTempelet()
{
	m_Content.clear();
    SetFilePointer(m_CurHandle,0,NULL, FILE_BEGIN);
    SetEndOfFile(m_CurHandle);
	return TRUE;
}


//格式 4000,usr
BOOL CFingerFileTable::DelOneTempelet(int fid)
{
	map <int, CString>::iterator m1_Iter,m1_tmp;
 
	DWORD filesize = 0,writesize = 0,nRead =0;
	unsigned char buf[5000] = {0};
 	filesize = GetFileSize(m_CurHandle,NULL);
    char buffer[4];
	SetFilePointer(m_CurHandle,0,NULL, FILE_BEGIN);
    SetEndOfFile(m_CurHandle);
  //  return true;
	unsigned char *pbuf = buf;
    for ( m1_Iter = m_Content.begin(); m1_Iter != m_Content.end(); m1_Iter++ )
	{   
		 if (m1_Iter->first!= fid )
		 {
			  memset(buffer,0,sizeof(buffer));	
              itoa(m1_Iter->first,buffer,10);
			  memcpy(pbuf,buffer,sizeof(int));
			  pbuf = pbuf+sizeof(int);
			  *pbuf++=',';
			  memcpy(pbuf,m1_Iter->second,m1_Iter->second.GetLength());
			  pbuf = pbuf + m1_Iter->second.GetLength();
			  *pbuf++=13;
			  *pbuf++=10;				 
		 }
		 else
			 m1_tmp = m1_Iter;		
	}

	if (m_Content.size() == 1)
	{
		m_Content.clear();
	}
	else
	m_Content.erase(m1_tmp);

    filesize=filesize - 10;
	WriteFile(m_CurHandle,buf,filesize,&writesize,NULL);
	FlushFileBuffers(m_CurHandle);
	return TRUE;
}

map<int,CString> CFingerFileTable::GetAllContent()
{ 
	const int MAX_BUFFER = 8 * 900;  //900行   1,user1
    unsigned char lpBuffer[MAX_BUFFER] = {0};  
    DWORD nNumberOfBytesToRead = 0;
    DWORD nNumberOfBytesRead =0 ;
    unsigned char *pbuf = NULL;
	BOOL bResult ; 
	DWORD nfilesize = 0;
    DWORD nRes =0;

	
	nfilesize = GetFileSize(m_CurHandle, NULL);

    if ((nfilesize == INVALID_FILE_SIZE) or (nfilesize == 0))
    {
		m_Content.clear();
		return m_Content;
    }
	if (nfilesize > MAX_BUFFER - 3)
	{
		m_Content.clear();
		return m_Content;
	}
    
	bResult = ReadFile(m_CurHandle,lpBuffer,nfilesize,&nNumberOfBytesRead,NULL);
	if (!bResult)
	{
		m_Content.clear();
		return m_Content;
	}
    
	lpBuffer[nNumberOfBytesRead+0] = 0x0D;
	lpBuffer[nNumberOfBytesRead+1] = 0x0A;
	lpBuffer[nNumberOfBytesRead+2] = '\0';

	pbuf = lpBuffer;

    CString str;
	int idx;
	CString sName;

	unsigned char  tmp[4]={0};

	m_Content.clear();

	while (*pbuf!='\0')
	{   
		memcpy(&tmp,pbuf,4);
		idx  = atoi((const char *)tmp);

        pbuf = pbuf + 5 ; //跳过逗号
		while ((*pbuf!= 0x0D) and (*pbuf!='\0'))
		{
			str.Format("%c",*pbuf) ; 
			sName = sName + str;
			pbuf ++ ;	
		}
		if (sName.IsEmpty()) break;
		pbuf = pbuf + 2 ;  		
		m_Content.insert(finger_pair(idx,sName));
		sName ="";
	}  

    map<int,CString> mTmp;
    map<int,CString>::iterator m_iter,m_iter1,m_iter2,m_iterTmp;
    for (m_iter=m_Content.begin(); m_iter!=m_Content.end(); m_iter++)
    {
 
    }
 
  
	return m_Content;
}

BOOL CFingerFileTable::GetCurrExePath(LPTSTR path)
{
	TCHAR   szExePath[256] = {0};
	
	TCHAR   szDrive[255];
    TCHAR   szDir[255];
	TCHAR   szFname[255];
    TCHAR   szExt[5];
	::GetModuleFileName(GetModuleHandle(NULL),szExePath,256) ;
	_splitpath(szExePath,szDrive,szDir,szFname,szExt) ;
	_tcscat(szDrive,szDir);
	_tcscpy(path,szDrive);
    return TRUE;
}

BOOL CFingerFileTable::AppendTempelet(int fid, LPCTSTR username)
{
	if (fid > 9999)
	{
		return FALSE;
	}
	DWORD nfilesize = 0,nRes = 0;
	unsigned char buf[10] = {0};
	char buffer[10]={0};
    nfilesize= GetFileSize(m_CurHandle,NULL);
	if (nfilesize==INVALID_FILE_SIZE)
	{
		return FALSE;
	}
	if (nfilesize==0) //新文件
	{		
		memset(buffer,0,sizeof(buffer));		
		itoa(fid,buffer,10);		
		memcpy(&buf[0],&buffer,sizeof(int));	
		
		buf[4]= ',';
		memcpy(&buf[5],"usr",3);			
		if (WriteFile(m_CurHandle,buf,8,&nfilesize,NULL)==0)
		{
			char szError[256];
			DWORD dwError = GetLastError();
			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,                       
				0,
				0,
				szError,
				sizeof(szError),
				NULL);
			//AfxMessageBox(szError);
			
			return FALSE;
		}			
	}   
	else
	{
		nRes = SetFilePointer(m_CurHandle,nfilesize,NULL, FILE_BEGIN);

		buf[0]= 13;
		buf[1]= 10; 
		
		memset(buffer,0,sizeof(buffer));
		
		itoa(fid,buffer,10);
		
		memcpy(&buf[2],&buffer,sizeof(int));	
		
		buf[6]= ',';
		memcpy(&buf[7],"usr",3);
			
		if (WriteFile(m_CurHandle,buf,10,&nfilesize,NULL)==0)
		{
			return FALSE;
		}
	}
    FlushFileBuffers(m_CurHandle);
    
    m_Content.insert(finger_pair(fid,username));	 
	return TRUE;
}

BOOL CFingerFileTable::IsExisitId(int fid)
{
	map <int, CString>::iterator m1_Iter;
	if (m_CurHandle==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	m1_Iter = m_Content.find(fid);
	if (m1_Iter == m_Content.end())
	{
		return FALSE;
	}
	return TRUE;
}

