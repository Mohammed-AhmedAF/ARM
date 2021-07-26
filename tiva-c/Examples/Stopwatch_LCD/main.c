#include "Macros.h"
#include "STD_TYPES.h"
#include "SysTick_interface.h"
#include "SYSCNTRL_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "LCD_interface.h"
#include "SCB_interface.h"
#include "TM4C123.h"                    // Device header
#include "APP_interface.h"




int main(void)
{
	/*Enabling clock for peripherals*/
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
	
	GPIO_vidUnlock(GPIO_PORTA);
	GPIO_vidCommit(GPIO_PORTA,GPIO_PIN4);
	GPIO_vidLock(GPIO_PORTA);
	
	GPIOConfig_t GPIOBtn0Config;
	GPIOBtn0Config.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	GPIOBtn0Config.u8DigEnable = GPIO_DEN_SET;
	GPIOBtn0Config.u8Direction = GPIO_INPUT;
	GPIOBtn0Config.u8Port = GPIO_PORTF;
	GPIOBtn0Config.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&GPIOBtn0Config);
	
	GPIOBtn0Config.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&GPIOBtn0Config);

	/*Button 2: PortA4*/
	GPIOConfig_t GPIOBtn2Config;
	GPIOBtn2Config.u8AlternateFunc = GPIO_ALTERFUNC_UNSET;
	GPIOBtn2Config.u8DigEnable = GPIO_DEN_SET;
	GPIOBtn2Config.u8Direction = GPIO_INPUT;
	GPIOBtn2Config.u8Port = GPIO_PORTA;
	GPIOBtn2Config.u8Pin = GPIO_PIN4;
	GPIO_vidConfigurePin(&GPIOBtn2Config);
	
	/*Button 2 external interrupt configuration*/
	ExtInterruptConfig_t ExtInterruptConfig2;
	ExtInterruptConfig2.ptrFunc = vidPauseCount;
	ExtInterruptConfig2.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	ExtInterruptConfig2.u8InterruptSense =  GPIO_SENSE_EDGE;
	ExtInterruptConfig2.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	ExtInterruptConfig2.u8PullResistance = GPIO_PUR_ENABLED;
	
	GPIO_vidConfigInterrupt(GPIO_PORTA,GPIO_PIN4,&ExtInterruptConfig2);

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
	NVIC_vidSetInterrupt(NVIC_GPIOA);
	NVIC_vidSetPriority(NVIC_GPIOA,1);
	NVIC_vidSetInterrupt(NVIC_GPIOF);

	/*Enabling global interrupt*/
	__enable_irq();
	
	
	while(1)
	{
		/*Going into deep sleep mode*/
		SCB_vidEnterSleepMode(SCB_SLEEPMODE_DEEP);
	}
	
}