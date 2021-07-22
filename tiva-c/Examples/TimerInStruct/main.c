#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"

volatile u16 u16Count = 0;
void vidBlink(void)
{
	u16Count++;
	if (u16Count == 70)
	{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN_LED_RED);
		u16Count = 0;
	}
}

int main(void)
{
	/*Enanbling clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_0);

	
	/*LED PortF configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN_LED_RED,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN_LED_RED,GPIO_DEN_SET);
	
	TIMERConfig_t TIMER0AConfig;
	TIMER0AConfig.u8Config = TIMER_CONFIG_1632_16BIT;
	TIMER0AConfig.u8TimerAMode = TIMER_TIMERA_MODE_PERIODIC;
	TIMER0AConfig.u8TimerACountDir = TIMER_TIMERA_COUNTDIR_DOWN;
	TIMER0AConfig.u16ReloadValue = 30000;
	TIMER0AConfig.u8InterruptMask = TIMER_TIMERA_INTERRUPT_TIMEOUT;
	TIMER0AConfig.ptrFunc = vidBlink;
	
	TIMERS_vidInit(&TIMER0AConfig);
	
	/*Enabling NVIC for timer0*/
	NVIC_vidSetInterrupt(NVIC_TIMER0A);
	
	/*Global interrupt enabled*/
	__enable_irq();
	while(1);
}