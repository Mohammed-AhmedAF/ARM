#include "Macros.h"
#include "STD_TYPES.h"
#include "SCB_interface.h"
#include "TM4C123.h"

static void (*pFunPendSV) (void);

void SCB_vidTriggerPendSV(void)
{
		SET_BIT(SCB->ICSR,28);

}

void SCB_vidPutISR(u8 u8InterruptID, void (*ptrF)(void))
{
	switch(u8InterruptID)
	{
		case SCB_INTERRUPT_PENDSV:
			pFunPendSV = ptrF;
		break;
	
	}
	
}

 void PendSV_Handler()
 {
	pFunPendSV();
 }