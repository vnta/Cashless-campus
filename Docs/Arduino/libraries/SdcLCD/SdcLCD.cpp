/**
	\addtogroup	ARDUINO_SdcLCD

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include "SdcLCD.h"

#define ABS(x)						((x) > 0 ? (x) : -(x))
#define INTSWAP(x,y)				do{x ^= y; y ^= x; x ^= y;} while(0)
#define FAST_GRAPHICS				1

// LCD control ports and external memory address
#if MBOARD_UNO
  // chip select control port
  #define LCD_CSConfig()			(DDRB |= (1<<DDB4))
  #define LCD_SelectChip()			(PORTB &= (~(1<<PB4)))
  #define LCD_DeselectChip()		(PORTB |= (1<<PB4))
  // reset control port
  #define LCD_RSTConfig()			(DDRB |= (1<<DDB0))
  #define LCD_ResetChip()			(PORTB &= (~(1<<PB0)))
  #define LCD_ReleaseChip()			(PORTB |= (1<<PB0))
  // read enable control port
  #define LCD_RDConfig()			(DDRB |= (1<<DDB1))
  #define LCD_RDEnable()			(PORTB &= (~(1<<PB1)))
  #define LCD_RDDisable()			(PORTB |= (1<<PB1))
  // write enable control port
  #define LCD_WRConfig()			(DDRB |= (1<<DDB2))
  #define LCD_WREnable()			(PORTB &= (~(1<<PB2)))
  #define LCD_WRDisable()			(PORTB |= (1<<PB2))
  // register select control port
  #define LCD_RSConfig()			(DDRB |= (1<<DDB3))
  #define LCD_RSEnable()			(PORTB &= (~(1<<PB3)))
  #define LCD_RSDisable()			(PORTB |= (1<<PB3))
  // data port
  #define LCD_DataConfig()			do{\
									(DDRD = 0xFF);\
									UCSR0B &= ~((1<<RXEN0));\
									UCSR0B &= ~((1<<TXEN0));\
									}while(0);
#elif MBOARD_MEGA2560
  // memory address allocation for the registers
  #define LCD_CREG					((uint16_t)0x2400)	// RS low
  #define LCD_DREG					((uint16_t)0x2500)	// RS high
  // chip select control port
  #define LCD_CSConfig()			(DDRC |= (1<<DDC6))
  #define LCD_SelectChip()			(PORTC &= (~(1<<PC6)))
  #define LCD_DeselectChip()		(PORTC |= (1<<PC6))
  // reset control port
  #define LCD_RSTConfig()			(DDRC |= (1<<DDC7))
  #define LCD_ResetChip()			(PORTC &= (~(1<<PC7)))
  #define LCD_ReleaseChip()			(PORTC |= (1<<PC7))
#elif MBOARD_CMEGA128
  // memory address allocation for the registers
  #define LCD_CREG					((uint16_t)0x1200)	// RS low
  #define LCD_DREG					((uint16_t)0x1300)	// RS high
  // chip select control port
  #define LCD_CSConfig()			(DDRB |= (1<<DDB5))
  #define LCD_SelectChip()			(PORTB &= (~(1<<PB5)))
  #define LCD_DeselectChip()		(PORTB |= (1<<PB5))
  // reset control port
  #define LCD_RSTConfig()			(DDRB |= (1<<DDB6))
  #define LCD_ResetChip()			(PORTB &= (~(1<<PB6)))
  #define LCD_ReleaseChip()			(PORTB |= (1<<PB6))
#elif MBOARD_CKMAX32

#endif


#if (ILI9325) || (ST7781)
  #define CMD_WRITE_DATA			0x0022
#elif SSD1963

#endif



#if MBOARD_UNO
// 8bit bit banging: asm(nop) is inserted to ensure the timing requirements
#define LCD_SetCtrlReg(c)			do{ \
									(PORTB) &=  ~(0x08);\
									(PORTD) = (uint8_t)((c)>>8);\
									(PORTB) &=  ~(0x04);\
									asm volatile("nop"::);\
									(PORTB) |=  0x04;\
									asm volatile("nop"::);\
									(PORTD) = (uint8_t)(c);\
									(PORTB) &=  ~(0x04);\
									asm volatile("nop"::);\
									(PORTB) |=  0x04;\
									}while(0)
#define LCD_SetDataReg(d)			do{ \
									(PORTB) |=  (0x08);\
									(PORTD) = (uint8_t)((d)>>8);\
									(PORTB) &=  ~(0x04);\
									asm volatile("nop"::);\
									(PORTB) |=  0x04;\
									asm volatile("nop"::);\
									(PORTD) = (uint8_t)(d);\
									(PORTB) &=  ~(0x04);\
									asm volatile("nop"::);\
									(PORTB) |=  0x04;\
									}while(0)
#elif (MBOARD_MEGA2560) || (MBOARD_CMEGA128)
// 8bit memory interface: note that 16bit data is transferred via 8bit bus
#define LCD_SetCtrlReg(c)			do{ \
									*(volatile uint8_t*)(LCD_CREG)=(uint8_t)((c)>>8);\
									*(volatile uint8_t*)(LCD_CREG)=(uint8_t)(c);\
									}while(0)
#define LCD_SetDataReg(d)			do{ \
									*(volatile uint8_t*)(LCD_DREG)=(uint8_t)((d)>>8);\
									*(volatile uint8_t*)(LCD_DREG)=(uint8_t)(d);\
									}while(0)
#endif

#define LCD_SetCtrlDataReg(c,d)		do{ \
									LCD_SetCtrlReg((c));\
									LCD_SetDataReg((d));\
									}while(0)
#if DIR_PORTRAIT
#define LCD_SetHorzWnd(a,b)			do{ \
									LCD_SetCtrlDataReg(0x0050,(a));\
									LCD_SetCtrlDataReg(0x0051,(b));\
									LCD_SetCtrlDataReg(0x0020,(a));\
									}while(0)
#define LCD_SetVertWnd(a,b)			do{ \
									LCD_SetCtrlDataReg(0x0052,(a));\
									LCD_SetCtrlDataReg(0x0053,(b));\
									LCD_SetCtrlDataReg(0x0021,(a));\
									}while(0)
#define LCD_DrawPixel(x,y,c)		do{ \
									LCD_SetHorzWnd(x,x);\
									LCD_SetVertWnd(y,y);\
									LCD_SetCtrlDataReg(CMD_WRITE_DATA,(c));\
									}while(0)
#elif DIR_LANDSCAPE
#if 1
  // for CW LANDSCAPE(mode18)
  #define LCD_SetHorzWnd(a,b)		do{ \
									LCD_SetCtrlDataReg(0x0052,(SCR_WIDTH-(b)-1));\
									LCD_SetCtrlDataReg(0x0053,(SCR_WIDTH-(a)-1));\
									LCD_SetCtrlDataReg(0x0021,(SCR_WIDTH-(b)-1));\
									}while(0)

  #define LCD_SetVertWnd(a,b)		do{ \
									LCD_SetCtrlDataReg(0x0050,(a));\
									LCD_SetCtrlDataReg(0x0051,(b));\
									LCD_SetCtrlDataReg(0x0020,(a));\
									}while(0)
  #else 
  // for CCW LANDSCAPE(mode28)
  #define LCD_SetHorzWnd(a,b)		do{ \
									LCD_SetCtrlDataReg(0x0052,(a));\
									LCD_SetCtrlDataReg(0x0053,(b));\
									LCD_SetCtrlDataReg(0x0021,(a));\
									}while(0)
  #define LCD_SetVertWnd(a,b)		do{ \
									LCD_SetCtrlDataReg(0x0050,(SCR_HEIGHT-(b)-1));\
									LCD_SetCtrlDataReg(0x0051,(SCR_HEIGHT-(a)-1));\
									LCD_SetCtrlDataReg(0x0020,(SCR_HEIGHT-(b)-1));\
									}while(0)
  #endif
#define LCD_DrawPixel(x,y,c)		do{ \
									LCD_SetHorzWnd(x,x);\
									LCD_SetVertWnd(y,y);\
									LCD_SetCtrlDataReg(CMD_WRITE_DATA,(c));\
									}while(0)
#endif
// you can slow down the signal timing by activating this
#define XMEM_DELAY			0

void SdcLCD::initLCD()
{
	uint16_t dummy;

	// deselect the chip before port setting
	LCD_DeselectChip();
	// chip select output(PB5)
	LCD_CSConfig();

	// release the reset before port setting
	LCD_ReleaseChip();
	// reset output(PB6)
	LCD_RSTConfig();

#if MBOARD_UNO
	// read enable 
	LCD_RDDisable();
	LCD_RDConfig();
	// write enable
	LCD_WRDisable();
	LCD_WRConfig();
	// register select
	LCD_RSDisable();
	LCD_RSConfig();
	// data port
	LCD_DataConfig();
#endif

#if MBOARD_MEGA2560
	// enable XMEM
	XMCRA = XMCRA | (1<<SRE);
  #if XMEM_DELAY
	// with some delay
	XMCRA = XMCRA | ((1<<SRW11)|(1<<SRW10)|(1<<SRW01)|(1<<SRW00));
  #endif
	// address bits selection (PC0, PC1)
	XMCRB = ((1<<XMM2) | (1<<XMM1));
#elif MBOARD_CMEGA128
	// enable XMEM
	MCUCR = MCUCR | (1<<SRE);
  #if XMEM_DELAY
	// with some delay
	MCUCR = MCUCR | (1<<SRW10);
	XMCRA = ((1<<SRW11)|(1<<SRW01)|(1<<SRW00));
  #endif
	// address bits selection (PC0, PC1)
	XMCRB = ((1<<XMM2) | (1<<XMM1));
#endif

#if LCD_GR2400 // ILI9325

	_delay_ms(5);

	LCD_ResetChip();
	_delay_ms(50);

	LCD_ReleaseChip();
	_delay_ms(5);

	LCD_SelectChip();

	// ili9325 initialization starts
	LCD_SetCtrlDataReg(0x0001, 0x0100); // SM=0,SS=1
	LCD_SetCtrlDataReg(0x0002, 0x0200); // B/C=1,EOR=0
#if DIR_LANDSCAPE // CW LANDSCAPE (mode18)
	LCD_SetCtrlDataReg(0x0003, 0x1018); // TRI,DFM,HWM,ORG=0,AM=0,BGR=1,I/D=3
#elif DIR_PORTRAIT
	LCD_SetCtrlDataReg(0x0003, 0x1030); // TRI,DFM,HWM,ORG=0,AM=0,BGR=1,I/D=3
#endif
	LCD_SetCtrlDataReg(0x0004, 0x0000); // no resize
	LCD_SetCtrlDataReg(0x0008, 0x0207); // FP=3,BP=7
	LCD_SetCtrlDataReg(0x0009, 0x0000); // PTS,PTG,ICS=0
	LCD_SetCtrlDataReg(0x000A, 0x0000); // FMARKOE,FMI=0
	LCD_SetCtrlDataReg(0x000C, 0x0000); // ENC,RM,DM,RIM=0
	LCD_SetCtrlDataReg(0x000D, 0x0000); // FMP=0
	LCD_SetCtrlDataReg(0x000F, 0x0000); // VSPL,HSPL,EPL,DPL=0

	// power on sequence
	LCD_SetCtrlDataReg(0x0010, 0x0000); // SAP,BT,AP,DSTB,SLP,STB=0
	LCD_SetCtrlDataReg(0x0011, 0x0007); // DC1x,DC0x=0,VC=7
	LCD_SetCtrlDataReg(0x0012, 0x0000); // VCIRE,PON,VRH=0
	LCD_SetCtrlDataReg(0x0013, 0x0000); // VDV=0
	LCD_SetCtrlDataReg(0x0007, 0x0001); // PTDE,BASEE,GON,DTE,CL=0, D=1

	_delay_ms(200);

	LCD_SetCtrlDataReg(0x0010, 0x1690); // SAP=1,BT=6,APE=1,AP=1,DSTB,SLP,STB=0
	LCD_SetCtrlDataReg(0x0011, 0x0227); // DC1x=2,DC0x=2,VC=7

	_delay_ms(50);

	LCD_SetCtrlDataReg(0x0012, 0x000D); // VCIRE=0,PON=0,VRH=D

	_delay_ms(50);

	LCD_SetCtrlDataReg(0x0013, 0x1200); // VDV=12
	LCD_SetCtrlDataReg(0x0029, 0x000A); // VCM=A
	LCD_SetCtrlDataReg(0x002B, 0x000D); // FRS=D

	_delay_ms(50);

	// GRAM initial address counter
	LCD_SetCtrlDataReg(0x0020, 0x0000); // horizontal address
	LCD_SetCtrlDataReg(0x0021, 0x0000); // vertical address

	// gamma curve (original.wintek24.cpt28)
	LCD_SetCtrlDataReg(0x0030, 0x0204);	// 0000.0204.0000
	LCD_SetCtrlDataReg(0x0031, 0x0507); // 0404.0507.0305
	LCD_SetCtrlDataReg(0x0032, 0x0204);	// 0003.0204.0003
	LCD_SetCtrlDataReg(0x0035, 0x0107); // 0405.0107.0304
	LCD_SetCtrlDataReg(0x0036, 0x0207);	// 0808.0207.000F
	LCD_SetCtrlDataReg(0x0037, 0x0305); // 0407.0305.0407
	LCD_SetCtrlDataReg(0x0038, 0x0002);	// 0303.0002.0204
	LCD_SetCtrlDataReg(0x0039, 0x0305); // 0707.0305.0707
	LCD_SetCtrlDataReg(0x003C, 0x0701); // 0504.0701.0403
	LCD_SetCtrlDataReg(0x003D, 0x060A); // 0808.060A.1604

	// GRAM horizontal and vertical RAM positions
	LCD_SetCtrlDataReg(0x0050, 0x0000); // horizontal start address
	LCD_SetCtrlDataReg(0x0051, 0x00EF); // horizontal end address
	LCD_SetCtrlDataReg(0x0052, 0x0000); // vertical start address
	LCD_SetCtrlDataReg(0x0053, 0x013F); // vertical start address
	LCD_SetCtrlDataReg(0x0060, 0xA700); // GS=1,NL=27,SCN=0
	LCD_SetCtrlDataReg(0x0061, 0x0001); // NDL,VLE=0,REV=1
	LCD_SetCtrlDataReg(0x006A, 0x0000); // VL=0

	// partial display
	LCD_SetCtrlDataReg(0x0080, 0x0000);
	LCD_SetCtrlDataReg(0x0081, 0x0000);
	LCD_SetCtrlDataReg(0x0082, 0x0000);
	LCD_SetCtrlDataReg(0x0083, 0x0000);
	LCD_SetCtrlDataReg(0x0084, 0x0000);
	LCD_SetCtrlDataReg(0x0085, 0x0000);

	// Panel Control
	LCD_SetCtrlDataReg(0x0090, 0x0010); // DIV=0,RTNI=10
	LCD_SetCtrlDataReg(0x0092, 0x0000); // NOWI=0
	LCD_SetCtrlDataReg(0x0007, 0x0133); // PTD=0,BASEE=1,GON=1,DTE=1,CL=0,D=3

	LCD_DeselectChip();

#elif LCD_FGD280	// ST7781

	// reset the controller
	_delay_ms(5);

	LCD_ResetChip();
	_delay_ms(5);

	LCD_ReleaseChip();
	_delay_ms(120);

	LCD_SelectChip();

	// ST7781 display control setting
	LCD_SetCtrlDataReg(0x0001, 0x0100); // SM=0,SS=1
	LCD_SetCtrlDataReg(0x0002, 0x0700); // B/C=1,EOR=0
#if DIR_LANDSCAPE // CW LANDSCAPE (mode18)
	LCD_SetCtrlDataReg(0x0003, 0x1018); // TRI,DFM,HWM,ORG=0,AM=0,BGR=1,I/D=3
#elif DIR_PORTRAIT
	LCD_SetCtrlDataReg(0x0003, 0x1030); // TRI,DFM,HWM,ORG=0,AM=0,BGR=1,I/D=3
#endif
	LCD_SetCtrlDataReg(0x0008, 0x0302); // FP=3,BP=7
	LCD_SetCtrlDataReg(0x0009, 0x0000); // PTS,PTG,ICS=0
	LCD_SetCtrlDataReg(0x000A, 0x0000); // FMARKOE,FMI=0

	// power control register initial
	LCD_SetCtrlDataReg(0x0010, 0x0790); // SAP,BT,AP,DSTB,SLP,STB=0
	LCD_SetCtrlDataReg(0x0011, 0x0005); // DC1x,DC0x=0,VC=7
	LCD_SetCtrlDataReg(0x0012, 0x0000); // VCIRE,PON,VRH=0
	LCD_SetCtrlDataReg(0x0013, 0x0000); // VDV=0

	_delay_ms(100);

	LCD_SetCtrlDataReg(0x0010, 0x12B0); // SAP=1,BT=6,APE=1,AP=1,DSTB,SLP,STB=0

	_delay_ms(50);

	LCD_SetCtrlDataReg(0x0011, 0x0007); // DC1x=2,DC0x=2,VC=7

	_delay_ms(50);

	LCD_SetCtrlDataReg(0x0012, 0x008C); // VCIRE=0,PON=0,VRH=D
	LCD_SetCtrlDataReg(0x0013, 0x1700); // VDV=12
	LCD_SetCtrlDataReg(0x0029, 0x001A); // VCM=A

	_delay_ms(50);

	// gamma curve
	LCD_SetCtrlDataReg(0x0030, 0x0000);
	LCD_SetCtrlDataReg(0x0031, 0x0507);
	LCD_SetCtrlDataReg(0x0031, 0x0507);
	LCD_SetCtrlDataReg(0x0032, 0x0003);
	LCD_SetCtrlDataReg(0x0035, 0x0200);
	LCD_SetCtrlDataReg(0x0036, 0x0106);
	LCD_SetCtrlDataReg(0x0037, 0x0000);
	LCD_SetCtrlDataReg(0x0038, 0x0507);
	LCD_SetCtrlDataReg(0x0039, 0x0104);
	LCD_SetCtrlDataReg(0x003C, 0x0200);
	LCD_SetCtrlDataReg(0x003D, 0x0005);

	// GRAM horizontal and vertical RAM positions
	LCD_SetCtrlDataReg(0x0050, 0x0000); // horizontal start address
	LCD_SetCtrlDataReg(0x0051, 0x00EF); // horizontal end address
	LCD_SetCtrlDataReg(0x0052, 0x0000); // vertical start address
	LCD_SetCtrlDataReg(0x0053, 0x013F); // vertical start address

	LCD_SetCtrlDataReg(0x0060, 0xA700); // GS=1,NL=27,SCN=0
	LCD_SetCtrlDataReg(0x0061, 0x0001); // NDL,VLE=0,REV=1

	// Panel Control
	LCD_SetCtrlDataReg(0x0090, 0x0033); // DIV=0,RTNI=10
	LCD_SetCtrlDataReg(0x0007, 0x0133); // PTD=0,BASEE=1,GON=1,DTE=1,CL=0,D=3

	LCD_DeselectChip();

	_delay_ms(50);

#endif

}

void SdcLCD::clearScreen(LCDCOLOR color)
{
	int32_t index = 0;
	const int32_t screenSize = ((int32_t)_screenWidth) * ((int32_t)_screenHeight);

	LCD_SelectChip();

	LCD_SetHorzWnd(0, _screenWidth - 1);
	LCD_SetVertWnd(0, _screenHeight - 1);
	LCD_SetCtrlReg(CMD_WRITE_DATA);

	while( index <  screenSize )
	{
		LCD_SetDataReg(color);
		index++;
	}

	LCD_DeselectChip();
}

void SdcLCD::setForegroundColor(LCDCOLOR color)
{
	_foregroundColor = color;
}

void SdcLCD::setBackgroundColor(LCDCOLOR color)
{
	_backgroundColor = color;
}

void SdcLCD::setPenWidth(int16_t width)
{
	_penWidth = width;
}

int16_t SdcLCD::getScreenWidth(void)
{
	return _screenWidth;
}

int16_t SdcLCD::getScreenHeight(void)
{
	return _screenHeight;
}

void SdcLCD::drawPixel(int16_t x, int16_t y)
{
	LCD_SelectChip();
	LCD_DrawPixel(x, y, _foregroundColor);
	LCD_DeselectChip();
}

void SdcLCD::drawPixel(int16_t x, int16_t y, LCDCOLOR col)
{
	LCD_SelectChip();
	LCD_DrawPixel(x, y, col);
	LCD_DeselectChip();
}

void SdcLCD::drawFilledRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
	int16_t ref_x;

	if(x1 > x2) INTSWAP(x1, x2);
	if(y1 > y2) INTSWAP(y1, y2);

	LCD_SelectChip();

	// define the window
	LCD_SetHorzWnd(x1, x2);
	LCD_SetVertWnd(y1, y2);

	// data write command
	LCD_SetCtrlReg(CMD_WRITE_DATA);

	ref_x = x1;

	while(y1 <= y2)
	{
		while(x1 <= x2)
		{
			LCD_SetDataReg(_foregroundColor);
			x1++;
		}
		y1++;
		x1 = ref_x;
	}

	LCD_DeselectChip();

}

void SdcLCD::drawLine(int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
	int16_t dx = x2 - x1;
	int16_t dy = y2 - y1;

	int16_t s0, s1, sh, num;
	int16_t a0 = _penWidth>>1;
	int16_t a1 = _penWidth - (_penWidth>>1) - 1;

	// 2,3,6,7 octant
	if( ABS(dx) > ABS(dy) )
	{
		// swapping is required
		if(dx < 0)
		{
			INTSWAP(x1, x2);
			INTSWAP(y1, y2);
		}
		dx = x2 - x1;
		dy = y2 - y1;

		// horizontal line (y1 = y2)
		if(dy == 0)
		{
			drawFilledRectangle(x1, y1 - a0, x2, y1 + a1);
			return;
		}
		else if(dy < 0)
		{
			s1 = -1;
			sh = -dy;
		}
		else if(dy > 0)
		{
			s1 = 1;
			sh = dy;
		}

		num = dx >> 1;
		s0 = x1;

		while(x1 < x2)
		{
			num += sh;
			if(!(num < dx))
			{
				drawFilledRectangle(s0, y1 - a0, x1, y1 + a1);
				num -= dx;
				s0 = x1;
				y1 += s1;
			}
			x1++;
		}

		// line ending
//		if( s0 < x2 )
			drawFilledRectangle(s0, y2 - a0, x2, y2 + a1);
	}
	// 1,4,5,8 octant
	else
	{
		// SWAP is required
		if(dy < 0)
		{
			INTSWAP(x1, x2);
			INTSWAP(y1, y2);
		}

		dx = x2 - x1;
		dy = y2 - y1;

		// vertical line (x1 = x2)
		if(dx == 0)
		{
			drawFilledRectangle(x1 - a0, y1, x2 + a1, y2);
			return;
		}
		else if(dx < 0)
		{
			s1 = -1;
			sh = -dx;
		}
		else if(dx > 0)
		{
			s1 = 1;
			sh = dx;
		}

		num = dy >> 1;

		s0 = y1;

		while(y1 < y2)
		{
			num += sh;
			if(!(num < dy))
			{
				drawFilledRectangle(x1 - a0, s0, x1 + a1, y1);
				num -= dy;
				s0 = y1;
				x1 += s1;
			}
			y1++;
		}
		// line ending
//		if( s0 < y2 )
			drawFilledRectangle(x2 - a0, s0, x2 + a1, y2);
	}
}

void SdcLCD::drawRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
	int16_t del = _penWidth>>1;

	// this will fix one pixel misalignment at the corner
	if( _penWidth & 0x1 )
	{
		drawLine(x1, y1, x2 + del, y1);
		drawLine(x2, y1, x2, y2 + del);
	}
	else
	{
		drawLine(x1, y1, x2 + del - 1, y1);
		drawLine(x2, y1, x2, y2 + del - 1);
	}
	drawLine(x2, y2, x1 - del, y2);
	drawLine(x1, y2, x1, y1 - del);
}

void SdcLCD::drawCircle(int16_t x, int16_t y, int16_t r)
{
	int16_t dx, dy, p, ridx;

#if FAST_GRAPHICS

	int16_t dr0 = (_penWidth)>>1;
	int16_t dr1 = (_penWidth - 1)>>1;

#else

	int16_t dr0 = _penWidth;
	int16_t dr1 = _penWidth - 1;

	x = x<<1;
	y = y<<1;
	r = r<<1;

#endif // FAST_GRAPHICS

	ridx = r - dr0;

	while(ridx <= (r + dr1))
	{
		dx = 0;
		dy = ridx;
		p = 1 - ridx;

		while(dx <= dy)
		{

			LCD_SelectChip();
#if FAST_GRAPHICS

			// 4th octant
			LCD_DrawPixel(x + dx, y + dy, _foregroundColor);
			// 5th octant
			LCD_DrawPixel(x - dx, y + dy, _foregroundColor);
			// 1th octant
			LCD_DrawPixel(x + dx, y - dy, _foregroundColor);
			// 8th octant
			LCD_DrawPixel(x - dx, y - dy, _foregroundColor);

			// 3th octant
			LCD_DrawPixel(x + dy, y + dx, _foregroundColor);
			// 6th octant
			LCD_DrawPixel(x - dy, y + dx, _foregroundColor);
			// 2th octant
			LCD_DrawPixel(x + dy, y - dx, _foregroundColor);
			// 7th octant
			LCD_DrawPixel(x - dy, y - dx, _foregroundColor);

#else

			// 4th octant
			LCD_DrawPixel((x + dx)>>1, (y + dy)>>1, _foregroundColor);
			// 5th octant
			LCD_DrawPixel((x - dx)>>1, (y + dy)>>1, _foregroundColor);
			// 1th octant
			LCD_DrawPixel((x + dx)>>1, (y - dy)>>1, _foregroundColor);
			// 8th octant
			LCD_DrawPixel((x - dx)>>1, (y - dy)>>1, _foregroundColor);

			// 3th octant
			LCD_DrawPixel((x + dy)>>1, (y + dx)>>1, _foregroundColor);
			// 6th octant
			LCD_DrawPixel((x - dy)>>1, (y + dx)>>1, _foregroundColor);
			// 2th octant
			LCD_DrawPixel((x + dy)>>1, (y - dx)>>1, _foregroundColor);
			// 7th octant
			LCD_DrawPixel((x - dy)>>1, (y - dx)>>1, _foregroundColor);

#endif // FAST_GRAPHICS
			LCD_DeselectChip();

			dx++;

			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}

		ridx++;
	}

}

void SdcLCD::drawFilledCircle(int16_t x, int16_t y, int16_t r)
{
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;

	while(dx <= dy)
	{
		// vertical filling

		// from 1th to 4th octant
		drawFilledRectangle(x + dx, y - dy, x + dx, y + dy);
		// from 8th to 5th octant
		drawFilledRectangle(x - dx, y - dy, x - dx, y + dy);

		// from 2th to 3th octant
		drawFilledRectangle(x + dy, y - dx, x + dy, y + dx);
		// from 7th to 6th octant
		drawFilledRectangle(x - dy, y - dx, x - dy, y + dx);

		dx++;
		if(p < 0)
			p = p + (dx<<1) + 1;
		else
		{
			dy--;
			p = p + ((dx-dy)<<1) + 1;
		}
	}
}


void SdcLCD::drawEllipse(int16_t x,int16_t y,int16_t a,int16_t b)
{
	int32_t sx, sy, dx, dy, px, py, p;
	int32_t ridx, ridy;

#if FAST_GRAPHICS

	int32_t dr0 = (_penWidth)>>1;
	int32_t dr1 = (_penWidth - 1)>>1;

#else

	int32_t dr0 = _penWidth;
	int32_t dr1 = _penWidth - 1;

	x = x<<1;
	y = y<<1;
	a = a<<1;
	b = b<<1;

#endif // FAST_GRAPHICS

	ridx = a - dr0;
	ridy = b - dr0;

	while(ridx <= (a + dr1))
	{
		sx = ridx * ridx;
		sy = ridy * ridy;
		dx = 0;
		dy = ridy;
		px = 0;
		py = (sx * dy)<<1;

		LCD_SelectChip();

#if FAST_GRAPHICS

		// 2nd quadrant
		LCD_DrawPixel(x + dx, y + dy, _foregroundColor);
		// 3rd quadrant
		LCD_DrawPixel(x - dx, y + dy, _foregroundColor);
		// 1st quadrant
		LCD_DrawPixel(x + dx, y - dy, _foregroundColor);
		// 4th quadrant
		LCD_DrawPixel(x - dx, y - dy, _foregroundColor);

#else

		// 2nd quadrant
		LCD_DrawPixel((x + dx)>>1, (y + dy)>>1, _foregroundColor);
		// 3rd quadrant
		LCD_DrawPixel((x - dx)>>1, (y + dy)>>1, _foregroundColor);
		// 1st quadrant
		LCD_DrawPixel((x + dx)>>1, (y - dy)>>1, _foregroundColor);
		// 4th quadrant
		LCD_DrawPixel((x - dx)>>1, (y - dy)>>1, _foregroundColor);

#endif // FAST_GRAPHICS

		LCD_DeselectChip();

		// region 1
		p = sy - (sx * ridy) + (sx>>2);

		while(px < py)
		{
			dx++;
			px = px + (sy<<1);

			if(p < 0)
				p = p + sy + px;
			else
			{
				dy--;
				py = py - (sx<<1);
				p = p + sy + px - py;
			}

			LCD_SelectChip();

#if FAST_GRAPHICS

			LCD_DrawPixel(x + dx, y + dy, _foregroundColor);
			LCD_DrawPixel(x - dx, y + dy, _foregroundColor);
			LCD_DrawPixel(x + dx, y - dy, _foregroundColor);
			LCD_DrawPixel(x - dx, y - dy, _foregroundColor);

#else

			LCD_DrawPixel((x + dx)>>1, (y + dy)>>1, _foregroundColor);
			LCD_DrawPixel((x - dx)>>1, (y + dy)>>1, _foregroundColor);
			LCD_DrawPixel((x + dx)>>1, (y - dy)>>1, _foregroundColor);
			LCD_DrawPixel((x - dx)>>1, (y - dy)>>1, _foregroundColor);

#endif // FAST_GRAPHICS

			LCD_DeselectChip();

		}

		// region 2
		p = (sy * ((dx<<1) + 1) * ((dx<<1) + 1) + sx * ((dy<<1) - 2) * ((dy<<1) - 2)
			- ((sx * sy)<<2))>>2;

		while(dy > 0)
		{
			dy--;
			py = py - (sx<<1);

			if(p > 0)
				p = p + sx - py;
			else
			{
				dx++;
				px = px + (sy<<1);
				p = p + sx - py + px;
			}

			LCD_SelectChip();

#if FAST_GRAPHICS

			LCD_DrawPixel(x + dx, y + dy, _foregroundColor);
			LCD_DrawPixel(x - dx, y + dy, _foregroundColor);
			LCD_DrawPixel(x + dx, y - dy, _foregroundColor);
			LCD_DrawPixel(x - dx, y - dy, _foregroundColor);
#else

			LCD_DrawPixel((x + dx)>>1, (y + dy)>>1, _foregroundColor);
			LCD_DrawPixel((x - dx)>>1, (y + dy)>>1, _foregroundColor);
			LCD_DrawPixel((x + dx)>>1, (y - dy)>>1, _foregroundColor);
			LCD_DrawPixel((x - dx)>>1, (y - dy)>>1, _foregroundColor);

#endif // FAST_GRAPHICS

			LCD_DeselectChip();

		}

		ridx++;
		ridy++;
	}

}
void SdcLCD::drawFilledEllipse(int16_t x,int16_t y,int16_t a,int16_t b)
{
	int32_t sx = a * a;
	int32_t sy = b * b;

	int32_t dx = 0, dy = b, p;
	int32_t px = 0, py = (sx * dy)<<1;

	// vertical filling

	// from 1st to 2nd quadrant
	drawFilledRectangle(x + dx, y - dy, x + dx, y + dy);
	// from 4th to 3rd quadrant
	drawFilledRectangle(x - dx, y - dy, x - dx, y + dy);

	// region 1
	p = sy - (sx * b) + (sx>>2);

	while(px < py)
	{
		dx++;
		px = px + (sy<<1);

		if(p < 0)
			p = p + sy + px;
		else
		{
			dy--;
			py = py - (sx<<1);
			p = p + sy + px - py;
		}

		drawFilledRectangle(x + dx, y - dy, x + dx, y + dy);
		drawFilledRectangle(x - dx, y - dy, x - dx, y + dy);
	}

	// region 2
	p = (sy * ((dx<<1) + 1) * ((dx<<1) + 1) + sx * ((dy<<1) - 2) * ((dy<<1) - 2)
		- ((sx * sy)<<2))>>2;

	while(dy > 0)
	{
		dy--;
		py = py - (sx<<1);

		if(p > 0)
			p = p + sx - py;
		else
		{
			dx++;
			px = px + (sy<<1);
			p = p + sx - py + px;
		}

		drawFilledRectangle(x + dx, y - dy, x + dx, y + dy);
		drawFilledRectangle(x - dx, y - dy, x - dx, y + dy);
	}
}


void SdcLCD::drawQuadrant(int16_t x,int16_t y,int16_t r,int16_t quad)
{
	int16_t dx, dy, p, ridx, dr0, dr1;

#if FAST_GRAPHICS

	dr0 = (_penWidth)>>1;
	dr1 = (_penWidth - 1)>>1;

#else

	dr0 = _penWidth;
	dr1 = _penWidth - 1;

	x = x<<1;
	y = y<<1;
	r = r<<1;

#endif // FAST_GRAPHICS

	ridx = r - dr0;

	if(quad == 1)
	{
		while(ridx <= (r + dr1))
		{
			dx = 0;
			dy = ridx;
			p = 1 - ridx;

			while(dx <= dy)
			{

				LCD_SelectChip();

#if FAST_GRAPHICS

				// 1th octant
				LCD_DrawPixel(x + dx, y - dy, _foregroundColor);
				// 2th octant
				LCD_DrawPixel(x + dy, y - dx, _foregroundColor);

#else
				LCD_DrawPixel((x + dx)>>1, (y - dy)>>1, _foregroundColor);
				LCD_DrawPixel((x + dy)>>1, (y - dx)>>1, _foregroundColor);

#endif

				LCD_DeselectChip();

				dx++;

				if(p < 0)
					p = p + (dx<<1) + 1;
				else
				{
					dy--;
					p = p + ((dx-dy)<<1) + 1;
				}
			}

			ridx++;
		}
	}
	else if(quad == 2)
	{
		while(ridx <= (r + dr1))
		{
			dx = 0;
			dy = ridx;
			p = 1 - ridx;

			while(dx <= dy)
			{

				LCD_SelectChip();
#if FAST_GRAPHICS

				// 4th octant
				LCD_DrawPixel(x + dx, y + dy, _foregroundColor);
				// 3th octant
				LCD_DrawPixel(x + dy, y + dx, _foregroundColor);

#else

				LCD_DrawPixel((x + dx)>>1, (y + dy)>>1, _foregroundColor);
				LCD_DrawPixel((x + dy)>>1, (y + dx)>>1, _foregroundColor);

#endif

				LCD_DeselectChip();

				dx++;

				if(p < 0)
					p = p + (dx<<1) + 1;
				else
				{
					dy--;
					p = p + ((dx-dy)<<1) + 1;
				}
			}

			ridx++;
		}

	}
	else if(quad == 3)
	{
		while(ridx <= (r + dr1))
		{
			dx = 0;
			dy = ridx;
			p = 1 - ridx;

			while(dx <= dy)
			{
				LCD_SelectChip();

#if FAST_GRAPHICS

				// 5th octant
				LCD_DrawPixel(x - dx, y + dy, _foregroundColor);
				// 6th octant
				LCD_DrawPixel(x - dy, y + dx, _foregroundColor);

#else

				LCD_DrawPixel((x - dx)>>1, (y + dy)>>1, _foregroundColor);
				LCD_DrawPixel((x - dy)>>1, (y + dx)>>1, _foregroundColor);

#endif

				LCD_DeselectChip();

				dx++;

				if(p < 0)
					p = p + (dx<<1) + 1;
				else
				{
					dy--;
					p = p + ((dx-dy)<<1) + 1;
				}
			}

			ridx++;
		}
	}
	else
	{
		while(ridx <= (r + dr1))
		{
			dx = 0;
			dy = ridx;
			p = 1 - ridx;

			while(dx <= dy)
			{

				LCD_SelectChip();

#if FAST_GRAPHICS

				// 8th octant
				LCD_DrawPixel(x - dx, y - dy, _foregroundColor);
				// 7th octant
				LCD_DrawPixel(x - dy, y - dx, _foregroundColor);

#else

				LCD_DrawPixel((x - dx)>>1, (y - dy)>>1, _foregroundColor);
				LCD_DrawPixel((x - dy)>>1, (y - dx)>>1, _foregroundColor);

#endif
				LCD_DeselectChip();

				dx++;

				if(p < 0)
					p = p + (dx<<1) + 1;
				else
				{
					dy--;
					p = p + ((dx-dy)<<1) + 1;
				}
			}

			ridx++;
		}
	}
}
void SdcLCD::drawFilledQuadrant(int16_t x,int16_t y,int16_t r,int16_t quad)
{
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;

	if(quad == 1)
	{
		while(dx <= dy)
		{
			// from 1th octant to the center
			drawFilledRectangle(x + dx, y - dy, x + dx, y);

			// from 2th octant to the center
			drawFilledRectangle(x + dy, y - dx, x + dy, y);

			dx++;
			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}
	}
	else if(quad == 2)
	{
		while(dx <= dy)
		{
			// from the center to 4th octant
			drawFilledRectangle(x + dx, y, x + dx, y + dy);

			// from the center to 3th octant
			drawFilledRectangle(x + dy, y, x + dy, y + dx);

			dx++;
			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}
	}
	else if(quad == 3)
	{
		while(dx <= dy)
		{
			// from the center to 5th octant
			drawFilledRectangle(x - dx, y, x - dx, y + dy);

			// from the center to 6th octant
			drawFilledRectangle(x - dy, y, x - dy, y + dx);

			dx++;
			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}
	}
	else
	{
		while(dx <= dy)
		{
			// from 8th octant to the center
			drawFilledRectangle(x - dx, y - dy, x - dx, y);

			// from 7th octant to the center
			drawFilledRectangle(x - dy, y - dx, x - dy, y);

			dx++;
			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}
	}
}
void SdcLCD::drawRoundRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t r)
{
	int16_t dx, dy, p, ridx, dr0, dr1;

	// two horizontal lines
	drawLine(x1 + r, y1, x2 -r, y1);
	drawLine(x1 + r, y2, x2 -r, y2);
	// two vertical lines
	drawLine(x1, y1 + r, x1, y2 -r);
	drawLine(x2, y1 + r, x2, y2 -r);

#if FAST_GRAPHICS

	dr0 = (_penWidth)>>1;
	dr1 = (_penWidth - 1)>>1;

#else

	dr0 = _penWidth;
	dr1 = _penWidth - 1;

	x1 = x1<<1;
	x2 = x2<<1;
	y1 = y1<<1;
	y2 = y2<<1;
	r = r<<1;

#endif // FAST_GRAPHICS

	ridx = r - dr0;

	// four quadrants
	while(ridx <= (r + dr1))
	{
		dx = 0;
		dy = ridx;
		p = 1 - ridx;

		while(dx <= dy)
		{

			LCD_SelectChip();

#if FAST_GRAPHICS

			// upper right corner
			LCD_DrawPixel(x2 - r + dx, y1 + r - dy, _foregroundColor); // 1th octant
			LCD_DrawPixel(x2 - r + dy, y1 + r - dx, _foregroundColor); // 2nd octant

			// lower right corner
			LCD_DrawPixel(x2 - r + dy, y2 - r + dx, _foregroundColor); // 3rd octant
			LCD_DrawPixel(x2 - r + dx, y2 - r + dy, _foregroundColor); // 4th octant

			// lower left corner
			LCD_DrawPixel(x1 + r - dx, y2 - r + dy, _foregroundColor); // 5th octant
			LCD_DrawPixel(x1 + r - dy, y2 - r + dx, _foregroundColor); // 6th octant

			// upper left corner
			LCD_DrawPixel(x1 + r - dy, y1 + r - dx, _foregroundColor); // 7th octant
			LCD_DrawPixel(x1 + r - dx, y1 + r - dy, _foregroundColor); // 8th octant

#else

			// upper right corner
			LCD_DrawPixel((x2 - r + dx)>>1, (y1 + r - dy)>>1, _foregroundColor);	// 1th
			LCD_DrawPixel((x2 - r + dy)>>1, (y1 + r - dx)>>1, _foregroundColor);	// 2nd

			// lower right corner
			LCD_DrawPixel((x2 - r + dy)>>1, (y2 - r + dx)>>1, _foregroundColor);	// 3rd
			LCD_DrawPixel((x2 - r + dx)>>1, (y2 - r + dy)>>1, _foregroundColor);	// 4th

			// lower left corner
			LCD_DrawPixel((x1 + r - dx)>>1, (y2 - r + dy)>>1, _foregroundColor);	// 5th
			LCD_DrawPixel((x1 + r - dy)>>1, (y2 - r + dx)>>1, _foregroundColor);	// 6th

			// upper left corner
			LCD_DrawPixel((x1 + r - dy)>>1, (y1 + r - dx)>>1, _foregroundColor);	// 7th
			LCD_DrawPixel((x1 + r - dx)>>1, (y1 + r - dy)>>1, _foregroundColor);	// 8th

#endif // FAST_GRAPHICS

			LCD_DeselectChip();

			dx++;

			if(p < 0)
				p = p + (dx<<1) + 1;
			else
			{
				dy--;
				p = p + ((dx-dy)<<1) + 1;
			}
		}

		ridx++;
	}

}


void SdcLCD::drawFilledRoundRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t r)
{
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;

	// four quadrants
	while(dx <= dy)
	{
		// upper right corner : 1st quadrant
		drawFilledRectangle(x2-r+dx, y1+r-dy, x2-r+ dx, y1+r); // 1th octant
		drawFilledRectangle(x2-r+dy, y1+r-dx, x2-r+ dy, y1+r); // 2th octant

		// lower right corner : 2nd quadrant
		drawFilledRectangle(x2-r+dy, y2-r, x2-r+dy, y2-r+dx); // 3th octant
		drawFilledRectangle(x2-r+dx, y2-r, x2-r+dx, y2-r+dy); // 4th octant

		// lower left corner : 3rd quadrant
		drawFilledRectangle(x1+r-dx, y2-r, x1+r-dx, y2-r+dy); // 5th octant
		drawFilledRectangle(x1+r-dy, y2-r, x1+r-dy, y2-r+dx); // 6th octant

		// upper left corner : 4th quadrant
		drawFilledRectangle(x1+r-dy, y1+r-dx, x1+r-dy, y1+r); // 7th octant
		drawFilledRectangle(x1+r-dx, y1+r-dy, x1+r-dx, y1+r); // 8th octant

		dx++;
		if(p < 0)
			p = p + (dx<<1) + 1;
		else
		{
			dy--;
			p = p + ((dx-dy)<<1) + 1;
		}
	}

	// horizontal fill : 1st block
	drawFilledRectangle(x1 + r, y1, x2 - r, y1 + r);
	// horizontal fill : 2nd block
	drawFilledRectangle(x1, y1 + r, x2, y2 - r);
	// horizontal fill : 3rd block
	drawFilledRectangle(x1 + r, y2 - r, x2 - r, y2);
}


void SdcLCD::setFont(LCDFONT* pFont)
{
	_font = pFont;
}

LCDFONT* SdcLCD::getFont(void)
{
	return _font;
}
/**
	\brief  Draws a glyph on LCD.
	\param  Xpos: the Line where to display the character shape.
	\param  Ypos: start column address.
	\param  idx: pointer to the character data.
	\retval	width of the glyph
  */
