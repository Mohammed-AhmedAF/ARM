#include "STD_TYPES.h"
#include "Macros.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "TIMER0_interface.h"
#include "UART_interface.h"
#include "ROTENC_interface.h"

int main(void)
{
	/*Enabling running clock for peripherals*/
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	
	/*LED GPIO Configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	/*UART GPIO configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);

	/*UART0 peripheral configuration*/
	UARTConfig_t strctUART0Config;
	strctUART0Config.u8Module = UART_MODULE_0;
	strctUART0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	strctUART0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	strctUART0Config.u8Loopback = UART_LOOPBACK_DISABLED;
	strctUART0Config.u8WordLength = UART_WORDSIZE_8;
	strctUART0Config.u8RxTx = UART_RXTX_BOTH;
	strctUART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV8;
	strctUART0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	strctUART0Config.u8ParityEnable = UART_PARITY_DISABLED;
	strctUART0Config.u8StopBits = UART_STOPBITS_1;
	strctUART0Config.u16Integer = 208;
	strctUART0Config.u8Fraction = 21;
	UART0_vidInit(&strctUART0Config);
	
	ROTENCConfig_t strctROTENCConfig;
	strctROTENCConfig.u8ClockPort = GPIO_PORTA;
	strctROTENCConfig.u8ClockPin = GPIO_PIN5;
	strctROTENCConfig.u8DataPort = GPIO_PORTA;
	strctROTENCConfig.u8DataPin = GPIO_PIN6;
	
	ROTENC_vidInit(&strctROTENCConfig);
	
	ROTENCRead_t strctROTENCRead;
	
	while(1)
	{
		strctROTENCRead = ROTENC_strctGetReading(&strctROTENCConfig);
		
	}

}

