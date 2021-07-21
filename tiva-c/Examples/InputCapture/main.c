#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "TM4C123.h"                    // Device header
#include "TIMERS_interface.h"
#include "SERVICES_interface.h"
#include <stdio.h>

static u32 u32TimePeriod;
static float fFrequency;
static float timer_period_ms;
static char mesg[27];

void Delay(unsigned long counter);
static u8 i = 0;
static u8 u8EndFlag = 0;

int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidSelectGPIOBus(SYSCNTRL_GPIO_PORTA,SYSCNTRL_BUS_AHP);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	/*UART0 pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);

	/*UART0 configuration*/
	UARTConfig_t UARTConfig0;
	UARTConfig0.u16Integer = 104;
	UARTConfig0.u8Fraction = 11;
	UARTConfig0.u8FIFOEnabled = UART_FIFO_ENABLED;
	UARTConfig0.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	UARTConfig0.u8RxTx = UART_RXTX_BOTH;
	UARTConfig0.u8WordLength = UART_WORDSIZE_8;
	UART0_vidInit(&UARTConfig0);

	/*Input capture pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTB,GPIO_PIN6,GPIO_INPUT);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN6);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN6,0x07);
	
	/*Timer configuration*/
	TIMERConfig_t TIMER0AConfig;
	TIMER0AConfig.u8Config = TIMER_CONFIG_3264_32BIT;
	TIMER0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_CAPTURE;
	TIMER0AConfig.u8TimerACaptMode = TIMER_TIMERA_CAPTMODE_EDGETIMER;
	TIMER0AConfig.u8TimerAEventMode = TIMER_TIMERA_EVENTMODE_POSITIVE;
	TIMER0A_vidConfigInputCapt(&TIMER0AConfig);

	while(1)
	{
		if (u8EndFlag == 0)
		{
		for (i = 0; i < 4; i++)
		{
		u32TimePeriod = TIMER0A_u32MeasureTimerPeriod();
		timer_period_ms = (u32TimePeriod*62.5)/1000000;
		fFrequency = 1000/timer_period_ms;
		sprintf(mesg, "\r\nFrequency = %f Hz", fFrequency);
		UART0_vidSendString(mesg);
		SERVICES_vidDelay(1000);
			if (i == 3)
			{
				u8EndFlag = 1;
			}
		}
	}
	}
}
