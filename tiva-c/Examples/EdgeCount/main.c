#include "TM4C123.h"                    // Device header
#include "Macros.h"
#include "STD_TYPES.h"
#include "SysTick_interface.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"


u16 TIMER0_u16GetCount(void);
void getCountForOneSec(void);
void vidInitEdgeCount(void);


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

u16 TIMER0_u16GetCount(void)
{
	return (u16) TIMER0->TAR;

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

void vidInitEdgeCount(void)
{
	CLEAR_BIT(TIMER0->CTL,0); /*Ensuring that the timer is disabled*/
	TIMER0->CFG |= 0x4; /*16 bit timer configuration*/
	CLEAR_BIT(TIMER0->TAMR,2); /*Edge count*/
	TIMER0->TAMR |= 0x3; /*Capture mode*/
	SET_BIT(TIMER0->TAMR,4); /*Count direction: up*/
	TIMER0->TAMATCHR = 0xFFFF;
	TIMER0->TAPMR = 0xFF;
	CLEAR_BIT(TIMER0->CTL,2); /*Positive edge*/
	TIMER0->CTL |= (1<<0); /*Start timer*/
}