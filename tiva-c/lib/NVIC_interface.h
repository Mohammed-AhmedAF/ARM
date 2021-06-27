#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H

/*Function declarations*/
void NVIC_vidSetInterrupt(u8 u8InterruptID);
void NVIC_vidClearInterrupt(u8 u8InterruptID);


/*Interrupt IDs*/
#define NVIC_GPIOA 0
#define NVIC_GPIOB 1
#define NVIC_GPIOC 2
#define NVIC_GPIOD 3
#define NVIC_GPIOE 4
#define NVIC_UART0 5
#define NVIC_UART1 6

#endif