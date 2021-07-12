#include "LSTD_TYPES.h"
#include "MEXTI_private.h"
#include "MEXTI_interface.h"



void  (*MEXTI_CallBack) (void);
void  (*MEXTI1_CallBack) (void);

void (*MEXTI_Callback_Arr[15]) (void);

void EXTI0_vidSetCallBack(void (*funcPtr) (void)) {
	MEXTI_CallBack = funcPtr;

}

void EXTI1_vidSetCallBack(void (*funcPtr) (void)) {
	MEXTI1_CallBack = funcPtr;
}

void EXTI_vidSetCallback(u8 u8LineID,void (*funcPtr) (void))
{
	MEXTI_Callback_Arr[u8LineID] = funcPtr;
}

void EXTI_vidSetEXTIMode(u8 ID, u8 Mode)
{
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

void EXTI_vidEnable(u8 ID) {
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}

}
void EXTI_vidDisable(u8 ID)
{
	if (ID <= 18) {
		MEXTI->IMR |= (1<<ID);
	}
}
	


void EXTI0_IRQHandler(void) {
	MEXTI_Callback_Arr[0]();
	MEXTI->PR |= 1;
}

void EXTI1_IRQHandler(void) {
	MEXTI_Callback_Arr[1]();
	MEXTI->PR |= 2;
}