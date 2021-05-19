#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSCNTRL_interface.h"
#include "TM4C123.h"                    // Device header




void vidDelayMS(u16);

#define GPIOA_AFSEL * ((u32*) 0x40004420)
#define GPIOA_PCTL * ((u32*) 0x4000452C)
#define GPIOA_AMSEL * ((u32*) 0x40004528)

int main(void)
{
	u8 u8Command;
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
	
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*UART*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	
	/*Blue LED*/
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);
	/*Green LED*/
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);

	
	UART_vidInit();

	
	GPIOA_AFSEL |= 0x03;
	/*Disabling angalog function*/
	GPIOA_AMSEL = 0;
	GPIOA_PCTL |= 0x11;
	vidDelayMS(100);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_HIGH);
	UART_vidSendString("Hello");
	NVIC->IP[5] = 3 << 5; /* set interrupt priority to 3 */
NVIC->ISER[0] |= 0x00000020; /* enable IRQ5 for UART0 */
	while(1)
	{
			u8Command = UART_u8ReceiveByte();
			if (u8Command == 'g')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
				UART_vidSendString("Green LED on\n\r\0");
			}
			else if(u8Command == 'b')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_HIGH);
				UART_vidSendString("Blue LED on\n\r\0");
			}
			else if(u8Command == 'p')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);
				UART_vidSendString("Blue LED off\n\r\0");
			}
			else if (u8Command== 'h')
			{
				GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
				UART_vidSendString("Green LED off!\n\r\0");
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
