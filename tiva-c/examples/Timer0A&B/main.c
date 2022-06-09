#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

static volatile u8CountA = 0;
static volatile u8CountB = 0;

static void vidBlinkA(void); 
static void vidBlinkB(void);

static void vidBlinkA(void)
{
	u8CountA++;
	if (u8CountA == 250)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		u8CountA = 0;
	}
}

static void vidBlinkB(void)
{
	u8CountB++;
	if (u8CountB == 76)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		u8CountB = 0;
	}
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
	timer0AConfig.u16ReloadValue = 60000;
	timer0AConfig.u8Config = TIMER_CONFIG_1632_16BIT;
	timer0AConfig.u8InterruptMask = TIMER_TIMERA_INTERRUPT_TIMEOUT;
	timer0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_PERIODIC;
	timer0AConfig.u8TimerACountDir = TIMER_TIMERA_COUNTDIR_DOWN;
	TIMERS_vidInit(&timer0AConfig);
	
	TIMERConfig_t timer0BConfig;
	timer0BConfig.ptrFunc = vidBlinkB;
	timer0BConfig.u16ReloadValue = 10000;
	timer0BConfig.u8Config = TIMER_CONFIG_1632_16BIT;
	timer0BConfig.u8InterruptMask = TIMER_TIMERB_INTERRUPT_TIMEOUT;
	timer0BConfig.u8TimerAMode = TIMER_TIMERB_MODE_PERIODIC;
	timer0BConfig.u8TimerACountDir = TIMER_TIMERB_COUNTDIR_DOWN;
	TIMER0B_vidInit(&timer0BConfig);
	
	
	NVIC_vidSetInterrupt(NVIC_TIMER0A);
	NVIC_vidSetInterrupt(NVIC_TIMER0B);
	
	/*Enable global interrupt*/
	__enable_irq();
	
	while(1);
}