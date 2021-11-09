#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

/*Configuration structu*/
typedef struct
{
	u8 u8ClockSource;
	u8 u8Interrupt;
	u32 u32ReloadValue;
	void (*ptrFunc) (void);
} SysTickConfig_t;

/*Function declaration*/
void SysTick_vidInit(u8 u8ClockSource,u8 u8InterruptEnabled);
void SysTick_vidInitExtended(SysTickConfig_t * SysTickConfig);
void SysTick_vidSetValue(u32);
u32 SysTick_u32GetCurrentValue(void);
void SysTick_vidStart(void);
void SysTick_vidStop(void);
void SysTick_vidToggle(void);
void SysTick_vidPutISR(void (*pf) (void));
void SysTick_vidSetBusyWait(u32 u32Ticks);
void _vidCheckForBusyWait(void);


#define SYSTICK_SYSTEM_CLOCK 2
#define SYSTICK_INTERRUPT_ENABLED 1
#define SYSTICK_INTERRUPT_DISABLED 0
#define SYSTICK_NO_INTERRUPT 0

/*Bit defintions*/
#define SYSTEM_CLOCK 2
#define INTERRUPT_ENABLE 1
#define ENABLE_SYSTICK 0
#define COUNTFLAG 16


#endif
