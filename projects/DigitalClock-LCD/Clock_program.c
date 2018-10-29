/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: This a clock module, it is used
 * to display clock in hours, minutes, and seconds.
 * Date: 29-10-2018
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MDIO_interface.h"
#include "ELCD_interface.h"
#include "Clock_interface.h"

#define SHIFT 4


/*Global variables*/
volatile u8 hour = 0;
volatile u8 min = 0;
volatile u16 sec = 0;
volatile u32 u32OVFCount = 0;
volatile u8 Flag = 0;
volatile u8 u8AlarmMin = 5;


void vidCount(void) {
	u32OVFCount++;
	if (u32OVFCount == 31250) {
		u32OVFCount = 0;
		sec++;
		if (sec < 60) {
			/*Writing seconds*/
			ELCD_vidGoToXY(6+SHIFT,0);
			ELCD_vidWriteNumber(sec/10);
			ELCD_vidGoToXY(7+SHIFT,0);
			ELCD_vidWriteNumber(sec%10);
		}
		else {
			sec = 0;
			ELCD_vidGoToXY(6+SHIFT,0);
			ELCD_vidWriteCharacter('0');
			ELCD_vidGoToXY(7+SHIFT,0);
			ELCD_vidWriteCharacter('0');
			min++;
			if (min < 60) {
				/*Writing minutes*/
				ELCD_vidGoToXY(3+SHIFT,0);
				ELCD_vidWriteNumber(min/10);
				ELCD_vidGoToXY(4+SHIFT,0);
				ELCD_vidWriteNumber(min%10);
			}
			else  {
				min = 0;
				ELCD_vidGoToXY(3+SHIFT,0);
				ELCD_vidWriteNumber(min/10);
				ELCD_vidGoToXY(4+SHIFT,0);
				ELCD_vidWriteNumber(min%10);
				hour++;
				if (hour < 24) {
					/*Writing hours*/
					ELCD_vidGoToXY(0+SHIFT,0);
					ELCD_vidWriteNumber(hour/10);
					ELCD_vidGoToXY(1+SHIFT,0);
					ELCD_vidWriteNumber(hour%10);
				}
				else {
					hour = 0;
					ELCD_vidGoToXY(0+SHIFT,0);
					ELCD_vidWriteNumber(hour/10);
					ELCD_vidGoToXY(1+SHIFT,0);
					ELCD_vidWriteNumber(hour%10);
				}
			}
		}
	}
}

void displayCount(void) {
	++u32OVFCount;
	if (u32OVFCount == 10000) {
		ELCD_vidSendCommand(ELCD_CLEAR_SCREEN);
		ELCD_vidSendCommand(ELCD_RETURN_HOME);
		u32OVFCount = 0;
		++sec;
		ELCD_vidWriteNumber(sec);
	}
}

void vidIncrementHour(void) {
	hour++;
	if (hour > 24) {
		hour = 0;
	}
	ELCD_vidGoToXY(0+SHIFT,0);
	ELCD_vidWriteNumber(hour/10);
	ELCD_vidGoToXY(1+SHIFT,0);
	ELCD_vidWriteNumber(hour%10);
}


void vidIncrementMinute(void) {
	min++;
	if (min > 59) {
		min = 0;
	}
	ELCD_vidGoToXY(3+SHIFT,0);
	ELCD_vidWriteNumber(min/10);
	ELCD_vidGoToXY(4+SHIFT,0);
	ELCD_vidWriteNumber(min%10);
}

void vidInitClock(void) {
	ELCD_vidWriteInPlace(0+SHIFT,'0');
	ELCD_vidWriteInPlace(1+SHIFT,'0');
	ELCD_vidWriteInPlace(2+SHIFT,':');
	ELCD_vidWriteInPlace(3+SHIFT,min/10+'0');
	ELCD_vidWriteInPlace(4+SHIFT,min%10+'0');
	ELCD_vidWriteInPlace(5+SHIFT,':');
	ELCD_vidWriteInPlace(6+SHIFT,'0');
	ELCD_vidWriteInPlace(7+SHIFT,'0');
}

void vidCheckMinute(u8 u8MinCpy) {
	if (u8AlarmMin == u8MinCpy) {
		MDIO_vidSetPinValue(MDIO_PORTB,MDIO_PIN3,STD_HIGH);
	}
}

void vidSetAlarm(void) {
	ELCD_vidSendCommand(ELCD_CLEAR_SCREEN);
	ELCD_vidSendCommand(ELCD_RETURN_HOME);
	ELCD_vidWriteString((u8*)"Minutes: \0");	
	ELCD_vidGoToXY(0,1);
	ELCD_vidWriteString((u8*)"Hours: \0");
	ELCD_vidGoToXY(10,0);

}

