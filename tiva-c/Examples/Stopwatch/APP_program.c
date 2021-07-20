#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "APP_interface.h"
#include "TM4C123.h"                    // Device header

volatile static u8 u8Command;
volatile static u8 u8Hours;
volatile static u8 u8Minutes;
volatile static u8 u8Seconds;
volatile static u8 u8CountDirection = APP_COUNT_UP;

void vidBlink(void)
{

	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	UART_vidSendNumber(UART0_vidSendByte,u8Hours);
	UART0_vidSendByte(':');
	UART_vidSendNumber(UART0_vidSendByte,u8Minutes);
	UART0_vidSendByte(':');
	UART_vidSendNumber(UART0_vidSendByte,u8Seconds);
	UART0_vidSendByte('\n');
	UART0_vidSendByte('\r');
	
	
	if (u8CountDirection == APP_COUNT_UP)
	{
	u8Seconds++;
	if (u8Seconds == 60)
	{
		u8Seconds = 0;
		u8Minutes++;
		if (u8Minutes == 60)
		{
			u8Minutes = 0;
			u8Hours++;
		}
	}
}
	else if (u8CountDirection == APP_COUNT_DOWN)
	{
		u8Seconds--;
		if (u8Seconds == 00)
		{
			if (u8Minutes == 0)
			{
						u8CountDirection = APP_COUNT_STOP;
			}
			else
			{
			u8Seconds = 59;
			u8Minutes--;
			}
		}
	}
}

void vidProcessCommand(void)
{
	u8Command = UART0_u8GetReceivedByte();
	if (u8Command == 'v')
	{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);

	}
	else if(u8Command == 'r')
	{
		vidResetStopWatch();
	}
	else if(u8Command == 'd')
	{
		vidCountDown();
	}
}

void vidResetStopWatch(void)
{
	u8Seconds = 0;
	u8Minutes = 0;
	u8Hours = 0;
	u8CountDirection = APP_COUNT_UP;
}

void vidCountDown(void)
{
	u8Hours = 0;
	u8Minutes = 2;
	u8Seconds = 59;
	u8CountDirection = APP_COUNT_DOWN;
}

void vidProcessButtons(void)
{
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		vidResetStopWatch();
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
	{
		vidCountDown();
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	}
}