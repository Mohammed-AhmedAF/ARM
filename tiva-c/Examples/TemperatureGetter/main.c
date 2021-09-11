#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "UART_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"

volatile u8Temperature;
u8 u8TemperatureArr[4];
u8 u8Index = 0;
void vidGetTemperaure(void);

void vidGetTemperature(void)
{
	u8Temperature = UART1_u8GetReceivedByte();
	u8TemperatureArr[u8Index] = u8Temperature;
	u8Index++;
	if (u8Index == 4)
	{	
		u8Index = 0;

		UART0_vidSendString("Temp: ");
		UART0_vidSendByte(u8TemperatureArr[0]);
		UART0_vidSendByte(u8TemperatureArr[1]);
		UART0_vidSendString(", Humidity: ");
		UART0_vidSendByte(u8TemperatureArr[2]);
		UART0_vidSendByte(u8TemperatureArr[3]);
		UART0_vidSendByte('\n');
		UART0_vidSendByte('\r');
	}

}

int main(void)
{
	/*Enabling running clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART1);
	
	/*Test LED pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	
	/*Configuring UART pins*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);
	
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN1,0x01);
	
	/*UART Configuration*/
	UARTConfig_t uart0Config;
	uart0Config.u16Integer = 104;
	uart0Config.u8Fraction = 11;
	uart0Config.u8FIFOEnabled = UART_FIFO_ENABLED;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV_16;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	UART0_vidInit(&uart0Config);
	
	UARTConfig_t uart1Config;
	uart1Config = uart0Config;
	uart1Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	uart1Config.ptrF = vidGetTemperature;
	UART1_vidInit(&uart1Config);
	
	/*NVIC configuation*/
	NVIC_vidSetInterrupt(NVIC_UART1);
	
	__enable_irq();
	
	while(1);
	

}