uint16_t SdcLCD::drawGlyph(int16_t x, int16_t y, const uint8_t *idx)
{
	unsigned int i, column, k = 0, width, line;
	uint8_t chbyte = 0;

	// font width in pixel
	width = idx[0];

	// pixel by pixel drawing
	if( _backgroundColor == LCD_COLOR_TRANSPARENT )
	{
		i = 1;
		line = 0;
		LCD_SelectChip();

		while(line < _font->Height)
		{
			// one line of glyph
			column = 0;
			while(column < width)
			{
				if(column < 8)
				{
					chbyte = idx[i];
					k = column;
				}
				else if(column < 16)
				{
					chbyte = idx[i+1];
					k = column - 8;
				}
				else if(column < 24)
				{
					chbyte = idx[i+2];
					k = column - 16;
				}
				else if(column < 32)
				{
					chbyte = idx[i+3];
					k = column - 24;
				}
				// font data error
				else
				{
				}

				if(chbyte & (0x80 >> k))
				{
					LCD_DrawPixel(x+column, y+line, _foregroundColor);
				}
				column++;
			}
			i = i+ _font->WidthBytes;
			line++;
		}

		LCD_DeselectChip();
	}
	else
	{
		LCD_SelectChip();

		// set column page address
		LCD_SetHorzWnd(x, x + width - 1);
		LCD_SetVertWnd(y, y + _font->Height - 1);

		// start data transfer
		LCD_SetCtrlReg(CMD_WRITE_DATA);

		i = 1;
		line = 0;

		while(line < _font->Height)
		{
			column = 0;

			while(column < width)
			{
				if(column < 8)
				{
					chbyte = idx[i];
					k = column;
				}
				else if(column < 16)
				{
					chbyte = idx[i+1];
					k = column - 8;
				}
				else if(column < 24)
				{
					chbyte = idx[i+2];
					k = column - 16;
				}
				else if(column < 32)
				{
					chbyte = idx[i+3];
					k = column - 24;
				}
				// font data error
				else
				{
				}

				if(chbyte & (0x80 >> k))
				{
					LCD_SetDataReg(_foregroundColor);
				}
				else
				{
					LCD_SetDataReg(_backgroundColor);
				}

				column++;
			}

			i = i + _font->WidthBytes;
			line++;
		}

		LCD_DeselectChip();
	}

	return width;
}


