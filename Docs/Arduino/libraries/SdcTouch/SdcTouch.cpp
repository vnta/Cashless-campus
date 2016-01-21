/**
	\addtogroup	ARDUINO_SDCTOUCH

	\{
 */

/*
	Copyright(c) 2012 Sungjune Lee.  This work is licensed under a 
	Creative Commons Attribution-NonCommercial-NoDerives 3.0 Unported License.
	For more information about the license, please visit
	http://creativecommons.org/licenses/by-nc-nd/3.0/
 */

#include "SdcTouch.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define ORDER_AVG					4		// how many measuremt? 2^4 = 16
#define MAX_ADCVAL					(0x0FF)	// maximum ADC value
#define MIN_ZVALUE					10

#if defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
	#define MEASURE_XPOS(x)			do{\
									PORTK |= (1<<PK0);DDRK |= (1<<DDK0);\
									PORTK &= ~(1<<PK1);DDRK |= (1<<DDK1);\
									PORTK &= ~(1<<PK2);DDRK &= ~(1<<DDK2);\
									PORTK &= ~(1<<PK3);DDRK &= ~(1<<DDK3);\
									ADMUX = 0x62;\
									ADCSRB = (ADCSRB & 0x40) + 0x08;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_YPOS(x)			do{\
									PORTK &= ~(1<<PK0);DDRK &= ~(1<<DDK0);\
									PORTK &= ~(1<<PK1);DDRK &= ~(1<<DDK1);\
									PORTK |= (1<<PK2);DDRK |= (1<<DDK2);\
									PORTK &= ~(1<<PK3);DDRK |= (1<<DDK3);\
									ADMUX = 0x61;\
									ADCSRB = (ADCSRB & 0x40) + 0x08;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_Z1PR(x)			do{\
									PORTK &= ~(1<<PK0);DDRK &= ~(1<<DDK0);\
									PORTK &= ~(1<<PK1);DDRK |= (1<<DDK1);\
									PORTK |= (1<<PK2);DDRK |= (1<<DDK2);\
									PORTK &= ~(1<<PK3);DDRK &= ~(1<<DDK3);\
									ADMUX = 0x60;\
									ADCSRB = (ADCSRB & 0x40) + 0x08;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_Z2PR(x)			do{\
									PORTK &= ~(1<<PK0);DDRK &= ~(1<<DDK0);\
									PORTK &= ~(1<<PK1);DDRK |= (1<<DDK1);\
									PORTK |= (1<<PK2);DDRK |= (1<<DDK2);\
									PORTK &= ~(1<<PK3);DDRK &= ~(1<<DDK3);\
									ADMUX = 0x63;\
									ADCSRB = (ADCSRB & 0x40) + 0x08;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	// PK0 - 
	// PK1 - PCINT17
	// PK2 - 
	// PK3 -
	#define ENABLE_PCINT()			do{\
									PORTK |= (1<<PK0);DDRK |= (1<<DDK0);\
									PORTK &= ~(1<<PK1);DDRK |= (1<<DDK1);\
									PORTK &= ~(1<<PK2);DDRK &= ~(1<<DDK2);\
									PORTK |= ~(1<<PK3);DDRK &= ~(1<<DDK3);\
									ADMUX = 0x5F;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									_delay_ms(1);\
									PCICR |= (1<<PCIE2);\
									PCMSK2 |= (1<<PCINT17);\
									}while(0)
	#define PCINT_VECTOR			PCINT2_vect
	#define DISABLE_PCINT()			do{\
									PCICR &= ~(1<<PCIE2);\
									PCMSK2 &= ~(1<<PCINT17);\
									}while(0)

#elif defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)

	#define MEASURE_XPOS(x)			do{\
									PORTC |= (1<<PC0);DDRC |= (1<<DDC0);\
									PORTC &= ~(1<<PC1);DDRC |= (1<<DDC1);\
									PORTC &= ~(1<<PC2);DDRC &= ~(1<<DDC2);\
									PORTC &= ~(1<<PC3);DDRC &= ~(1<<DDC3);\
									ADMUX = 0x62;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_YPOS(x)			do{\
									PORTC &= ~(1<<PC0);DDRC &= ~(1<<DDC0);\
									PORTC &= ~(1<<PC1);DDRC &= ~(1<<DDC1);\
									PORTC |= (1<<PC2);DDRC |= (1<<DDC2);\
									PORTC &= ~(1<<PC3);DDRC |= (1<<DDC3);\
									ADMUX = 0x61;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_Z1PR(x)			do{\
									PORTC &= ~(1<<PC0);DDRC &= ~(1<<DDC0);\
									PORTC &= ~(1<<PC1);DDRC |= (1<<DDC1);\
									PORTC |= (1<<PC2);DDRC |= (1<<DDC2);\
									PORTC &= ~(1<<PC3);DDRC &= ~(1<<DDC3);\
									ADMUX = 0x60;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	#define MEASURE_Z2PR(x)			do{\
									PORTC &= ~(1<<PC0);DDRC &= ~(1<<DDC0);\
									PORTC &= ~(1<<PC1);DDRC |= (1<<DDC1);\
									PORTC |= (1<<PC2);DDRC |= (1<<DDC2);\
									PORTC &= ~(1<<PC3);DDRC &= ~(1<<DDC3);\
									ADMUX = 0x63;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									ADCSRA |= (1<<ADSC);\
									while(ADCSRA & (1<<ADSC));\
									x = ADCH;\
									}while(0)
	// PC0 - 
	// PC1 - PCINT9
	// PC2 -
	// PC3 - 
	#define ENABLE_PCINT()			do{\
									PORTC |= (1<<PC0);DDRC &= ~(1<<DDC0);\
									PORTC &= ~(1<<PC1);DDRC &= ~(1<<DDC1);\
									PORTC &= ~(1<<PC2);DDRC &= ~(1<<DDC2);\
									PORTC &= ~(1<<PC3);DDRC |= (1<<DDC3);\
									ADMUX = 0x4F;\
									ADCSRB = (ADCSRB & 0x40) + 0x00;\
									_delay_ms(1);\
									PCICR |= (1<<PCIE1);\
									PCMSK1 |= (1<<PCINT9);\
									}while(0)
	#define PCINT_VECTOR			PCINT1_vect
	// disable interrupt
	#define DISABLE_PCINT()			do{\
									PCICR &= ~(1<<PCIE1);\
									PCMSK1 &= ~(1<<PCINT9);\
									}while(0)

