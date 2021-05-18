#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MEXTI_private.h"
#include "MEXTI_interface.h"

void (*MEXTI_CallBack) (void);

void MEXTI_vidSetCallBack(void (*funcPtr) (void)) {
	MEXTI_CallBack = funcPtr;
}


void MEXTI_vidSetEXTIMode(u8 ID, u8 Mode) {
	switch(Mode){
		case MEXTI_MODE_RISING:
			MEXTI->RTSR |= (1<<ID);
			break;
		case MEXTI_MODE_FALLING:
			MEXTI->FTSR |= (1<<ID);
			break;
		case MEXTI_MODE_IOC:
			MEXTI->RTSR |= (1<<ID);
			MEXTI->FTSR |= (1<<ID);		
			break;
	}
}
void MEXTI_vidEnable(u8 ID) {
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}
}
void MEXTI_vidDisable(u8 ID) {
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}
}
void MEXTI_vidSetInterruptMask(u8 u8LineCpy) {
	MEXTI->IMR |= (1<<u8LineCpy);
}

void MEXTI_vidSetEventMask(u8 u8LineCpy) {
	MEXTI->EMR |= (1<<u8LineCpy);
}

void MEXTI_vidSetPending(u8 u8LineCpy) {
	MEXTI->PR |= (1<<u8LineCpy);
}

void MEXTI_vidSetRisingTrigger(u8 u8LineCpy) {
	MEXTI->RTSR |= (1<<u8LineCpy);
}

void MEXTI_vidSetFallingTrigger(u8 u8LineCpy) {
	MEXTI->FTSR |= (1<<u8LineCpy);
}

void EXTI0_IRQHandler(void) {
	MEXTI_CallBack();
	MEXTI->PR |= (1<<0);
}
