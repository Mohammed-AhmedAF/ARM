#ifndef _APP_INTERFACE_H
#define _APP_INTERFACE_H

#define APP_COUNT_UP 1
#define APP_COUNT_DOWN 2
#define APP_COUNT_STOP 0

typedef struct 
{
	u8 u8ID;
	u8 u8Seconds;
	u8 u8Minutes;
	u8 u8Hours;
}TimeData_t;


void vidBlink(void);
void vidCountDown(void);
void vidReceiveMessage(void);
void vidResetStopWatch(void);
void vidProcessButtons(void);
void vidReceiveMessage_dev(void);
void vidProcessMessage(u8 u8MessageLength, u8 * u8MessagePtr);

#endif