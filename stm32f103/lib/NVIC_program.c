/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: NVIC driver for stm32f103c8t6 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "NVIC_private.h"
#include "NVIC_interface.h"

void NVIC_vidEnableInterrupt(u8 u8InterruptNumber) {
	if (u8InterruptNumber >= 0 && u8InterruptNumber<= 31) {
		SET_BIT(NVIC->ISER[0],u8InterruptNumber);
	}
	else if(u8InterruptNumber <= 59) {
		u8InterruptNumber -= 32; /*To make the ID between 0 and 32,
			    as the ID is actually between 0 and 59 in
			    STM32F103C8t6 MCU
		*/
		SET_BIT(NVIC->ISER[1],1<<u8InterruptNumber);
	}
	else {
		/*Return error*/
	}
}

void NVIC_vidDisableInterrupt(u8 ID) {
	if (ID <= 31) {
		NVIC->ICER[0] = (1<<ID);
	}
	else if (ID <= 59) {
		ID = ID-32;
		NVIC->ICER[1] = (1<<ID);
	}
}

void NVIC_vidSetPendingFlag(u8 ID) {
	if (ID <= 31) {
		NVIC->ISPR[0] = (1<<ID);
	}
	else if (ID <= 59) {
		ID -= 32;
		NVIC->ISPR[1] = (1<<ID);
	}
	else
	{
		/*Return error*/
	}

}

void  NVIC_vidClearPendingFlag(u8 ID) {
	if (ID <= 31) {
		NVIC->ICPR[0] = (1<<ID);
	}
	else if (ID <= 59) {
		ID -= 32;
		NVIC->ICPR[1] = (1<<ID);
	}

}

u8 NVIC_u8GetActiveFlag(u8 ID)
{
	u8 u8Flag;
	if (ID <= 31) {
		u8Flag = GET_BIT(NVIC->IABR[0],ID);
		return u8Flag;
	}
	else if (ID <= 59) {
		ID -= 32;
		u8Flag = GET_BIT(NVIC->IABR[1],ID);
		return u8Flag;
	}
	else
	{
		/*Return error*/
	}
}

void NVIC_vidSetPriority(s8 s8InterruptID, u8 u8GroupPriority, u8 u8SubPriority, u32 u32Group)
{
	u8 u8LocalPriority = u8SubPriority|(u8GroupPriority<<((u32Group-0x05FA0300)/256)); 
	/*Core peripheral*/

	/*External peripheral*/
	if (s8InterruptID >= 0)
	{
		NVIC_IPR[s8InterruptID] = (u8LocalPriority << 4);
	}
	SCB_AIRCR = u32Group;
}
