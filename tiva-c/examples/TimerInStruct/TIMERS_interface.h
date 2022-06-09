#ifndef _TIMERS_INTERFACE_H
#define _TIMERS_INTERFACE_H

typedef struct 
{
	u16 u16ReloadValue;
	u8 u8Config;
	u8 u8TimerAMode;
	u8 u8TimerACaptMode;
	u8 u8TimerACountDir;
	u8 u8TimerAEventMode;
	u8 u8InterruptMask;
	void (*ptrFunc) (void);
} TIMERConfig_t;




/*Function declarations*/
void TIMERS_vidSetup(void);
void TIMERS_vidStart(void);
void TIMERS_vidStartOneShoot(u8 times);
void TIMERS_vidStartPeriodic(u16 u16Value);
void TIMERS_vidInit(TIMERConfig_t * TIMERConfig);
void TIMERS_vidPutFunction(void (*ptFun) (void));
void TIMER0A_vidConfigInputCapt(TIMERConfig_t * TIMERConfig);
u32 TIMER0A_u32MeasureTimerPeriod(void);


#define ONESHOOT_MODE 0x1
#define PERIODIC_MODE 0x2
#define CAPTURE_MODE 0x3
#define TIMERS_TIMA_COUNT_UP (1U<<4)
#define TIMERA_ENABLE 0

/*GPTM mode*/
#define TIMER_CONFIG_1632_32BIT 1
#define TIMER_CONGIG_3264_64BIT 2
#define TIMER_CONFIG_1632_32BIT_RTC 3
#define TIMER_CONFIG_1632_16BIT 4
#define TIMER_CONFIG_3264_32BIT 5

/*Interrupt mask*/
#define TIMER_TIMERA_INTERRUPT_TIMEOUT 1
#define TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH 2
#define TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT 3


/*TIMERnA Mode*/
#define TIMER_TIMERA_MODE_ONESHOOT 1
#define TIMER_TIMERA_MODE_PERIODIC 2
#define TIMER_TIMERA_MODE_CAPTURE 3

/*TIMERnA Capture mode*/
#define TIMER_TIMERA_CAPTMODE_EDGECOUNT 1
#define TIMER_TIMERA_CAPTMODE_EDGETIMER 2

/*TIMERnA Count direction*/
#define TIMER_TIMERA_COUNTDIR_DOWN 1
#define TIMER_TIMERA_COUNTDIR_UP 2

/*TIMERnA Event mode*/
#define TIMER_TIMERA_EVENTMODE_POSITIVE 1
#define TIMER_TIMERA_EVENTMODE_NEGATIVE 2
#define TIMER_TIMERA_EVENTMODE_BOTHEDGES 3


#endif
