#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "SysTick_interface.h"

void vidGeneratePWM(void);

void vidGeneratePWM(void)
{
	static u8 u8PWMDuty = 0;
	if (u8PWMDuty < 2)
	{
		GPIO_vidSetPinValue(GPIO_PORTA,GPIO_PIN6,STD_HIGH);
		GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN1,STD_HIGH);
	}
	else {
		GPIO_vidSetPinValue(GPIO_PORTA,GPIO_PIN6,STD_LOW);
		GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN1,STD_LOW);
	}
	
	u8PWMDuty++;
	if (u8PWMDuty == 10)
	{
	 u8PWMDuty = 0;
	}
}


int main(void)
{
	/*Enable clock for GPIO peripheral*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*GPIO configuration*/
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN6,GPIO_OUTPUT);
	
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	
	/*SysTick configuration*/
	/*SysTick to cause an interrupt each 1/10 of a second*/
	SysTickConfig_t sysConfig;
	sysConfig.ptrFunc = vidGeneratePWM;
	sysConfig.u32ReloadValue = 160000;
	sysConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	sysConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	SysTick_vidInitExtended(&sysConfig);
	SysTick_vidStart();
	
	/*Enabling non-maskable interrupts*/
	__enable_irq();
	
	while(1);
}