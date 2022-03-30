#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSCNTRL_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "TIMER0_interface.h"

void vidReceiveCommand(void);
void vidOnSysTick(void);

volatile u8 u8SysTickFlag = 1;
void vidReceiveCommand(void)
{
	static u8 u8Command;
	u8Command = UART0_u8GetReceivedByte();
	if (u8Command == 'a')
	{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);	
	TIMER0_vidDelayMicro(10000);
	}
	else
	{
			GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);

	}
}

void vidOnSysTick(void)
{
	
	u8SysTickFlag = 0;
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);

}

int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	
	/*GPIO LED pin configuation*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	
	/*UART pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);
	
	/*UART Configuration*/
	UARTConfig_t uart0Config;
	uart0Config.ptrF = vidReceiveCommand;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV_16;
	
	UART0_vidInit(&uart0Config);
	
	/*NVIC configuation*/
	NVIC_vidSetInterrupt(NVIC_UART0);
	NVIC_vidSetPriority(NVIC_UART0,0);
	
	/*SysTick configuration*/
	SysTickConfig_t sysTickConfig;
	sysTickConfig.ptrFunc = vidOnSysTick;
	sysTickConfig.u32ReloadValue = 16000000;
	sysTickConfig.u8ClockSource = SYSTICK_CLOCK_SYSTEM;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTick_vidInitExtended(&sysTickConfig);
	SysTick_vidStart();
	
	/*Timer initialization*/
	NVIC_vidSetPriority(NVIC_TIMER0A,0);
	TIMER0_vidInit(31,0);
	while(1)
	{
		
	}
}