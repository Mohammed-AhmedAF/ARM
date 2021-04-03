#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSCNTRL_interface.h"
#include "TM4C123GH6PM.h"


void vidDelayMS(u16);
void vidDoOnUART(void);



#define GPIOA_AFSEL * ((u32*) 0x40004420)
#define GPIOA_PCTL * ((u32*) 0x4000452C)

int main(void)
{
	u8 u8Command;
	UARTConfig_t uartConfig;
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*LED pins configuration*/
	/*LED 1*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);
	/*LED 2*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
	
	/*LED 3*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN1,STD_LOW);
	
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	/*UART configuration*/
	uartConfig.u8Integer = 104;
	uartConfig.u8Fraction = 11;
	uartConfig.u8WordLength = UART_CLOCKSOURCE_RC;
	uartConfig.u8WordLength = UART_WORDSIZE_8;
		
	GPIOA_AFSEL |= 0x03;
	GPIOA_PCTL |= 0x11;
	
	
	UART_vidInit(&uartConfig);


	/*Interrupt*/
	UART_vidPutISRFunction(vidDoOnUART);
	
	NVIC->IP[5] = 3 << 5;
	NVIC->ISER[0] |= 0x00000020;
	__enable_irq();
	
	UART_vidSendString("a: Blue\r\n");
	UART_vidSendString("b: Green\r\n");
	UART_vidSendString("c: Red\r\n");

	while(1)
	{
			
	}
}

void vidDelayMS(u16 u16Milli)
{
	u16 u16MilliIterator;
	u16 u16Count;
	for (u16MilliIterator = 0; u16MilliIterator < u16Milli; u16MilliIterator++)
	{
		for (u16Count = 0; u16Count < 3180; u16Count++) {
		
		}
	}
}

void vidDoOnUART(void)
{
					u8 u8Val = UART_u8GetReceivedByte();
					if (u8Val == 'a') {
						GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
						UART_vidSendString("a\r\n");
					}
					else if (u8Val == 'b')
					{
						GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
						UART_vidSendString("b\r\n");
					}
					else if (u8Val == 'c')
					{
						GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
						UART_vidSendString("c\r\n");
					}
				


}