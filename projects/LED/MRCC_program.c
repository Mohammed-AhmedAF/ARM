/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: RCC driver for stm32f103c8t6 MCU
 *
 */

#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MRCC_private.h"
#include "MRCC_interface.h"

void MRCC_vidInit(void) {
	MRCC->CR = 0x00010000;
	MRCC->CFGR = 0x00000001;
}

void MRCC_vidEnableClock(u8 u8BusCpy, u8 u8PeripheralCpy) {
	switch(u8BusCpy) {
		case BUS_AHB:
			MRCC->AHBENR |= u8PeripheralCpy;
			break;
		case BUS_APB1:
			MRCC->APB1ENR |= u8PeripheralCpy;
			break;
		case BUS_APB2:
			MRCC->APB2ENR |= u8PeripheralCpy;
			break;
	}
}

void MRCC_vidDisableClock(u8 u8BusCpy, u8 u8PeripheralCpy) {
	switch(u8BusCpy) {
		case BUS_AHB:
			CLEAR_BIT(MRCC->AHBENR,3);
			break;
		case BUS_APB1:
			CLEAR_BIT(MRCC->APB1ENR,4);
			break;
		case BUS_APB2:
			CLEAR_BIT(MRCC->APB2ENR,5);
			break;
	}
}
