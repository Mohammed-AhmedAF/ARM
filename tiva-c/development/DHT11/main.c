#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMER0_interface.h"
#include "DHT11_interface.h"
#include "LCD_interface.h"
#include "UART_interface.h"
#include "APP_interface.h"
#include "NVIC_interface.h"

void vidBlink(void);
void vidBlink(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
}



int main(void)
{
	/*Enable clock for used peripherals*/
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*Timer used for DHT11*/
	TIMER0_vidInit(31,0);
	
	/*GPIO pin configuration of UART pins*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	/*GPIO pin configuation of LED pins*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);

	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	
	/*UART configuation*/
	UARTConfig_t uart0Config;
	uart0Config.u16Integer = 8;
	uart0Config.u8Fraction = 44;
	uart0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV_16;
	uart0Config.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	uart0Config.u8RxTx = UART_RXTX_BOTH;
	uart0Config.u8WordLength = UART_WORDSIZE_8;
	uart0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	UART0_vidInit(&uart0Config);
	
	/*SysTick configuation*/
	SysTickConfig_t sysConfig;
	sysConfig.ptrFunc = vidBlink;
	sysConfig.u32ReloadValue = 16000000;
	sysConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	sysConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTick_vidInitExtended(&sysConfig);
	SysTick_vidStart();
	DHT11_vidInit();
	
	NVIC_vidSetInterrupt(NVIC_UART0);
	while(1)
	{
		APP_vidGetTemperature();
		TIMER0_vidDelayMicro(350000);
	}
	
}