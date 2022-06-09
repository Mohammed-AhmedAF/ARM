#include "Macros.h"
#include "STD_TYPES.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "TM4C123.h"                    // Device header

static void (*ptrFCallback) (void) = NULL;

u32 u32OVFCount = 0;
volatile u8 u8DelayFlag = 0;
volatile u32 u32DelayMicro = 0;

void vidCountOVF(void)
{
	u32OVFCount++;
	
	
}

void TIMER0_vidInit(u16 u16LoadVal, u16 u16PrescaleVal)
{
	/*Enabling clock access to timer*/
	SET_BIT(SYSCTL->RCGCTIMER,0); 

	/*Timer configuration (16-bit)*/
	SET_BIT(TIM0_CFG,2);
	
	/**Timer mode**/
	/*Periodic*/
	SET_BIT(TIM0_TAMR,1);
	/*Count direction: down*/
	CLEAR_BIT(TIM0_TAMR,4);
	
	/*Prescaler*/ 
	TIM0_TAPR = u16PrescaleVal;
	
	/*Load value*/
	TIM0_TAILR = u16LoadVal;
	
	/*Interrupt on timer-out*/
	SET_BIT(TIM0_IMR,0);
	
	/*Enable timer*/
	SET_BIT(TIM0_CTL,0);
	
	NVIC_EnableIRQ(19);
}

void TIMER0_vidPutISRFunction(void (*ptrF) (void))
{
	ptrFCallback = ptrF;
}

void TIMER0_vidDelayMicro(u32 u32Micro)
{
	TIM0_TAV = 0;
	u32DelayMicro = u32Micro;
	u8DelayFlag = 1;
	while(u8DelayFlag)
	{
		__disable_irq();
		if (u32OVFCount == u32DelayMicro)
		{
			u32OVFCount = 0;
			break;
		}
		__enable_irq();
	}
	
	
}

void TIMER0A_Handler()
{
	if (ptrFCallback != NULL)
	{
		ptrFCallback();
	}
	SET_BIT(TIM0_ICR,0);
}