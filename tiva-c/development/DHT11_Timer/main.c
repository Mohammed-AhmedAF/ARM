#include "Macros.h"
#include "STD_TYPES.h"
#include "SysTick_interface.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMER0_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "DHT11_interface.h"
#include "APP_interface.h"

void uart0ReceiveHandler(void);
void vidBlink(void);

void uart0ReceiveHandler(void)
{
	if (UART0_u8GetReceivedByte() == 'i')
	{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
	}
}

void vidBlink(void)
{
	static u8 sysTickCount = 0;
	sysTickCount++;
	if (sysTickCount == 3)
	{
		APP_vidGetTemperature();
		sysTickCount = 0;
	}
}	

int main(void)
{
	/*Configuring running clock for used peripherals*/
  SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*UART pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_INPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	/*UART0 module configuration*/
	UARTConfig_t uart0Config;
	uart0Config.u8Module = UART_MODULE_0;
	uart0Config.u8StopBits = UART_STOPBITS_1;
	uart0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_RX;
	uart0Config.ptrFHandlerReceive = uart0ReceiveHandler;
	uart0Config.u8ParityEnable = UART_PARITY_DISABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	UART_vidInit(&uart0Config);
	
	/*On-board LED configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	
	//TIMER0_vidInit(0,1);
	NVIC_vidSetInterrupt(NVIC_UART0);
	NVIC_vidSetPriority(NVIC_UART0,4);
	APP_vidInit();

	SysTickConfig_t sysTickConfig;
	sysTickConfig.ptrFunc = vidBlink;
	sysTickConfig.u32ReloadValue = 16000000;
	sysTickConfig.u8ClockSource = SYSTICK_CLOCK_SYSTEM;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTick_vidInitExtended(&sysTickConfig);
  SysTick_vidStart();
	
	
	while(1)
	{


	}
}