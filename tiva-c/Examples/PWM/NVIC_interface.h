#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H

/*Function declarations*/
void NVIC_vidSetInterrupt(u8 u8InterruptID);
void NVIC_vidClearInterrupt(u8 u8InterruptID);
void NVIC_vidSetPending(u8 u8InterruptID);
void NVIC_vidClearPending(u8 u8InterruptID);
void NVIC_vidSetPriority(u8 u8InterruptID, u8 u8InterruptPriority);

/*Interrupt IDs*/
#define NVIC_GPIOA 0
#define NVIC_GPIOB 1
#define NVIC_GPIOC 2
#define NVIC_GPIOD 3
#define NVIC_GPIOE 4
#define NVIC_UART0 5
#define NVIC_UART1 6
#define NVIC_TIMER0A 19
#define NVIC_TIMER0B 20
#define NVIC_PWM0_0 10
#define NVIC_PWM0_1 11
#define NVIC_PWM0_2 12

#endif