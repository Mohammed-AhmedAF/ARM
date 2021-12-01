#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "I2C_interface.h"

void vidBlinkOnSysTick(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_LED_RED);
	I2C3_u8SendByte(2,0,'a');
}


void SYSTICK_vidInitialize(void)
{
	SysTickConfig_t sysTickConfig;
	sysTickConfig.ptrFunc = vidBlinkOnSysTick;
	sysTickConfig.u32ReloadValue = 15998355;
	sysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	
	SysTick_vidInitExtended(&sysTickConfig);
	SysTick_vidStart();
}