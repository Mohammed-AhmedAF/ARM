#ifndef _SYSCNTRL_INTERFACE_H
#define _SYSCNTRL_INTERFACE_H

void SYSCNTRL_vidEnableGPIOClock(u8 u8PortNumber);
void SYSCNTRL_vidEnableUARTClock(u8 u8UARTChannel);
void SYSCNTRL_vidEnableTimerClock(u8 u8Timer);
void SYSCNTRL_vidEnableI2CClock(u8 u8I2CModule);
void SYSCNTRL_vidEnableTimerClock(u8 u8TimerID);
void SYSCNTRL_vidEnableWatchdog(u8 u8module);
void SYSCNTRL_vidUsePLL(void);
void SYSCNTRL_vidPLL80(void);

/*GPIO*/
#define SYSCNTRL_GPIO_PORTA 0
#define SYSCNTRL_GPIO_PORTB 1
#define SYSCNTRL_GPIO_PORTC 2
#define SYSCNTRL_GPIO_PORTD 3
#define SYSCNTRL_GPIO_PORTE 4
#define SYSCNTRL_GPIO_PORTF 5

/*I2C*/
#define SYSCNTRL_I2C_0 0
#define SYSCNTRL_I2C_1 1
#define SYSCNTRL_I2C_2 2
#define SYSCNTRL_I2C_3 3

/*UART*/
#define SYSCNTRL_UART0 0
#define SYSCNTRL_UART1 1

/*Watchdog*/
#define SYSCNTRL_WDT_0 0
#define SYSCNTRL_WDT_1 1

/*General purpos timers*/
#define SYSCNTRL_TIMER_0 0
#define SYSCNTRL_TIMER_1 1

#endif
