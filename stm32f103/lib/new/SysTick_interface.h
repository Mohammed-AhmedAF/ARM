#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

typedef struct
{
	u8 u8ClockSource;
	u8 u8InterruptReq;
	u32 u32ReloadValue;
	void (*ptrFun) (void);
	
}SysTickConfig_t;

void SysTick_vidSetCallBack(void (*ptrFunc) (void));
void SysTick_vidInit(SysTickConfig_t * sysTickConfig);
void SysTick_vidStart(void);

#define SYSTICK_CLOCK_EXTERNAL 0
#define SYSTICK_CLOCK_PROCESSOR 1

#define SYSTICK_INTERRUPT_DISABLED 0
#define SYSTICK_INTERRUPT_ENABLED 1


#endif
