#include "LSTD_TYPES.h"
#include "Macros.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

void MEXTI_vidSetEXTIMode(u8 ID, u8 Mode) {
	case MEXTI_MODE_RISING:
		MEXTI->RSTR |= (1<<ID);
		break;
	case MEXTI_MODE_FALLING:
		MEXTI->FSTR |= (1<<ID);
		break;
	case MEXTI_MODE_IOC:
		MEXTI->RSTR |= (1<<ID);
		MEXTI->SFTR |= (1<<ID);		
	break;
}
void MEXTI_vidEnable(u8 ID) {
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}
}
void MEXTI_vidDisable(u8 ID);
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}
	
void MEXTI_vidSetInterruptMask(u8 u8LineCpy) {
	MEXTI->IMR |= (1<<u8LineCpy);
}

void MEXTI_vidSetEventMask(u8 u8LineCpy) {
	MEXTI->EMR |= (1<<u8LineCpy);
}

void MEXTI_vidSetPending(u8 u8LineCpy) {
	MEXTI->PR |= (1<<u8LinCpy);
}

void MEXTI_vidSetRisingTrigger(u8 u8LineCpy) {
	MEXTI->RSTR |= (1<<u8LineCpy);
}

void MEXTI_vidSetFallingTrigger(u8 u8LineCpy) {
	MEXTI->FSTR |= (1<<u8LineCpy);
}
