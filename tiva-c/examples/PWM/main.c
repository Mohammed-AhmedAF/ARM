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

	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN7);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN7,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN7,0x4);
	
	/*LED*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);

	
	/*PWM configuration*/
	PWMConfig_t PWMConfig;
	PWMConfig.u8Module = PWM_MODULE_0;
	PWMConfig.u8Generator = PWM_GENERATOR_0;
	PWMConfig.u8Channel = PWM_CHANNEL_0;
	PWMConfig.u16Output =PWM_OUTPUTACT_COMPA_DOWN_LOW|PWM_OUTPUTACT_LOAD_HIGH;
	PWMConfig.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig.u16LoadVal = 50000;
	PWMConfig.u16CompVal = 25000;
	
	PWMConfig_t PWMConfigB;
	PWMConfigB.u8Module = PWM_MODULE_0;
	PWMConfigB.u8Generator = PWM_GENERATOR_0;
	PWMConfigB.u8Channel = PWM_CHANNEL_1;
	PWMConfigB.u16Output = PWM_OUTPUTACT_COMPB_DOWN_INVERT|PWM_OUTPUTACT_LOAD_HIGH;
	PWMConfigB.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfigB.u16LoadVal = 39999;
	PWMConfigB.u16CompVal = 10000;
		
	PWM_vidDisableGenerator(PWMConfig.u8Module,PWMConfig.u8Generator);
	PWM_vidConfigCountDir(PWMConfig.u8Module,PWMConfig.u8Generator,PWMConfig.u8CountDirection);
	
	PWM_vidSetOutput_test(PWMConfig.u8Module,PWMConfig.u8Generator,PWM_BLOCK_A,PWMConfig.u16Output);
	PWM_vidSetOutput_test(PWMConfigB.u8Module,PWMConfigB.u8Generator,PWM_BLOCK_B,PWMConfigB.u16Output);

	PWM_vidAssignLoadVal(PWMConfig.u8Module,PWMConfig.u8Generator,PWMConfig.u16LoadVal);
	
	PWM_vidSetCompValue(PWMConfig.u8Module,PWMConfig.u8Generator,PWMConfig.u8Channel,PWMConfig.u16CompVal);
	PWM_vidSetCompValue(PWMConfigB.u8Module,PWMConfigB.u8Generator,PWMConfigB.u8Channel,PWMConfigB.u16CompVal);

	PWM_vidSelectChannel(PWMConfig.u8Module,PWMConfig.u8Channel);
	PWM_vidSelectChannel(PWMConfigB.u8Module,PWMConfigB.u8Channel);

	PWM_vidEnableGenerator(PWMConfigB.u8Module,PWMConfigB.u8Generator);
	
	__enable_irq();
	while(1);
}