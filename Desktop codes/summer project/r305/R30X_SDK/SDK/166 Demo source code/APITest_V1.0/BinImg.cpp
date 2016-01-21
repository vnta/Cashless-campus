// BinImg.cpp : implementation file
//

#include "stdafx.h"
#include "OPTModuleTest.h"
#include "BinImg.h"
#include "Protocol.h"
#include "OptModuleTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BinImg dialog


BinImg::BinImg(CWnd* pParent /*=NULL*/)
	: CDialog(BinImg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BinImg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BinImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BinImg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BinImg, CDialog)
	//{{AFX_MSG_MAP(BinImg)
	ON_BN_CLICKED(IDC_BUTTON1, OnBinImg)
	ON_BN_CLICKED(IDC_BUTTON2, OnGenBin)
	ON_BN_CLICKED(IDC_BUTTON3, OnGenXH)
	ON_BN_CLICKED(IDC_BUTTON4, OnGenXHTZ)
	ON_BN_CLICKED(IDC_BUTTON5, OnSaveToBmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
void BinImg::ShowBMP(int ID,CString strPath)
{
	CStatic *pStatic;
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)LoadImage( GetModuleHandle(NULL),strPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap  == NULL)
		hBitmap  = (HBITMAP)LoadImage( NULL,strPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	pStatic=(CStatic *)GetDlgItem( ID );
	pStatic->SetBitmap(hBitmap);//显示图像	
}
// BinImg message handlers
char gstrPath[256]={0};
void BinImg::OnBinImg() 
{
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,_T("BMP Files (*.bmp)|*.bmp"));
	if(!fdlg.DoModal()) return;
	CString str;
	str=fdlg.GetPathName();
	char strPath[256]={0};
	memcpy(strPath,str,str.GetLength());
	strcpy(gstrPath,strPath);
    ShowBMP(IDC_BINIMG,strPath);	
}

