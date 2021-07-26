#include "STD_TYPES.h"
#include "Macros.h"
#include "SYSTICK_interface.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"
#include "APP_interface.h"

u8* message = "Confirm missile \0";
u8* message2 = "launch authority.\0";
static volatile u8 u8Count = 0;
static volatile u16 u16Counter = 0;
static volatile u8 u8Seconds = 0;
static volatile u8 u8Minutes = 0;
static volatile u8 u8Hours = 0;


void vidBlink(void)
{
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);

	LCD_vidGoToXY(LCD_XPOS13,0);
	LCD_vidWriteNumber(u8Seconds);
	u8Seconds++;
	delay_micro(10);
	LCD_vidGoToXY(LCD_XPOS12,0);
	LCD_vidWriteCharacter(':');
	LCD_vidGoToXY(LCD_XPOS10,0);
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
	LCD_vidWriteNumber(u8Minutes);
	LCD_vidGoToXY(LCD_XPOS9,0);
	LCD_vidWriteCharacter(':');
	LCD_vidGoToXY(LCD_XPOS7,0);
	LCD_vidWriteNumber(u8Hours);

	/**/
	LCD_vidGoToXY(LCD_XPOS7,3);


}

void vidGreenLED(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidGoToXY(LCD_XPOS0,u8Count);
	LCD_vidWriteString(message);
	u8Count++;
	if (u8Count == 4)
	{
		u8Count = 0;
	}
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);

}
void vidClearScreen(void)
{

	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	u8Seconds = 0;
	u8Minutes = 0;
	u8Hours = 0;
	u8Count = 0;

}

void vidPauseCount(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	SysTick_vidToggle();
	GPIO_vidClearInterrupt(GPIO_PORTA,GPIO_PIN4);
}


void vidProcessButtons(void)
{
	/*Checking the MIS register*/
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		vidGreenLED();
	}
	/*Checking the MIS register*/
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
		{
	vidClearScreen();
	}

}