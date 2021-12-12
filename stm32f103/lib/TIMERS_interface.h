/*
 * TIMERS_interface.h
 *
 *  Created on: Dec 12, 2021
 *      Author: Mohammed
 */

#ifndef INC_TIMERS_INTERFACE_H_
#define INC_TIMERS_INTERFACE_H_

typedef struct {
	uint16_t u16ReloadValue;
	uint8_t u8TimerID;
	uint8_t u8CountDir;
	uint8_t u8Interrupt;
	void (*ptrFCalback) (void);
}TIMERConfig_t;


/*Function declarations*/
void TIMERS_vidInit(TIMERConfig_t * TIMERConfig);
void TIMERS_vidPutISRFunction(uint8_t u8TimerID, void (*ptrF) (void));
void TIMERS_vidSetReloadValue(uint8_t u8TimerID, uint16_t u16Value);
void TIMERS_vidEnableTimer(uint8_t u8TimerID);
void TIMERS_vidDisableTimer(uint8_t u8TimerID);
void TIMERS_vidEnableInterrupt(uint8_t u8TimerID,uint8_t u8Interrupt);

/*Macro definitions*/
#define TIMERS_TIMER_1 1
#define TIMERS_TIMER_2 2
#define TIMERS_TIMER_3 3
#define TIMERS_TIMER_4 4
#define TIMERS_TIMER_5 5
#define TIMERS_TIMER_6 6
#define TIMERS_TIMER_7 7
#define TIMERS_TIMER_8 8

#define TIMERS_DIRECTION_UP 0
#define TIMERS_DIRECTION_DOWN 1

#define TIMERS_INTERRUPT_UPDATE 0
#define TIMERS_INTERRUPT_CAPTCOMP1 1
#define TIMERS_INTERRUPT_CAPTCOMP2 2
#define TIMERS_INTERRUPT_CAPTCOMP3 3
#define TIMERS_INTERRUPT_CAPTCOMP4 4


#endif /* INC_TIMERS_INTERFACE_H_ */
