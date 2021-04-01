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
	
	/*Green LED*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
	
	/*Blue LED*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*UART pins*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	/*UART configuration*/
	uartConfig.u8Integer = 104;
	uartConfig.u8Fraction = 11;
	uartConfig.u8WordLength = UART_CLOCKSOURCE_RC;
	uartConfig.u8WordLength = UART_WORDSIZE_8;
	
	UART_vidInit(&uartConfig);

	
	GPIOA_AFSEL |= 0x03;
	GPIOA_PCTL |= 0x11;
	//vidDelayMS(100);

	/*Interrupt*/
	UART_vidPutISRFunction(vidDoOnUART);
	
	NVIC->IP[5] = 3 << 5;
	NVIC->ISER[0] |= 0x00000020;
	__enable_irq();
	
	UART_vidSendString("k,b,p,h");

	while(1)
	{
			u8Command = UART_u8ReceiveByte();
			if (u8Command == 'k')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
				UART_vidSendString((u8*)"Green LED on\n\r\0");
			}
			if (u8Command == 'b')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_HIGH);
				UART_vidSendString((u8*)"Blue LED on\n\r\0");
			}
			if (u8Command == 'p')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);
				UART_vidSendString((u8*)"Blue LED off\n\r\0");
			}
			if (u8Command== 'h')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
				UART_vidSendString((u8*)"Green LED off!\n\r\0");
			}
		
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
					GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
					UART_vidSendString((u8*)"Gekk!\n\r\0");


}