/**
	\brief  Display one character
	\param  x,y : starting point
	\param  ch : character ascii code, must be between 0x20 and 0x7E.
	\retval	width of the glyph
  */
uint16_t SdcLCD::drawCharacter(int16_t x, int16_t y, char ch)
{
	unsigned int index = 0;

	// replace unprintable characters to space
	if((ch < ' ') || (ch > '~'))
		return _font->table[0];

	if((x > _screenWidth) || (y > _screenHeight))
		return 0;

	ch -= ' ';

	// find the font glyph data starting point
	while( ch > 0 )
	{
		index += (_font->Height)*(_font->WidthBytes) + 1;
		ch--;
	}

	return drawGlyph(x, y, &_font->table[index]);
}

/**
	\brief  Display a maximum of 20 char on the LCD.
	\param	x,y : starting point
	\param  *ptr: pointer to string to display on LCD.
	\retval total pixel width of the text drawn
  */
uint16_t SdcLCD::drawString(int16_t x, int16_t y, char *str)
{
	unsigned int width, length = 0;

	// Send the string character by character on lCD
	while ((*str != 0) )
	{
		// Display one character on LCD
		width = drawCharacter(x, y, *str);

		// proceed to next character position
		if(width == 0)
			break;
		else
			x += width;

		// point on the next character
		str++;
		length += width;
	}

	return length;
}

