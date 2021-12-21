#ifndef _TIMERS_INTERFACE_H
#define _TIMERS_INTERFACE_H

typedef struct 
{
	u32 u32MatchValue;
	u16 u16ReloadValue;
	u16 u16PrescalerValue;
	u8 u8TimerID;
	u8 u8TimerBlock;
	u8 u8Config;
	u8 u8PWM;
	u8 u8PWMInverted;
	u8 u8TimerMode;
	u8 u8TimerCaptMode;
	u8 u8TimerCountDir;
	u8 u8TimerEventMode;
	u8 u8InterruptMask;
	u8 u8InterruptID;
	void (*ptrFunc) (void);
} TIMERConfig_t;




/*Function declarations*/
void TIMERS_vidSetup(void);
void TIMERS_vidStart(void);
void TIMERS_vidStartOneShoot(u8 times);
void TIMERS_vidStartPeriodic(u16 u16Value);
void TIMERS_vidInit(TIMERConfig_t * TIMERConfig);
void TIMER0B_vidInit(TIMERConfig_t * TIMERConfig);
void TIMERS_vidPutFunction(u8 u8Timer,void (*ptFun) (void));
void TIMER0A_vidConfigInputCapt(TIMERConfig_t * TIMERConfig);
u32 TIMER0A_u32MeasureTimerPeriod(void);
void TIMER0_vidDisable(u8 u8Timer0Sub);
void TIMER0_vidStart(void);

/*Version 2 function*/
void TIMERS_vidEnableTimer(u8 u8TimerID, u8 u8TimerBlock);
void TIMERS_vidDisableTimer(u8 u8TimerID, u8 u8TimerBlock);
void TIMERS_vidSelectTimerConfig(u8 u8TimerID, u8 u8TimerConfig);
void TIMERS_vidSelectCountDirectionA(u8 u8TimerID, u8 u8CountDir);
void TIMERS_vidSelectCountDirectionB(u8 u8TimerID, u8 u8CountDir);
void TIMERS_vidSelectModeA(u8 u8Timer, u8 u8Mode);
void TIMERS_vidSelectModeB(u8 u8Timer, u8 u8Mode);
void TIMERS_vidEnableInterruptA(u8 u8Timer, u8 u8Interrupt);
void TIMERS_vidEnableInterruptB(u8 u8Timer, u8 u8Interrupt);
void TIMERS_vidSelectCaptModeA(u8 u8Timer, u8 u8CaptMode);
void TIMERS_vidSelectEventModeA(u8 u8Timer, u8 u8EventMode);
void TIMERS_vidClearInterruptFlag(u8 u8Timer, u8 u8InterruptFlag);
void TIMERS_vidSetLoadValueA(u8 u8Timer, u32 u32LoadValue);
void TIMERS_vidSetLoadValueB(u8 u8Timer, u32 u32LoadValue);
void TIMERS_vidSetPrescalerValueA(u8 u8Timer, u16 u16PrescalerValue);
void TIMERS_vidSetPrescalerValueB(u8 u8Timer, u16 u16PrescalerValue);
void TIMERS_vidSetMatchValueA(u8 u8TimerID, u32 u32MatchValue);
void TIMERS_vidSetMatchValueB(u8 u8TimerID,u32 u32MatchValue);
void TIMERS_vidConfigPWMA(u8 u8TimerID, u8 u8PWM);
void TIMERS_vidConfigPWMB(u8 u8TimerID, u8 u8PWM);
void TIMERS_vidInvertPWMA(u8 u8TimerID, u8 u8PWMInvert);
void TIMERS_vidInvertPWMB(u8 u8TimerID, u8 u8PWMInvert);
u8 TIMERS_u8GetInterruptID(u8 u8TimerID, u8 u8TimerBlock);


/*TIMER IDs*/
#define TIMERS_TIMER_0 0
#define TIMERS_TIMER_1 1
#define TIMERS_TIMER_2 2
#define TIMERS_TIMER_3 3
#define TIMERS_TIMER_4 4
#define TIMERS_TIMER_5 5

/*Block IDs*/
#define TIMERS_BLOCK_A 0
#define TIMERS_BLOCK_B 1

/*Count directions*/
#define TIMERS_COUNTDIR_DOWN 0
#define TIMERS_COUNTDIR_UP 1


#define TIMERS_TIMER0A 1
#define TIMERS_TIMER0B 2
#define TIMERS_TIMER1A 3
#define TIMERS_TIMER1B 4
#define TIMERS_TIMER2A 5
#define TIMERS_TIMER2B 6
#define TIMERS_TIMER3A 7
#define TIMERS_TIMER3B 8
#define TIMERS_TIMER4A 9
#define TIMERS_TIMER4B 10
#define TIMERS_TIMER5A 11
#define TIMERS_TIMER5B 12

/*Timer modes*/
#define ONESHOOT_MODE 0x1
#define PERIODIC_MODE 0x2
#define CAPTURE_MODE 0x3
#define TIMERS_TIMA_COUNT_UP (1U<<4)
#define TIMERA_ENABLE 0

/*GPTM configuration*/
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

/*Interrupt mask*/
#define TIMER_TIMERB_INTERRUPT_TIMEOUT 1
#define TIMER_TIMERB_INTERRUPT_CAPTUREMODE_MATCH 2
#define TIMER_TIMERB_INTERRUPT_CAPTUREMODE_EVENT 3

/*TIMERnB Mode*/
#define TIMER_TIMERB_MODE_ONESHOOT 1
#define TIMER_TIMERB_MODE_PERIODIC 2
#define TIMER_TIMERB_MODE_CAPTURE 3

/*TIMERnB Capture mode*/
#define TIMER_TIMERB_CAPTMODE_EDGECOUNT 1
#define TIMER_TIMERB_CAPTMODE_EDGETIMER 2

/*TIMERnB Count direction*/
#define TIMER_TIMERB_COUNTDIR_DOWN 1
#define TIMER_TIMERB_COUNTDIR_UP 2

/*TIMERnB Event mode*/
#define TIMER_TIMERB_EVENTMODE_POSITIVE 1
#define TIMER_TIMERB_EVENTMODE_NEGATIVE 2
#define TIMER_TIMERB_EVENTMODE_BOTHEDGES 3

#define TIMERS_INTERRUPT_BLOCKA_TIMEOUT 0
#define TIMERS_INTERRUPT_BLOCKA_CAPTMODE 1

#define TIMERS_INTERRUPT_BLOCKB_TIMEOUT 0
#define TIMERS_INTERRUPT_BLOCKB_CAPTMODE 1

#define TIMERS_PWM_DISABELD 0
#define TIMERS_PWM_ENABLED 1

#define TIMERS_PWM_NOTINVERTED 0
#define TIMERS_PWM_INVERTED 1

/*General macro definitions*/

#define TIMERS_INTERRUPT_TIMEOUT 1
#define TIMERS_INTERRUPT_CAPTUREMODE_MATCH 2
#define TIMERS_INTERRUPT_CAPTUREMODE_EVENT 3

#define TIMERS_MODE_ONESHOOT 1
#define TIMERS_MODE_PERIODIC 2
#define TIMERS_MODE_CAPTURE 3

#define TIMERS_CONFIG_1632_32BIT 1
#define TIMERS_CONGIG_3264_64BIT 2
#define TIMERS_CONFIG_1632_32BIT_RTC 3
#define TIMERS_CONFIG_1632_16BIT 4
#define TIMERS_CONFIG_3264_32BIT 5
#endif
