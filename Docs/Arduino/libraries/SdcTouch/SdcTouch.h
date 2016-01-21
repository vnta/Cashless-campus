/**
	\defgroup	ARDUINO_SDCTOUCH
	\ingroup	ARDUINO
	\brief		Resistive touch sensor interface for Arduino
	\author		Sungjune Lee
	\date		Wed May 30 16:39:18 EDT 2012

	\verbatim
	Programming Example
	==============================================================================
	// If you haven't you need to run "Calibrate" example at least once to
	// get the correct calibration parameters for your setting. Otherwise all the 
	// screen coordinate value are invalid.
	//
	// class definition on the heap
	SdcTouch touch;

	// wait indefinitely for the touch event
	touch.waitForSingleEvent();

	// then get the screen coordinates
	x = touch.getScrX();
	y = touch.getScrY();

	// you can do polling instead of waiting event.  this feature is particularly 
	// useful when you follow the trajectory of continuous touch.
	if( touch.checkTouchContinuous() )
	{
		x = touch.getScrX();
		y = touch.getScrY();
	}
	else
	{
		// user does not touch the screen at the moment
	}

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */
#ifndef SDCTOUCH_h
#define SDCTOUCH_h

#include <inttypes.h>

#define RAW_READ_TEST				0		// For test purpose only
#define EEADDR_TOUCHPARAM			0x100	// EEPROM address for the parameters

enum {TOUCH_WAIT = 0, TOUCH_DETECTED = 1};

class SdcTouch {
public:
	// constructor
	SdcTouch();

#if RAW_READ_TEST
	// get the raw ADC input value
	uint8_t getRawX(void);
	uint8_t getRawY(void);
	uint8_t getRawZ(void);
#endif

	// get calibrated screen coordinate
	int16_t getScrX(void);
	int16_t getScrY(void);

	// wait for touch event indefinitely
	void waitForSingleTouch(void);
	// check the z value for touch detection
	bool checkTouchContinuous(void);
	// measure the raw touch value with ADC
	bool measure(void);
	// save calibration parameters
	void saveParameters(void);
	// load calibration parameters
	void loadParameters(void);

	// this value is exposed for the calibration 
	uint16_t raw_x;
	uint16_t raw_y;
	uint16_t raw_z;

	// calibration parameters
	int32_t p[7];	
};


#endif // SDCTOUCH_h
/**
	\}
 */

