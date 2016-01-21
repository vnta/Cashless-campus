#ifndef _IMGFORMATS_H_
#define _IMGFORMATS_H_


/* 
	BMP24 file format
 */
#define BMP_SIGNATURE		0x4D42
#define LNF_SIGNATURE		0x4453
#define LNF_RGB565			0x01
#define LNF_RGB888			0x02

#define	WORD				uint16_t
#define	DWORD				uint32_t
#define	byte				uint8_t

#pragma pack(push,2)
typedef struct tagBMPHEADER
{	// File Header
	WORD		bfType; // 0x4D42 = "BM"
	DWORD		bfSize;
	WORD		bfReserved1;
	WORD		bfReserved2;
	DWORD		bfOffBits;
	// Image header
	DWORD 		biSize;
	long	   	biWidth;
	long	   	biHeight;
	WORD	   	biPlanes;
	WORD	   	biBitCount;
	DWORD  		biCompression;
	DWORD  		biSizeImage;
	long	    biXPelsPerMeter;
	long	    biYPelsPerMeter;
	DWORD  		biClrUsed;
	DWORD  		biClrImportant;
} BMPHEADER, *PBMPHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tagRGBTRIPLE
{
	byte    rgbtBlue;
	byte    rgbtGreen;
	byte    rgbtRed;
} RGBTRIPLE, *PRGBTRIPLE;
#pragma pack(pop)

/* 
	LCD native image file format 
*/
#pragma pack(push,2)
typedef struct tagLNFHEADER
{
	WORD		lnfID; // 0x4453
	WORD		width;
	WORD		height;
	WORD		imageType;
	WORD		bytesPerPixel;
	DWORD		pixelCount;
	WORD		reserved;
} LNFHEADER, *PLNFHEADER;
#pragma pack(pop)

// LCD native 16bit (RGB565) format
typedef uint16_t LCDCOLOR;

#define LCD_COLOR_WHITE				0xFFFF
#define LCD_COLOR_BLACK				0x0000
#define LCD_COLOR_GREY				0xF7DE
#define LCD_COLOR_RED				0xF800
#define LCD_COLOR_ORANGE			0xFC00
#define LCD_COLOR_GREEN				0x07E0
#define LCD_COLOR_BLUE				0x001F
#define LCD_COLOR_MAGENTA			0xF81F
#define LCD_COLOR_CYAN				0x07FF
#define LCD_COLOR_YELLOW			0xFFE0
#define LCD_COLOR(R, G, B)			((((R)& 0x00F8) << 8) | \
									(((G) & 0x00FC) << 3) | \
									(((B) & 0x00F8) >> 3))
#define LCD_COLOR_DKGREY			LCD_COLOR(80,80,80)
#define LCD_COLOR_LTGREY			LCD_COLOR(192,192,192)
#define LCD_COLOR_DKGREEN			LCD_COLOR(0,128,64)
#define LCD_COLOR_SKYBLUE			LCD_COLOR(0,128,255)
#define LCD_COLOR_TRANSPARENT		LCD_COLOR(8,4,8)

#endif // _IMGFORMATS_H_

/**
	\}
 */

