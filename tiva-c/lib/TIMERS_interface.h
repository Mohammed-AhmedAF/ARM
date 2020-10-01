#ifndef _TIMERS_INTERFACE_H
#define _TIMERS_INTERFACE_H


void TIMERS_vidSetup(void);
void TIMERS_vidStart(void);
void TIMERS_vidStartOneShoot(u8 times);
void TIMERS_vidStartPeriodic(u16 u16Value);
void TIMERS_vidPutFunction(void (*ptFun) (void));

#define ONESHOOT_MODE 0x1
#define PERIODIC_MODE 0x2
#define CAPTURE_MODE 0x3
#define TIMERS_TIMA_COUNT_UP (1U<<4)
#define TIMERA_ENABLE 0

#endif
