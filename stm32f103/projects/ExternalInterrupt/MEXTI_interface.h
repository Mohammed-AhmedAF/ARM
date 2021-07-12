#ifndef _MEXTI_INTERFACE_H
#define _MEXTI_INTERFACE_H

#define MEXTI_MODE_RISING 1
#define MEXTI_MODE_FALLING 2
/*On change*/
#define MEXTI_MODE_IOC 3 

#define MEXTI_ID_0 0

void EXTI0_vidSetCallBack(void (*func) (void));
void EXTI_vidSetEXTIMode(u8 ID, u8 Mode);
void EXTI1_vidSetCallBack(void (*funcPtr) (void));
void EXTI_vidSetCallback(u8 u8LineID,void (*funcPtr) (void));

void EXTI_vidEnable(u8 ID);
void EXTI_vidEnable(u8 ID);

void EXTI_vidSetInterruptMask(u8 u8LineCpy);
void EXTI_vidSetEventMask(u8 u8LineCpy);
void EXTI_vidSetPending(u8 u8LineCpy);
void EXTI_vidSetFallingTrigger(u8 u8LineCpy);
void EXTI_vidSetRisingTrigger(u8 u8LineCpy);

#define EXTI_LINE_0 0
#define EXTI_LINE_1 1
#define EXTI_LINE_2 2
#define EXTI_LINE_3 3
#define EXTI_LINE_4 4
#define EXTI_LINE_5 5
#define EXTI_LINE_6 6
#define EXTI_LINE_7 7
#define EXTI_LINE_8 8 
#define EXTI_LINE_9 9
#define EXTI_LINE_10 10

#endif
