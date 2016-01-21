/**
	\defgroup	ARDUINO_LCDFONTS
	\ingroup	ARDUINO
	\brief		Font definition file for SDCLCD
	\author		Sungjune Lee
	\date		Thu May 10 16:41:12 EDT 2012

	Version History
	==============================================================================
	v1.0: (10 May 2012) Initial release.

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#ifndef __LCDFONTS_H
#define __LCDFONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct _lcdfont
{    
  uint8_t WidthBytes;		/* number of bytes for a row */
  uint8_t Height;
  const uint8_t *table;
} LCDFONT;

extern LCDFONT DroidSans_10;
extern LCDFONT DroidSans_12;
extern LCDFONT DroidSans_14;
extern LCDFONT DroidSans_16;
extern LCDFONT DroidSans_18;
extern LCDFONT DroidSans_20;
extern LCDFONT DroidSans_Bold_10;
extern LCDFONT DroidSans_Bold_12;
extern LCDFONT DroidSans_Bold_14;
extern LCDFONT DroidSans_Bold_16;
extern LCDFONT DroidSans_Bold_18;
extern LCDFONT DroidSans_Bold_20;
extern LCDFONT DroidSerif_10;
extern LCDFONT DroidSerif_12;
extern LCDFONT DroidSerif_14;
extern LCDFONT DroidSerif_16;
extern LCDFONT DroidSerif_18;
extern LCDFONT DroidSerif_20;
extern LCDFONT DroidSerif_Bold_10;
extern LCDFONT DroidSerif_Bold_12;
extern LCDFONT DroidSerif_Bold_14;
extern LCDFONT DroidSerif_Bold_16;
extern LCDFONT DroidSerif_Bold_18;
extern LCDFONT DroidSerif_Bold_20;
extern LCDFONT DroidSerif_Italic_10;
extern LCDFONT DroidSerif_Italic_12;
extern LCDFONT DroidSerif_Italic_14;
extern LCDFONT DroidSerif_Italic_16;
extern LCDFONT DroidSerif_Italic_18;
extern LCDFONT DroidSerif_Italic_20;
extern LCDFONT Federant_10;
extern LCDFONT Federant_12;
extern LCDFONT Federant_14;
extern LCDFONT Federant_16;
extern LCDFONT Federant_18;
extern LCDFONT Federant_20;
extern LCDFONT LiberationSans_10;
extern LCDFONT LiberationSans_12;
extern LCDFONT LiberationSans_14;
extern LCDFONT LiberationSans_16;
extern LCDFONT LiberationSans_18;
extern LCDFONT LiberationSans_20;
extern LCDFONT LiberationSerif_10;
extern LCDFONT LiberationSerif_12;
extern LCDFONT LiberationSerif_14;
extern LCDFONT LiberationSerif_16;
extern LCDFONT LiberationSerif_18;
extern LCDFONT LiberationSerif_20;
extern LCDFONT LiberationSerif_Italic_10;
extern LCDFONT LiberationSerif_Italic_12;
extern LCDFONT LiberationSerif_Italic_14;
extern LCDFONT LiberationSerif_Italic_16;
extern LCDFONT LiberationSerif_Italic_18;
extern LCDFONT LiberationSerif_Italic_20;
extern LCDFONT Ubuntu_10;
extern LCDFONT Ubuntu_12;
extern LCDFONT Ubuntu_14;
extern LCDFONT Ubuntu_16;
extern LCDFONT Ubuntu_18;
extern LCDFONT Ubuntu_20;
extern LCDFONT Ubuntu_Bold_10;
extern LCDFONT Ubuntu_Bold_12;
extern LCDFONT Ubuntu_Bold_14;
extern LCDFONT Ubuntu_Bold_16;
extern LCDFONT Ubuntu_Bold_18;
extern LCDFONT Ubuntu_Bold_20;
extern LCDFONT Ubuntu_Italic_10;
extern LCDFONT Ubuntu_Italic_12;
extern LCDFONT Ubuntu_Italic_14;
extern LCDFONT Ubuntu_Italic_16;
extern LCDFONT Ubuntu_Italic_18;
extern LCDFONT Ubuntu_Italic_20;

#ifdef __cplusplus
}
#endif
  
#endif /* __LCDFONTS_H */
 
/**
	\}
 */

