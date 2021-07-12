#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H

void NVIC_vidEnableInterrupt(u8 u8InterruptNumber);
void NVIC_vidDisableInterrupt(u8 ID);
void NVIC_vidSetPendingFlag(u8 ID);
void NVIC_vidClearPendingFlag(u8 ID);
u8 NVIC_u8GetActiveFlag(u8 u8ID);
void NVIC_vidSetPriority(u8 u8ID, u8 u8GroupPriority, u8 u8SubPriority, u32 u32Group);


#define GROUP3 0x05FA0300 // 4 bits for group (IPR) => group
#define GROUP4 0x05FA0400 // 3 bits for group and 1 bit for subpriority
#define GROUP5 0x05FA0500 // 2 bits for group and 2 bits for subpriority
#define GROUP6 0x05FA0600 // 1 bits for group and 3 bits for subpriority
#define GROUT7 0x05FA0700 // 0 group, 4 bits for subpriority

#define NVIC_EXTI0 6
#define NVIC_EXTI1 7
#define NVIC_EXTI2 8
#define NVIC_EXTI3 9
#define NVIC_EXTI4 10
#define NVIC_TIM2 28
#define NVIC_TIM3 29
#define NVIC_TIM4 30

#endif
