#include "Macros.h"
#include "STD_TYPES.h"
#include "SCB_private.h"
#include "SCB_interface.h"

void SCB_vidEnterSleepMode(u8 u8SleepMode)
{
	switch(u8SleepMode)
	{
		case SCB_SLEEPMODE_DEEP:
			SET_BIT(SYSCTRL,2);
		  __asm__("wfi");
			break;
	
	}
}