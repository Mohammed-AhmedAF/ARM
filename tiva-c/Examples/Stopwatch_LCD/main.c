#include "Macros.h"
#include "STD_TYPES.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "NVIC_interface.h"
#include "LCD_interface.h"
#include "TM4C123.h"                    // Device header

void vidBlink(void);
void vidGreenLED(void);

u8* message = "Confirm missile \0";
u8* message2 = "launch authority.\0";
volatile u8 u8Count = 0;
volatile u16 u16Counter = 0;
volatile u8 u8Seconds = 0;
volatile u8 u8Minutes = 0;
volatile u8 u8Hours = 0;

void vidBlink(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);

	LCD_vidGoToXY(LCD_XPOS16,0);
	LCD_vidWriteNumber(u8Seconds);
	u8Seconds++;
		delay_micro(10);
	LCD_vidGoToXY(LCD_XPOS15,0);
	LCD_vidWriteCharacter(':');
	LCD_vidGoToXY(LCD_XPOS13,0);
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
	LCD_vidGoToXY(LCD_XPOS12,0);
	LCD_vidWriteCharacter(':');
	LCD_vidGoToXY(LCD_XPOS10,0);
	LCD_vidWriteNumber(u8Hours);


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

void vidProcessButtons(void)
{
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == 1)
	{
		vidGreenLED();
	}
	else if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN4) == 1)
		{
	vidClearScreen();
	}

}

int main(void)
{
	
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	
	LCD_vidInit();

	/*LED pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);

	/*GPIO pin configuration*/
	
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIOConfig_t GPIOBtn0Config;
	GPIOBtn0Config.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	GPIOBtn0Config.u8DigEnable = GPIO_DEN_SET;
	GPIOBtn0Config.u8Direction = GPIO_INPUT;
	GPIOBtn0Config.u8Port = GPIO_PORTF;
	GPIOBtn0Config.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&GPIOBtn0Config);
	
	GPIOBtn0Config.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&GPIOBtn0Config);

	/*External interrupt configuration*/
	ExtInterruptConfig_t ExtInterruptConfig0;
	ExtInterruptConfig0.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	ExtInterruptConfig0.u8InterruptSense = GPIO_SENSE_EDGE;
	ExtInterruptConfig0.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	ExtInterruptConfig0.u8PullResistance = GPIO_PUR_ENABLED;
	ExtInterruptConfig0.ptrFunc = vidProcessButtons;
	
	
	ExtInterruptConfig_t ExtInterruptConfig4;
	ExtInterruptConfig4.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	ExtInterruptConfig4.u8InterruptSense = GPIO_SENSE_EDGE;
	ExtInterruptConfig4.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	ExtInterruptConfig4.u8PullResistance = GPIO_PUR_ENABLED;
	ExtInterruptConfig4.ptrFunc =  vidProcessButtons;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&ExtInterruptConfig0);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&ExtInterruptConfig4);
	
	SysTickConfig_t SysTickConfig;
	SysTickConfig.u32ReloadValue = 16000000;
	SysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	SysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTickConfig.ptrFunc = vidBlink;
	
	SysTick_vidInitExtended(&SysTickConfig);
	SysTick_vidStart();

	/*PORTF Interrupt*/
	NVIC_vidSetInterrupt(30);

	__enable_irq();
	
	
	while(1)
	{
	
}
	
}