#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "TM4C123.h"                    // Device header

static volatile u8 u8CountA = 0;
static volatile u8 u8Count2 = 0;

static void vidBlink(void); 
static void vidBlink2(void);

static void vidBlink(void)
{
	u8CountA++;
	if (u8CountA == 25)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		u8CountA = 0;
		
	}
	//TIMERS_vidClearInterruptFlag(TIMERS_TIMER_1,TIMERS_INTERRUPT_BLOCKA_TIMEOUT);
}

static void vidBlink2(void)
{
	u8Count2++;
	if (u8Count2 == 250)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		u8Count2 = 0;
		
	}
	//TIMERS_vidClearInterruptFlag(TIMERS_TIMER_1,TIMERS_INTERRUPT_BLOCKA_TIMEOUT);
}

int main(void)
{
/*Enabling clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_1);
	
	/*GPIO pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	/*Timer configuration*/
	TIMERConfig_t timer0AConfig;
	timer0AConfig.ptrFunc = vidBlink;
	timer0AConfig.u8TimerID = TIMERS_TIMER_1;
	timer0AConfig.u8TimerBlock = TIMERS_BLOCK_B;
	timer0AConfig.u16ReloadValue = 3000;
	timer0AConfig.u8PrescalerValue = 3;
	timer0AConfig.u8Config = TIMER_CONFIG_1632_16BIT;
	timer0AConfig.u8InterruptMask = TIMER_TIMERA_INTERRUPT_TIMEOUT;
	timer0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_PERIODIC;
	timer0AConfig.u8TimerACountDir = TIMERS_COUNTDIR_UP;
	TIMERS_vidInit(&timer0AConfig);
	
	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_TIMER1B);
	
	/*Enable global interrupt*/
	__enable_irq();
	
	while(1);
}