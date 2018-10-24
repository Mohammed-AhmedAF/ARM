/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Timer driver for STM32F103 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MTIM_private.h"
#include "MTIM_interface.h"

void MTIM_vidInit() {

	SET_BIT(MTIM2->CR1,MTIM_CR1_CEN);
	CLEAR_BIT(MTIM2->CR1,MTIM_CR1_DIR);
	MTIM2->PSC = 1000; /*Setting prescaler*/
	MTIM3->ARR = 1000000;
}

u16 MTIM_u16GetCount(void) {

	return (u16) MTIM2->CNT;
}

