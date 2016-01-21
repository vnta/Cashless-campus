#pragma once

#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair <int, CString> finger_pair;

class CFingerFileTable
{
	static int TableCount;
	public:
		CFingerFileTable();
		CFingerFileTable(LPCTSTR filepath);
		CFingerFileTable(const CFingerFileTable &filetable);
		virtual ~CFingerFileTable();

		
		map<int,CString>  GetAllContent();
		BOOL AppendTempelet(int fid, LPCTSTR username);
		BOOL DelOneTempelet(int fid);
		BOOL DelAllTempelet();
        BOOL IsExisitId(int fid);
	public:	 
	    CString m_filepath;	
	private:
		BOOL GetCurrExePath(LPTSTR path);
		map <int, CString> m_Content;
		HANDLE  m_CurHandle;   //当前操作的文件句柄	

};