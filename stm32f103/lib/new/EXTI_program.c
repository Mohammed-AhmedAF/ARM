#include "LSTD_TYPES.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"



void  (*EXTI_CallBack) (void);
void  (*EXTI1_CallBack) (void);

void (*EXTI_Callback_Arr[15]) (void);

void EXTI0_vidSetCallBack(void (*funcPtr) (void)) {
	EXTI_CallBack = funcPtr;

}

void EXTI1_vidSetCallBack(void (*funcPtr) (void)) {
	EXTI1_CallBack = funcPtr;
}

void EXTI_vidSetCallback(u8 u8LineID,void (*funcPtr) (void))
{
	EXTI_Callback_Arr[u8LineID] = funcPtr;
}

void EXTI_vidSetEXTIMode(u8 ID, u8 Mode)
{
	switch(Mode){
	case EXTI_MODE_RISING:
		EXTI->RTSR |= (1<<ID);
		break;
	case EXTI_MODE_FALLING:
		EXTI->FTSR |= (1<<ID);
		break;
	case EXTI_MODE_IOC:
		EXTI->RTSR |= (1<<ID);
		EXTI->FTSR |= (1<<ID);
	break;
	}
}

void EXTI_vidEnable(u8 ID) {
	if (ID <= 18) {
		EXTI->IMR |= (1<<ID);
	}

}
void EXTI_vidDisable(u8 ID)
{
	if (ID <= 18) {
		EXTI->IMR |= (1<<ID);
	}
}
	


void EXTI0_IRQHandler(void) {
	EXTI_Callback_Arr[0]();
	EXTI->PR |= 1;
}

void EXTI1_IRQHandler(void) {
	EXTI_Callback_Arr[1]();
	EXTI->PR |= 2;
}