void BinImg::GenImg(int nType)
{
	if(!pMyDlg->OpenDev())
	{
		AfxMessageBox("设备打开失败");
		return;
	}
	if(gstrPath[0]==0)
	{
		AfxMessageBox("请选择图像");
		return;
	}
	int ret;
	memset(gpImageData,0,gnImageSize);
	ret=PSGetImgDataFromBMP(gstrPath,gpImageData,&gnImageSize)	;
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	ret = PSDownImage(pMyDlg->m_Addr,gpImageData,gnImageSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	ret = PSGenBinImage(pMyDlg->m_Addr,nType);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	ret = PSUpImage(pMyDlg->m_Addr,gpImageData,&gnImageSize);
	if(ret!=PS_OK)
	{
		AfxMessageBox( PSErr2Str(ret) );
		return;
	}
	
	
	ret=PSImgData2BMP(gpImageData,"C:\\test.bmp");
	if(ret!=0)
	{
		AfxMessageBox("失败");
		return;
	}
	ShowBMP(IDC_BINIMG,"C:\\test.bmp");
}
 
void BinImg::OnGenBin() 
{
	 GenImg(BIN_IMG);
}

void BinImg::OnGenXH() 
{
	GenImg(XH_IMG);	
}

void BinImg::OnGenXHTZ() 
{
	GenImg(XHTZ_IMG);	
}

void BinImg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

//保存到一副Bmp 文件
void BinImg::OnSaveToBmp() 
{
    static char BASED_CODE szFilter[] = "Bmp File (*.bmp)|*.bmp|";

	CStatic *pImg = (CStatic *)GetDlgItem(IDC_BINIMG);
    HBITMAP   hbm   =   pImg->GetBitmap(); 
    if (hbm == NULL) return;

	CFileDialog dlgSave(
						FALSE,
						"*.bmp",
						"",
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						szFilter,
						NULL
						); 

	dlgSave.DoModal();   
	CString sFileName;
    sFileName = dlgSave.GetFileName();
    if (sFileName.IsEmpty())
    {
		return;
    }

	/*
	OPENFILENAME   ofn;               //   common   dialog   box   structure   
	char   szFile[260];               //   buffer   for   file   name   
	HWND   hwnd;                             //   owner   window   
	HANDLE   hf;                             //   file   handle   
    
	  //   Initialize   OPENFILENAME   
	  ZeroMemory(&ofn,   sizeof(ofn));   
	  ofn.lStructSize   =   sizeof(ofn);   
	  ofn.hwndOwner   =   hwnd;   
	  ofn.lpstrFile   =   szFile;   
	  //   
	  //   Set   lpstrFile[0]   to   '\0'   so   that   GetOpenFileName   does   not     
	  //   use   the   contents   of   szFile   to   initialize   itself.   
	  //   
	  ofn.lpstrFile[0]   =   '\0';   
	  ofn.nMaxFile   =   sizeof(szFile);   
	  ofn.lpstrFilter   =   "All\0*.*\0Text\0*.TXT\0";   
	  ofn.nFilterIndex   =   1;   
	  ofn.lpstrFileTitle   =   NULL;   
	  ofn.nMaxFileTitle   =   0;   
	  ofn.lpstrInitialDir   =   NULL;   
	  ofn.Flags   =   OFN_PATHMUSTEXIST   |   OFN_FILEMUSTEXIST;   
	  
		//   Display   the   Save   dialog   box.     
		
		  GetSaveFileName(&ofn);     
		  
			//   ofn.lpstrFile   Store   the   Filename.   
			MessageBox(NULL,ofn.lpstrFile,NULL,MB_OK);   
			
	*/
	SaveToFile(hbm,sFileName);   //保存到文件

		
}

BOOL BinImg::SaveToFile(HBITMAP  hBitmap,LPCTSTR lpszFileName)
{
	HDC   hDC;   
	//当前分辨率下每象素所占字节数   
	int   iBits;   
	//位图中每象素所占字节数   
	WORD   wBitCount;   
	//定义调色板大小，   位图中像素字节大小   ，位图文件大小   ，   写入文件字节数   
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;   
	//位图属性结构   
	BITMAP   Bitmap;   
	//位图文件头结构   
	BITMAPFILEHEADER   bmfHdr;   
	//位图信息头结构   
	BITMAPINFOHEADER   bi;   
	//指向位图信息头结构   
	LPBITMAPINFOHEADER   lpbi;   
	//定义文件，分配内存句柄，调色板句柄   
	HANDLE  fh,hDib,hPal,hOldPal=NULL;   
	
	//计算位图文件每个像素所占字节数   
	hDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);   
	iBits   =   GetDeviceCaps(hDC,   BITSPIXEL)   *   GetDeviceCaps(hDC,   PLANES);   
	DeleteDC(hDC);   
	if (iBits <= 1)   
		wBitCount = 1;   
	else if (iBits <= 4)   
		wBitCount = 4;   
	else if (iBits <= 8)   
		wBitCount = 8;   
	else   
		wBitCount = 24;   
	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);   
	bi.biSize   =   sizeof(BITMAPINFOHEADER);   
	bi.biWidth   =   Bitmap.bmWidth;   
	bi.biHeight   =   Bitmap.bmHeight;   
	bi.biPlanes   =   1;   
	bi.biBitCount   =   wBitCount;   
	bi.biCompression   =   BI_RGB;   
	bi.biSizeImage   =   0;   
	bi.biXPelsPerMeter   =   0;   
	bi.biYPelsPerMeter   =   0;   
	bi.biClrImportant   =   0;   
	bi.biClrUsed   =   0;   
	dwBmBitsSize   =   ((Bitmap.bmWidth * wBitCount +  31) / 32) * 4 * Bitmap.bmHeight;   
	//为位图内容分配内存     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));   
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);   
	*lpbi   =   bi;   
	//   处理调色板       
	hPal   =   GetStockObject(DEFAULT_PALETTE);   
	if   (hPal)   
	{     
		hDC   =   ::GetDC(NULL);   
		hOldPal   =   SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);   
		RealizePalette(hDC);   
	}   
	
	//   获取该调色板下新的像素值   
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize,   (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);   
	//恢复调色板   
	if   (hOldPal)   
	{   
		SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);   
		RealizePalette(hDC);   
		::ReleaseDC(NULL,   hDC);   
	}   
	//创建位图文件 ,用于保存创建的位图图像         
	fh   =   CreateFile(lpszFileName, GENERIC_WRITE,0, NULL , CREATE_ALWAYS,     
	                	FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);     
	
	if   (fh == INVALID_HANDLE_VALUE)   return   FALSE; 
	
	//   设置位图文件头     
	bmfHdr.bfType   =   0x4D42;   //   "BM"   
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;   
	bmfHdr.bfSize   =   dwDIBSize;   
	bmfHdr.bfReserved1   =   0;   
	bmfHdr.bfReserved2   =   0;   
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;
	
	//   写入位图文件头   
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER), &dwWritten,NULL);   
	//   写入位图文件其余内容   
	WriteFile(fh,(LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);   
	//清除   
	GlobalUnlock(hDib);   
	GlobalFree(hDib);   
	CloseHandle(fh);    
	return   TRUE; 
}
