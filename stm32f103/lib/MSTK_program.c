/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: STK driver for stm32f103c8t6 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MSTK_private.h"
#include "MSTK_interface.h"

void (*MSTK_CallBack) (void); /*Pointer to function*/

void MSTK_vidInit(void) {
	MSTK->CTRL = 3;
	MSTK->VAL = 1000000;
	MSTK->LOAD = 1000000;
}

void MSTK_vidSetCallBack(void (*ptrFunc) (void)) {
	MSTK_CallBack = ptrFunc;
}


/*Interrupt Handler*/
void SysTick_Handler(void) {
	MSTK_CallBack();
}
