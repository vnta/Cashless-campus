#ifndef  _PROTOCOL_Optics
#define  _PROTOCOL_Optics

#ifdef _OT_CPP_
#undef _OT_CPP_
#endif

///////////////////���󷵻���////////////////////
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
 

///////////////������//////////////////////////////
#define CHAR_BUFFER_A          0x01
#define CHAR_BUFFER_B          0x02
#define MODEL_BUFFER           0x03

//////////////////���ں�////////////////////////
#define COM1                   0x01
#define COM2                   0x02
#define COM3                   0x03

//////////////////������////////////////////////
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
	//////             ָ��                  //////
	///////////////////////////////////////////////
	//�����ָ��¼ȡͼ��
	int WINAPI      PSGetImage(int nAddr);
	
	//����ԭʼͼ������ָ������
	int  WINAPI    PSGenChar(int nAddr,int iBufferID);
	
	//��ȷ�ȶ�CharBufferA��CharBufferB�е������ļ�
	int WINAPI     PSMatch(int nAddr,int* iScore);
	
	//��CharBufferA��CharBufferB�е������ļ����������򲿷�ָ�ƿ�
	int  WINAPI    PSSearch(int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress);

	////��CharBufferA��CharBufferB�е������ļ��������������򲿷�ָ�ƿ�
	int  WINAPI     PSHighSpeedSearch(int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress);
	
	//��CharBufferA��CharBufferB�е������ļ��ϲ�����ģ�����ModelBuffer
	int  WINAPI    PSRegModule(int nAddr);
	
	//��ModelBuffer�е��ļ����浽flashָ�ƿ���
	int  WINAPI    PSStoreChar(int nAddr,int iBufferID, int iPageID);
	
	//��flashָ�ƿ��ж�ȡһ��ģ�嵽ModelBuffer
	int  WINAPI     PSLoadChar(int nAddr,int iBufferID,int iPageID);
	
	//�������������е��ļ��ϴ�����λ��
	int WINAPI     PSUpChar(int nAddr,int iBufferID, unsigned char* pTemplet, int* iTempletLength);
	
	//����λ������һ�������ļ�������������
	int WINAPI     PSDownChar(int nAddr,int iBufferID, unsigned char* pTemplet, int iTempletLength);
	
	//�ϴ�ԭʼͼ��
	int WINAPI     PSUpImage(int nAddr,unsigned char* pImageData, int* iImageLength);
	
	//����ԭʼͼ��
	int WINAPI     PSDownImage(int nAddr,unsigned char *pImageData, int iLength);
	
	//�ϴ�ԭʼͼ��
	int  WINAPI     PSImgData2BMP(unsigned char* pImgData,const char* pImageFile);
	
	//����ԭʼͼ��
	
	int  WINAPI     PSGetImgDataFromBMP(const char *pImageFile,unsigned char *pImageData,int *pnImageLen);
	
	//ɾ��flashָ�ƿ��е�һ�������ļ�
	int WINAPI     PSDelChar(int nAddr,int iStartPageID,int nDelPageNum);
	
	//���flashָ�ƿ�
	int WINAPI     PSEmpty(int nAddr);
	
	//��������
	int WINAPI     PSReadParTable(int nAddr,unsigned char* pParTable);
	
	//����ָ��
	int WINAPI     PSPowerDown(int nAddr);
	
	//�����豸���ֿ���
	int WINAPI     PSSetPwd(int nAddr,unsigned char* pPassword);
	
	//��֤�豸���ֿ���
	int WINAPI     PSVfyPwd(int nAddr,unsigned char* pPassword);
	
	//ϵͳ��λ�������ϵ��ʼ״̬
	int WINAPI      PSReset(int nAddr);
	
	
	//�����±�
	int	WINAPI	    PSReadInfo(int nAddr,int nPage,unsigned char* UserContent);
	
	//д���±�
	int	WINAPI	    PSWriteInfo(int nAddr,int nPage,unsigned char* UserContent);
	
	//дģ��Ĵ���������������
	int  WINAPI     PSSetBaud(int nAddr,int nBaudNum);
	//дģ��Ĵ�������ȫ�ȼ�����
	int WINAPI     PSSetSecurLevel(int nAddr,int nLevel);
	//дģ��Ĵ��������ݰ���С����
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
	
	//���ݴ���Ż�ȡ������Ϣ
	char* WINAPI   PSErr2Str(int nErrCode);

#ifdef _OT_CPP_
}
#endif

#endif                                                     