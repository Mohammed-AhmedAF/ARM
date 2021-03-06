/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: NVIC driver for stm32f103c8t6 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MNVK_private.h"
#include "MNVK_interface.h"

void MNVK_vidEnableInterrupt(u8 ID) {
	if (ID >= 0 && ID<= 31) {
		MNVK->ISER[0] = (1<<ID);
	}
	else if(ID >= 32 && ID <= 59) {
		ID -= 32; /*To make the ID between 0 and 32,
			    as the ID is actually between 0 and 59 in
			    STM32F103C8t6 MCU
		*/
		MNVK->ISER[1] = (1<<ID);
	}
	else {

	}
}

void MNVK_vidDisableInterrupt(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		MNVK->ICER[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID = ID-32;
		MNVK->ICER[1] = (1<<32);
	}
}

void MNVK_vidSetPendingFlag(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		MNVK->ISPR[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID -= 32;
		MNVK->ISPR[1] = (1<<ID);
	}

}

void  MNVK_vidClearPendingFlag(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		MNVK->ICPR[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID -= 32;
		MNVK->ICPR[1] = (1<<ID);
	}

}
