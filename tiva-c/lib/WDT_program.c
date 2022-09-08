#include "STD_TYPES.h"
#include "Macros.h"
#include "WDT_private.h"
#include "WDT_interface.h"

/*Pointer to function executed in interrupt handler*/
static void (*ptrFWDTHandler) (void) = NULL;

void WDT0_vidInit(const WDTConfig_t * WDTConfig)
{
	/*Setting load*/
	WATCHDOG0->LOAD = WDTConfig->u32Load;
	
	/*Interrupt type*/
	switch(WDTConfig->u8InterruptType)
	{
		case WDT_INTERRUPT_STANDARD:
		CLEAR_BIT(WATCHDOG0->CTL,2);
		break;
		case WDT_INTERRUPT_NONMASKABLE:
			SET_BIT(WATCHDOG0->CTL,2);
		break;
	}
	
	/*Setting handler function*/
	ptrFWDTHandler = WDTConfig->ptrFHandler;
}

void WDT0_vidEnable(void)
{
	SET_BIT(WATCHDOG0->CTL,0);
}

void  WDT0_Handler(void)
{
	if (ptrFWDTHandler != NULL)
	{
			ptrFWDTHandler();
	}
}

void WDT0_vidClearInterrupt(void)
{
	/*Writing any value to clear the interrupt*/
	WATCHDOG0->ICR = 1;
}