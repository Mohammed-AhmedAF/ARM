#include "TM4C123.h"                    // Device header
#include "Macros.h"
#include "STD_TYPES.h"
#include "SysTick_interface.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"


void getCountForOneSec(void);


volatile u16Count = 0;

/*Example of Edge Event Counter*/

int main(void)
{
	/*Enabling running clock for timer 0*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	/*GPIO Pin configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN6);	
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN6,0x7);
	GPIO_vidSetPinValue(GPIO_PORTB,GPIO_PIN6,STD_LOW);
	
	/*Blinking LED GPIO configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_LED_BLUE,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_LED_BLUE,GPIO_DEN_SET);
	
	
	/*Timer configuration*/
	vidInitEdgeCount();
	
	/*Configure systick*/
	SysTickConfig_t sysTickConfig;
	sysTickConfig.u32ReloadValue = 16000000;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	sysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	sysTickConfig.ptrFunc = getCountForOneSec;
	
	SysTick_vidInitExtended(&sysTickConfig);
	SysTick_vidStart();
	
	__enable_irq();
	while(1);
}


void getCountForOneSec(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_BLUE);
	u16Count = TIMER0_u16GetCount();
	
	/*Reinitiate timer*/
	CLEAR_BIT(TIMER0->CTL,0);
	TIMER0->TAR = 0;
	TIMER0->TAV = 0;
	vidInitEdgeCount();
	
}

