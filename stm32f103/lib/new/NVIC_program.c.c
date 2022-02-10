#include "STD_TYPES.h"
#include "Macros.h"
#include "NVIC_private.h"
#include "NVIC_interface.h"

void NVIC_vidEnableInterrupt(u8 ID) {
	if (ID >= 0 && ID<= 31) {
		NVIC->ISER[0] = (1<<ID);
	}
	else if(ID >= 32 && ID <= 59) {
		ID -= 32;
		NVIC->ISER[1] = (1<<ID);
	}
	else {

	}
}

void NVIC_vidDisableInterrupt(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		NVIC->ICER[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID = ID-32;
		NVIC->ICER[1] = (1<<32);
	}
}

void NVIC_vidSetPendingFlag(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		NVIC->ISPR[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID -= 32;
		NVIC->ISPR[1] = (1<<ID);
	}
}

void NVIC_vidClearPendingFlag(u8 ID) {
	if (ID >= 0 && ID <= 31) {
		NVIC->ICPR[0] = (1<<ID);
	}
	else if (ID >= 32 && ID <= 59) {
		ID -= 32;
		NVIC->ICPR[1] = (1<<ID);
	}

}