#endif

static volatile uint8_t touch_flag = TOUCH_WAIT;

SdcTouch::SdcTouch()
{
	// initialize the ADC
	ADCSRA |= (1<<ADEN);

	// load calibration parameters
	loadParameters();
}


ISR(PCINT_VECTOR)
{
	touch_flag = TOUCH_DETECTED;
}

void SdcTouch::waitForSingleTouch(void)
{
	uint8_t tmpz1, tmpz2;

	touch_flag = TOUCH_WAIT;
	ENABLE_PCINT();

	while(touch_flag == TOUCH_WAIT);
	{
		_delay_ms(10);
	}

	DISABLE_PCINT();

	do{
		// z2 measurement
		MEASURE_Z2PR(tmpz1);
		// z1 measurement
		MEASURE_Z1PR(tmpz2);
		// convert z
		tmpz1 = MAX_ADCVAL - tmpz1 + tmpz2;
	} while (tmpz1 < MIN_ZVALUE);

	measure();
}

bool SdcTouch::checkTouchContinuous(void)
{
	uint8_t tmpz1, tmpz2;

	// z2 measurement
	MEASURE_Z2PR(tmpz1);
	// z1 measurement
	MEASURE_Z1PR(tmpz2);
	// convert z
	tmpz1 = MAX_ADCVAL - tmpz1 + tmpz2;

	if (tmpz1 < MIN_ZVALUE)
		return false;
	else
	{
		return measure();
	}
}


bool SdcTouch::measure(void)
{
	uint8_t tmpx, tmpy, tmpz1, tmpz2, count;
	uint16_t sumx, sumy, sumz;

#if 0
	// wait until meaningful z values are measured
	do
	{
		// z2 measurement
		MEASURE_Z2PR(tmpz1);
		// z1 measurement
		MEASURE_Z1PR(tmpz2);
		// convert z
		tmpz1 = MAX_ADCVAL - tmpz1 + tmpz2;
	}
	while(tmpz1 < MIN_ZVALUE);
#endif

	sumx = sumy = sumz = 0;
	count = (1<<ORDER_AVG);

	while(count)
	{
		// x measurement
		MEASURE_XPOS(tmpx);
		// y measurement
		MEASURE_YPOS(tmpy);
		// z2 measurement
		MEASURE_Z2PR(tmpz1);
		// z1 measurement
		MEASURE_Z1PR(tmpz2);
		// convert z
		tmpz1 = MAX_ADCVAL - tmpz1 + tmpz2;
		
		if(tmpz1 < MIN_ZVALUE)
			return false;

		// add to the sum
		sumx += tmpx;
		sumy += tmpy;
		sumz += tmpz1;

		count--;
	}

	raw_x = sumx>>ORDER_AVG;
	raw_y = sumy>>ORDER_AVG;
	raw_z = sumz>>ORDER_AVG;

	return true;
}


void SdcTouch::saveParameters(void)
{
	eeprom_write_block(p, (int32_t*)EEADDR_TOUCHPARAM, 7 * sizeof(int32_t));
}

void SdcTouch::loadParameters(void)
{
	eeprom_read_block(p, (int32_t*)EEADDR_TOUCHPARAM, 7 * sizeof(int32_t));
}

int16_t SdcTouch::getScrX(void)
{
	return (int16_t)((p[0]*((int32_t)raw_x) + p[1]*((int32_t)raw_y) + p[2])/p[6]);
}

int16_t SdcTouch::getScrY(void)
{
	return (int16_t)((p[3]*((int32_t)raw_x) + p[4]*((int32_t)raw_y) + p[5])/p[6]);
}

#if RAW_READ_TEST

uint8_t SdcTouch::getRawX(void)
{
	uint8_t val, count;
	uint16_t sum = 0;

	// port setup  for x axis measurement
	MEASURE_XPOS(val);

	count = (1<<ORDER_AVG);
	while(count)
	{
		MEASURE_XPOS(val);
		sum += val;

		count--;
	}

	return (sum>>ORDER_AVG);
}

uint8_t SdcTouch::getRawY(void)
{
	uint8_t val, count;
	uint16_t sum = 0;

	// port setup  for x axis measurement
	MEASURE_YPOS(val);

	count = (1<<ORDER_AVG);
	while(count)
	{
		MEASURE_YPOS(val);
		sum += val;

		count--;
	}

	return (sum>>ORDER_AVG);
}


uint8_t SdcTouch::getRawZ(void)
{
	uint8_t val, count;
	uint16_t sum = 0;

	// port setup  for x axis measurement
	MEASURE_Z2PR(val);

	count = (1<<ORDER_AVG);
	while(count)
	{
		MEASURE_Z2PR(val);
		sum += val;

		MEASURE_Z1PR(val);
		sum -= val;

		count--;
	}

	return (MAX_ADCVAL - (sum>>ORDER_AVG));
}

#endif // RAW_READ_TEST

/**
	\}
 */

