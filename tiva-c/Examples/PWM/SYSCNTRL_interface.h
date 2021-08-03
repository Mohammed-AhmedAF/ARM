#ifndef _SYSCNTRL_INTERFACE_H
#define _SYSCNTRL_INTERFACE_H

void SYSCNTRL_vidEnableGPIOClock(u8 u8PortNumber);
void SYSCNTRL_vidEnableUARTClock(u8 u8UARTChannel);
void SYSCNTRL_vidEnableTimerClock(u8 u8Timer);
void SYSCNTRL_vidEnableI2CClock(u8 u8I2CModule);
void SYSCNTRL_vidEnableADCClock(u8 u8ADCPeriph);
void SYSCNTRL_vidSelectGPIOBus(u8 u8GPIOPort,u8 u8Bus);
void SYSCNTRL_vidEnablePWMClock(u8 uModule);
void SYSCNTRL_vidConfigPWMDiv(u8 u8DivisorEnabled, u8 u8Divisor);

	
#define SYSCNTRL_GPIO_PORTA 0
#define SYSCNTRL_GPIO_PORTB 1
#define SYSCNTRL_GPIO_PORTC 2
#define SYSCNTRL_GPIO_PORTD 3
#define SYSCNTRL_GPIO_PORTE 4
#define SYSCNTRL_GPIO_PORTF 5

#define SYSCNTRL_I2C_0 0
#define SYSCNTRL_I2C_1 1
#define SYSCNTRL_I2C_2 2
#define SYSCNTRL_I2C_3 3

#define SYSCNTRL_UART0 0
#define SYSCNTRL_UART1 1
#define SYSCNTRL_UART2 2


#define SYSCNTRL_TIMER_0 0
#define SYSCNTRL_TIMER_1 1

#define SYSCNTRL_ADC_0 0
#define SYSCNTRL_ADC_1 1

#define SYSCNTRL_BUS_AHB 1
#define SYSCNTRL_BUS_APB 2

#define SYSCNTRL_PWM_0 1
#define SYSCNTRL_PWM_1 2
#define SYSCNTRL_PWM_DIV_DISABLED 0
#define SYSCNTRL_PWM_DIV_ENABLED 1

#define SYSCNTRL_PWM_DIV_2 0
#define SYSCNTRL_PWM_DIV_4 1
#define SYSCNTRL_PWM_DIV_8 2
#define SYSCNTRL_PWM_DIV_16 3
#define SYSCNTRL_PWM_DIV_32 4
#define SYSCNTRL_PWM_DIV_64 5

#endif
