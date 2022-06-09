/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Clock application module
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"
#include "CLOCK_interface.h"

/*Global variables modified in ISR*/
volatile u8 u8AlarmFlag = CLOCK_ALARM_CLEARED;
volatile u32 u32OvFCount;
volatile u8 u8Sec = 0;
volatile u8 u8Minute = 33;
volatile u8 u8Hours = 21;
volatile u8 u8AlarmMinute = 35;


/*This function will initiate the clock*/


void CLOCK_vidCount(void) {
	u32OvFCount++;
	if (u32OvFCount == CLOCK_SEC_OVFCOUNT) {
		u32OvFCount = 0;
		u8Sec++;
		if (u8Sec == 60) {
			u8Sec = 0;
			u8Minute++;
			if (u8AlarmFlag == CLOCK_ALARM_SET) {
				CLOCK_vidCheckAlarm();
			}
			if (u8Minute == 60) {
				u8Minute = 0;
				u8Hours++;
				if (u8Hours == 23) {
					u8Hours = 0;
				}
			}
		}
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS0,LCD_YPOS1,u8Hours/10+'0');	
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS1,LCD_YPOS1,u8Hours%10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS2,LCD_YPOS1,':');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS3,LCD_YPOS1,u8Minute/10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS4,LCD_YPOS1,u8Minute%10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS5,LCD_YPOS1,':');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS6,LCD_YPOS1,u8Sec/10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS7,LCD_YPOS1,u8Sec%10+'0');
#ifdef CLOCK_AMPM_SWITCH
		if (u8Hours <= 12) {
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS9,LCD_YPOS1,'A');
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS10,LCD_YPOS1,'M');
		}
		else {
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS9,LCD_YPOS1,'P');
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS10,LCD_YPOS1,'M');
		}
#endif
	}

}

void CLOCK_vidIncrementHours(void) {
	u8Hours++;
}

void CLOCK_vidIncrementMinutes(void) {
	u8Minute++;
}

/*
 * This function will be called every minute to check if alarm
 *value has been reached.
 * */
void CLOCK_vidCheckAlarm(void) {
	if (u8Minute == u8AlarmMinute) {
		LCD_vidGoToXY(1,2);
		LCD_vidWriteString("Alarm");
	}
}

/*Function for setting the clock
 *Called by external interrupt
 * */
void CLOCK_vidSetClock(void) {
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidWriteString("Hours: \0");
}
