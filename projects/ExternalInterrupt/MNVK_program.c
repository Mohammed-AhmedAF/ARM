#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MNVK_private.h"
#include "MNVK_interface.h"

void MNVK_vidEnableInterrupt(u8 ID) {
	if (ID >= 0 && ID<= 31) {
		MNVK->ISER[0] = (1<<ID);
	}
	else if(ID >= 32 && ID <= 59) {
		ID -= 32;
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
