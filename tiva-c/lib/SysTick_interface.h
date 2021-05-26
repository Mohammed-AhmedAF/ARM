#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

void SysTick_vidInit(u8,u8);
void SysTick_vidSetValue(u32);
u32 SysTick_u32GetCurrentValue(void);
void SysTick_vidStart(void);
void SysTick_vidStop(void);
void SysTick_vidToggle(void);
void SysTick_vidPutISR(void (*pf) (void));


#define SYSTICK_SYSTEM_CLOCK 2
#define SYSTICK_INTERRUPT_ENABLED 1
#define SYSTICK_NO_INTERRUPT 0


#define SYSTEM_CLOCK 2
#define INTERRUPT_ENABLE 1
#define ENABLE_SYSTICK 0
#endif
