#ifndef  _PROTOCOL_Optics
#define  _PROTOCOL_Optics

#ifdef _OT_CPP_
#undef _OT_CPP_
#endif

///////////////////错误返回码////////////////////
#define PS_OK                0x00
#define PS_COMM_ERR          0x01
#define PS_NO_FINGER         0x02
#define PS_GET_IMG_ERR       0x03
#define PS_FP_TOO_DRY        0x04
#define PS_FP_TOO_WET        0x05
#define PS_FP_DISORDER       0x06
#define PS_LITTLE_FEATURE    0x07
#define PS_NOT_MATCH         0x08
#define PS_NOT_SEARCHED      0x09
#define PS_MERGE_ERR         0x0a
#define PS_ADDRESS_OVER      0x0b
#define PS_READ_ERR          0x0c
#define PS_UP_TEMP_ERR       0x0d
#define PS_RECV_ERR          0x0e
#define PS_UP_IMG_ERR        0x0f
#define PS_DEL_TEMP_ERR      0x10
#define PS_CLEAR_TEMP_ERR    0x11
#define PS_SLEEP_ERR         0x12
#define PS_INVALID_PASSWORD  0x13
#define PS_RESET_ERR         0x14
#define PS_INVALID_IMAGE     0x15
#define PS_HANGOVER_UNREMOVE 0X17
 

///////////////缓冲区//////////////////////////////
#define CHAR_BUFFER_A          0x01
#define CHAR_BUFFER_B          0x02
#define MODEL_BUFFER           0x03

//////////////////串口号////////////////////////
#define COM1                   0x01
#define COM2                   0x02
#define COM3                   0x03

//////////////////波特率////////////////////////
#define BAUD_RATE_9600         0x00
#define BAUD_RATE_19200        0x01
#define BAUD_RATE_38400        0x02
#define BAUD_RATE_57600        0x03   //default
#define BAUD_RATE_115200       0x04

#ifdef _OT_CPP_
extern "C"
{
#endif
	BOOL WINAPI PSOpenDevice(int nDeviceType,int nPortNum,int nPortPara,int nPackageSize=2);
		
	BOOL WINAPI PSCloseDevice();
	///////////////////////////////////////////////
	//////             指令                  //////
	///////////////////////////////////////////////
	//检测手指并录取图像
	int WINAPI      PSGetImage(int nAddr);
	
	//根据原始图像生成指纹特征
	int  WINAPI    PSGenChar(int nAddr,int iBufferID);
	
	//精确比对CharBufferA与CharBufferB中的特征文件
	int WINAPI     PSMatch(int nAddr,int* iScore);
	
	//以CharBufferA或CharBufferB中的特征文件搜索整个或部分指纹库
	int  WINAPI    PSSearch(int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress);

	////以CharBufferA或CharBufferB中的特征文件快速搜索整个或部分指纹库
	int  WINAPI     PSHighSpeedSearch(int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress);
	
	//将CharBufferA与CharBufferB中的特征文件合并生成模板存于ModelBuffer
	int  WINAPI    PSRegModule(int nAddr);
	
	//将ModelBuffer中的文件储存到flash指纹库中
	int  WINAPI    PSStoreChar(int nAddr,int iBufferID, int iPageID);
	
	//从flash指纹库中读取一个模板到ModelBuffer
	int  WINAPI     PSLoadChar(int nAddr,int iBufferID,int iPageID);
	
	//将特征缓冲区中的文件上传给上位机
	int WINAPI     PSUpChar(int nAddr,int iBufferID, unsigned char* pTemplet, int* iTempletLength);
	
	//从上位机下载一个特征文件到特征缓冲区
	int WINAPI     PSDownChar(int nAddr,int iBufferID, unsigned char* pTemplet, int iTempletLength);
	
	//上传原始图像
	int WINAPI     PSUpImage(int nAddr,unsigned char* pImageData, int* iImageLength);
	
	//下载原始图像
	int WINAPI     PSDownImage(int nAddr,unsigned char *pImageData, int iLength);
	
	//上传原始图像
	int  WINAPI     PSImgData2BMP(unsigned char* pImgData,const char* pImageFile);
	
	//下载原始图像
	
	int  WINAPI     PSGetImgDataFromBMP(const char *pImageFile,unsigned char *pImageData,int *pnImageLen);
	
	//删除flash指纹库中的一个特征文件
	int WINAPI     PSDelChar(int nAddr,int iStartPageID,int nDelPageNum);
	
	//清空flash指纹库
	int WINAPI     PSEmpty(int nAddr);
	
	//读参数表
	int WINAPI     PSReadParTable(int nAddr,unsigned char* pParTable);
	
	//休眠指令
	int WINAPI     PSPowerDown(int nAddr);
	
	//设置设备握手口令
	int WINAPI     PSSetPwd(int nAddr,unsigned char* pPassword);
	
	//验证设备握手口令
	int WINAPI     PSVfyPwd(int nAddr,unsigned char* pPassword);
	
	//系统复位，进入上电初始状态
	int WINAPI      PSReset(int nAddr);
	
	
	//读记事本
	int	WINAPI	    PSReadInfo(int nAddr,int nPage,unsigned char* UserContent);
	
	//写记事本
	int	WINAPI	    PSWriteInfo(int nAddr,int nPage,unsigned char* UserContent);
	
	//写模块寄存器－波特率设置
	int  WINAPI     PSSetBaud(int nAddr,int nBaudNum);
	//写模块寄存器－安全等级设置
	int WINAPI     PSSetSecurLevel(int nAddr,int nLevel);
	//写模块寄存器－数据包大小设置
	int   WINAPI   PSSetPacketSize(int nAddr,int nSize);
	
	int   WINAPI    PSUpChar2File(int nAddr,int iBufferID, const char* pFileName);
	int  WINAPI     PSDownCharFromFile(int nAddr,int iBufferID, const char* pFileName);
	
	int WINAPI PSGetRandomData(int nAddr,unsigned char* pRandom);
	int WINAPI PSSetChipAddr(int nAddr,unsigned char* pChipAddr);
	
	int WINAPI      PSReadInfPage(int nAddr, unsigned char* pInf);

	int  WINAPI     PSTemplateNum(int nAddr,int *iMbNum);
	int WINAPI PSGenBinImage(int nAddr, int nImgType);
	int  WINAPI  PSDoUserDefine(int nAddr,int GPIO,int STATE);
		
#define DEVICE_USB 0
#define DEVICE_COM 1
	
	
#define IMAGE_X 256
#define IMAGE_Y 288
	
	//根据错误号获取错误信息
	char* WINAPI   PSErr2Str(int nErrCode);

#ifdef _OT_CPP_
}
#endif

#endif                                                     