static unsigned long pow10(unsigned y)
{
	unsigned long val = 10;

	if(y == 0) return 1;
	else if(y == 1) return 10;
	y--;
	
	while(y)
	{
		val *= 10;
		y--;
	}
	return val;
}
/**
	\brief  Display a number
	\param	x,y: starting point
	\param  num: number to display
	\retval total pixel width of the text drawn
  */
uint16_t SdcLCD::drawNumber(int16_t x, int16_t y, unsigned long num)
{
	uint8_t index = 0;
	uint16_t width, length = 0;
	unsigned long val = num;

	// how many digits?
	while(val)
	{
		val = val/10;
		index++;
	}

	while(index)
	{
		// Display one character on LCD
		val = num / pow10(index - 1);
		width = drawCharacter(x, y, val + '0');

		// proceed to next character position
		if(width == 0)
			break;
		else
			x += width;

		// point on the next character
		num = num - val * pow10(index - 1);
		index--;
		length += width;
	}

	return length;
}

/**
	\brief	Set a window area for block write. Note that CMD_WRITE_DATA
			command is already invoked here.
	\param	x1,y1: upper left corner of the window
	\param	x2,y2: lower right corner of the window
	\retval	none
 */
void SdcLCD::setBlockArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	LCD_SelectChip();
	LCD_SetHorzWnd(x1, x2);
	LCD_SetVertWnd(y1, y2);
	// note the write data command here
	LCD_SetCtrlReg(CMD_WRITE_DATA);
	LCD_ReleaseChip();
}

void SdcLCD::drawBmpBlock(uint8_t* buff, uint16_t nPixel)
{
	uint16_t idx = 0;
	PRGBTRIPLE prgb = (PRGBTRIPLE)buff;

	LCD_SelectChip();
	// actual write data command should be found in the setBlockArea()
//	LCD_SetCtrlReg(CMD_WRITE_DATA);

	while(idx < nPixel)
	{
		LCD_SetDataReg(LCD_COLOR((prgb + idx)->rgbtRed,
			(prgb + idx)->rgbtGreen, (prgb + idx)->rgbtBlue));
		idx++; 
	}
	LCD_ReleaseChip();
}

void SdcLCD::drawRawBlock(uint8_t* buff, uint16_t nPixel)
{
	uint16_t idx = 0;
	LCDCOLOR *pCol = (LCDCOLOR*)buff;

	LCD_SelectChip();
	// actual write data command should be found in the setBlockArea()
//	LCD_SetCtrlReg(CMD_WRITE_DATA);

	while(idx < nPixel)
	{
		LCD_SetDataReg(*(pCol + idx));
		idx++;
	}
	LCD_ReleaseChip();
}

/**
	\}
 */

