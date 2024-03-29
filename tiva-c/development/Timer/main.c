#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

static volatile u8 u8CountA = 0;

static void vidBlink(void); 

static void vidBlink(void)
{
	u8CountA++;
	if (u8CountA == 25)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		u8CountA = 0;
		
	}
}

int main(void)
{
	/*Enabling clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_2);

	/*GPIO pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);

	/*PWM pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN1,0x7);
	
	/*Timer configuration*/
	TIMERConfig_t timer0BConfig;
	timer0BConfig.ptrFunc = vidBlink;
	timer0BConfig.u8TimerID = TIMERS_TIMER_2;
	timer0BConfig.u8TimerBlock = TIMERS_BLOCK_B;
	timer0BConfig.u16ReloadValue = 50000;
	timer0BConfig.u32MatchValue = 40000;
	timer0BConfig.u16PrescalerValue = 0;
	timer0BConfig.u8Config = TIMERS_CONFIG_1632_16BIT;
	timer0BConfig.u8PWM = TIMERS_PWM_ENABLED;
	timer0BConfig.u8PWMInverted = TIMERS_PWM_INVERTED;
	timer0BConfig.u8InterruptMask = TIMERS_INTERRUPT_TIMEOUT;
	timer0BConfig.u8TimerMode = TIMERS_MODE_PERIODIC;
	timer0BConfig.u8TimerCountDir = TIMERS_COUNTDIR_UP;
	TIMERS_vidInit(&timer0BConfig);
	
	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_TIMER2B);
	
	/*Enable global interrupt*/
	__enable_irq();
	
	while(1);
}