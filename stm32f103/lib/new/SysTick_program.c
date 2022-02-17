/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: STK driver for stm32f103c8t6 MCU
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "SysTick_private.h"
#include "SysTick_interface.h"

void (*STK_CallBack) (void); /*Pointer to function*/




void SysTick_vidInit(SysTickConfig_t * sysTickConfig)
{
	/*Clock source*/
	if (sysTickConfig->u8ClockSource == SYSTICK_CLOCK_PROCESSOR)
	{
		SET_BIT(STK->CTRL,2);
	}
	else
	{
		CLEAR_BIT(STK->CTRL,2);
	}
	
	/*Interrupt Request*/
	if (sysTickConfig->u8InterruptReq == SYSTICK_INTERRUPT_ENABLED)
	{
		SET_BIT(STK->CTRL,1);
	}
	else
	{
		CLEAR_BIT(STK->CTRL,1);
	}
	
	SysTick_vidSetCallBack(sysTickConfig->ptrFun);
	
	/*Reload value*/
	STK->LOAD = sysTickConfig->u32ReloadValue;
}

void SysTick_vidStart(void)
{
	SET_BIT(STK->CTRL,0);
}


void SysTick_vidSetCallBack(void (*ptrFunc) (void)) {
	STK_CallBack = ptrFunc;
}


/*Interrupt Handler*/
void SysTick_Handler(void) {
	STK_CallBack();
}
