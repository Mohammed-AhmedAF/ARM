#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

void SysTick_vidInit(u8,u8);
void SysTick_vidSetValue(u32);
u32 SysTick_u32GetValue(void);


#define SYSTICK_SYSTEM_CLOCK 2
#define SYSTICK_INTERRUPT_ENABLED 1

#define SYSTEM_CLOCK 2
#define INTERRUPT_ENABLE 1
#endif
