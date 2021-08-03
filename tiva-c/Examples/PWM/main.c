#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "PWM_interface.h"
#include "NVIC_interface.h"

void vidTestInterrupt(void);

volatile u32 u32Count = 0;

void vidTestInterrupt(void)
{
	u32Count++;
	if (u32Count == 70000)
	{
	//GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		u32Count = 0;
	}
	else
	{
		//GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);

	}
}

int main(void)
{
	/*Enable clock*/
	SYSCNTRL_vidEnablePWMClock(SYSCNTRL_PWM_0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	
	/*GPIO pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN6);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN6,0x4);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);

	
	/*PWM configuration*/
	PWMConfig_t PWMConfig;
	PWMConfig.u8Module = PWM_MODULE_0;
	PWMConfig.u8Generator = PWM_GENERATOR_0;
	PWMConfig.u8Channel = PWM_CHANNEL_0;
	PWMConfig.u8Output =PWM_OUTPUTACT_COMPA_UP_LOW|PWM_OUTPUTACT_LOAD_INVERT;
	PWMConfig.u8CountDirection = PWM_COUNTDIR_UP;
	PWMConfig.u16LoadVal = 62000;
	PWMConfig.u16CompVal = 6100;
	
	PWM_vidPutISRFunction(PWM_GENERATOR_0,vidTestInterrupt);
	PWM_vidEnableInterrupt(PWM_MODULE_0,PWM_GENERATOR_0,PWM_INTERRUPT_COUNT_COMPA_UP);
	
	PWM_vidInit(&PWMConfig);
		
	NVIC_vidSetInterrupt(NVIC_PWM0_0);
	
	__enable_irq();
	while(1);
}