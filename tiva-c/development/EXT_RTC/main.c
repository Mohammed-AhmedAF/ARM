#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "NVIC_interface.h"
#include "TIMER0_interface.h"
#include "I2C_interface.h"
#include "APP_interface.h"
#include "LCD_interface.h"
#include "MAX7219_interface.h"

void vidBlink(void);

void vidBlink(void)
{
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == STD_HIGH)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_GREEN);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
		}
	else
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	}
}

int main(void)
{
	/*Enabling clock for used peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidChangeSysClock(SYSCNTRL_SYSCLOCK_16MHZ);
	APP_UART0_vidInit();
	APP_I2C_Periph_vidInit(I2C_MODULE_1);

	APP_SYSTICK_vidInitialize();
	
	/*LED GPIO configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_GREEN,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_GREEN,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_RED,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_RED,GPIO_OUTPUT);

	/*Button GPIO configuration*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTF);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_SWITCH2,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_SWITCH2,GPIO_INPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_SWITCH1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_SWITCH1,GPIO_INPUT);
	
	/*External interrupt configuration*/
	ExtInterruptConfig_t extInterruptConf;
	extInterruptConf.ptrFunc = vidBlink;
	extInterruptConf.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	extInterruptConf.u8InterruptSense = GPIO_SENSE_EDGE;
	extInterruptConf.u8InterruptEvent = GPIO_EVENT_FE;
	extInterruptConf.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&extInterruptConf);
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&extInterruptConf);
	
	/*NVIC external interrupt configuration*/
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetPriority(NVIC_GPIOF,2);
	NVIC_vidSetInterrupt(NVIC_I2C1);

	/*Enable maskable interrupts*/
	__enable_irq();


	while(1)
	{
	
	}
}