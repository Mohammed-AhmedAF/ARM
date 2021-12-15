/***************************************************************************/
/* Author : Mohammed Ahmed                                                 */
/* Version: V01                                                            */
/* Date: 16 April 2021                                                     */
/***************************************************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H

#define RCC_AHB 0
#define RCC_APB1 1
#define RCC_APB2 2

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
void RCC_vidResetPeripheral(u8 u8Bus, u8 u8PeripheralID);

/*RCC_APB2ENR bits macros*/
#define RCC_GPIO_PORTA 2
#define RCC_GPIO_PORTB 3
#define RCC_GPIO_PORTC 4
#define RCC_ADC_1 9
#define RCC_ADC_2 10
#define RCC_TIM_1 11
#define RCC_SPI_1 12
#define RCC_UART_1 14

/*RCC_APB1ENR*/
#define RCC_TIMERS_2 0
#define RCC_TIMERS_3 1
#define RCC_TIMERS_4 4
#define RCC_TIMERS_5 5
#define RCC_TIMERS_6 6
#define RCC_TIMERS_7 7
#define RCC_SPI_2 14
#define RCC_SPI_3 15
#define RCC_UART_2 17
#define RCC_UART_3 18
#define RCC_UART_4 19
#define RCC_UART_5 20
#define RCC_I2C_1 21
#define RCC_I2C_2 22
#define RCC_DAC 29

#endif