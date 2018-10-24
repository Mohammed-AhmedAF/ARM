/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Timer driver for STM32F103 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MTIM_private.h"
#include "MTIM_interface.h"

void (*ptrFunc) (void);

void MTIM_vidPutFunction(void (*ptrF) (void)) {
	ptrFunc = ptrF;
}

void MTIM_vidInit() {

	MTIM2->PSC = 0; /*Setting prescaler*/
	MTIM2->ARR = 255;
	SET_BIT(MTIM2->DIER,MTIM_DIER_UIE);
	CLEAR_BIT(MTIM2->CR1,MTIM_CR1_DIR);
	SET_BIT(MTIM2->CR1,MTIM_CR1_CEN);

}

u16 MTIM_u16GetCount(void) {
	return (u16) MTIM2->CNT;
}

void TIM2_IRQHandler(void) {

	CLEAR_BIT(MTIM2->SR,0);

	ptrFunc();

}
