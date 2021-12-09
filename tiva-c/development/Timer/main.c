#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

static volatile u8CountA = 0;
static volatile u8CountB = 0;

static void vidBlinkA(void); 

static void vidBlinkA(void)
{
	u8CountA++;
	if (u8CountA == 25)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		u8CountA = 0;
	}
	TIMERS_vidClearInterruptFlag(TIMERS_TIMER_0,TIMERS_INTERRUPT_BLOCKA_TIMEOUT);
}

int main(void)
{
/*Enabling clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);
	
	/*GPIO pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*Timer configuration*/
	TIMERConfig_t timer0AConfig;
	timer0AConfig.ptrFunc = vidBlinkA;
	timer0AConfig.u8TimerID = TIMERS_TIMER_0;
	timer0AConfig.u16ReloadValue = 60000;
	timer0AConfig.u8Config = TIMER_CONFIG_1632_16BIT;
	timer0AConfig.u8InterruptMask = TIMER_TIMERA_INTERRUPT_TIMEOUT;
	timer0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_PERIODIC;
	timer0AConfig.u8TimerACountDir = TIMERS_COUNTDIR_UP;
	TIMERS_vidInit(&timer0AConfig);
	
	
	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_TIMER0A);
	
	/*Enable global interrupt*/
	__enable_irq();

	
	while(1);
}