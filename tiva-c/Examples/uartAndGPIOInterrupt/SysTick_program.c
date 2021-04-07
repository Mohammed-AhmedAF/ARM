#include "STD_TYPES.h"
#include "Macros.h"
#include "SysTick_private.h"
#include "SysTick_interface.h"


void (*callback) (void);

void SysTick_vidInit(u8 u8isClockSource, u8 u8isInterruptEnabled) {
	/*Configuring Clock Source*/
	if (u8isClockSource == SYSTICK_SYSTEM_CLOCK) {
		SET_BIT(SysTick->CTRL,SYSTEM_CLOCK);
	}
	else {
		CLEAR_BIT(SysTick->CTRL,SYSTEM_CLOCK);
	}
	/*Configuring Interrupt Enabled*/
	if (u8isInterruptEnabled == SYSTICK_INTERRUPT_ENABLED) {
		SET_BIT(SysTick->CTRL,INTERRUPT_ENABLE);
	}
	else {
		CLEAR_BIT(SysTick->CTRL,INTERRUPT_ENABLE);
	}

}

void SysTick_vidPutISR(void (*pf) (void))
{
	callback = pf;
}

void SysTick_vidStart(void) {
	SET_BIT(SysTick->CTRL,ENABLE_SYSTICK);
}

void SysTick_vidSetValue(u32 u32Value) {
	SysTick->RELOAD = u32Value;
}

u32 SysTick_u32GetCurrentValue(void) {
	return SysTick->CURRENT;
}

void SysTick_Handler()
{
	callback();
}