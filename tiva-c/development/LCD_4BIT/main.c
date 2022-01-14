#include "Macros.h"
#include "STD_TYPES.h"
#include "SYSCNTRL_interface.h"
#include "LCD_interface.h"
#include "SysTick_interface.h"

void vidTest(void)
{
	LCD_vidWriteCharacter('a');
}

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	
	LCD_vidInit();
	
	SysTickConfig_t sysTickConfig;
	sysTickConfig.ptrFunc = vidTest;
	sysTickConfig.u32ReloadValue = 16000000;
	sysTickConfig.u8Interrupt = SYSTICK_INTERRUPT_ENABLED;
	sysTickConfig.u8ClockSource = SYSTICK_SYSTEM_CLOCK;
	
	SysTick_vidInitExtended(&sysTickConfig);
	SysTick_vidStart();
	
	while(1)
	{
		
	}
}