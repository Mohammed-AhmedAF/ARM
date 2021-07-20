#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "SYSCNTRL_interface.h"
#include "SysTick_interface.h"
#include "LCD_interface.h"
#include "TM4C123.h"                    // Device header
#include "UART_interface.h"
#include "APP_interface.h"


/*Stopwatch application: 
	* Count up/Count down
	* Utilizing external interrupt and UART

*/

int main(void)
{
	/*RCC configuration*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART1);


	/*UART0 pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x01);
	
	/*UART1 pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN0,0x01);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN1,0x01);
	
	/*UART1 configuration*/
	UARTConfig_t  UARTConfig1;
	UARTConfig1.u16Integer = 8;
	UARTConfig1.u8Fraction = 44;
	UARTConfig1.u8ClockSource = UART_CLOCKSOURCE_RC;
	UARTConfig1.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	UARTConfig1.u8RxTx = UART_RXTX_BOTH;
	UARTConfig1.u8WordLength = UART_WORDSIZE_8;
	UARTConfig1.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	UARTConfig1.ptrF = vidReceiveMessage_dev;
	UART1_vidInit(&UARTConfig1);
	
	/*UART0 configuration*/
	UARTConfig_t  UARTConfig0;
	UARTConfig0.u16Integer = 104;
	UARTConfig0.u8Fraction = 11;
	UARTConfig0.u8ClockSource = UART_CLOCKSOURCE_RC;
	UARTConfig0.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	UARTConfig0.u8RxTx = UART_RXTX_BOTH;
	UARTConfig0.u8WordLength = UART_WORDSIZE_8;
	UARTConfig0.u8InterruptEnabled = UART_INTERRUPT_DISABLED;
	UARTConfig0.ptrF = vidReceiveMessage_dev;
	UART0_vidInit(&UARTConfig0);
	
	/*LED configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);

	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*SysTick configuration*/
	SysTickConfig_t SysTickConfig;
	SysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	SysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	SysTickConfig.u32ReloadValue = 16000000;
	SysTickConfig.ptrFunc = vidBlink;
	SysTick_vidInitExtended(&SysTickConfig);
	SysTick_vidStart();
	
	/*Input pins configuration*/
	/*Button connected to F0 resets timer*/
	/*Button connected to F4 turns on count down timer*/
	GPIOConfig_t GPIOConfig;
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIOConfig.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	GPIOConfig.u8DigEnable = GPIO_DEN_SET;
	GPIOConfig.u8Direction = GPIO_INPUT;
	GPIOConfig.u8Port = GPIO_PORTF;
	GPIOConfig.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&GPIOConfig);
	
	GPIOConfig.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&GPIOConfig);

	ExtInterruptConfig_t ExtInterruptConfig;
	ExtInterruptConfig.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	ExtInterruptConfig.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	ExtInterruptConfig.u8InterruptSense = GPIO_SENSE_EDGE;
	ExtInterruptConfig.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&ExtInterruptConfig);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&ExtInterruptConfig);

	GPIO_vidPutISR(GPIO_PORTF,vidProcessButtons);
	
	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_UART0);
	NVIC_vidSetPriority(NVIC_UART0,3);
	NVIC_vidSetInterrupt(NVIC_UART1);
	NVIC_vidSetPriority(NVIC_UART0,2);
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	
	/*Enable global interrupt*/
	__enable_irq();

	while(1)
	{
	
	}
}