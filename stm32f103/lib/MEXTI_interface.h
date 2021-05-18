#ifndef _MEXTI_INTERFACE_H
#define _MEXTI_INTERFACE_H

#define MEXTI_MODE_RISING 1
#define MEXTI_MODE_FALLING 2
#define MEXTI_MODE_IOC 3

#define MEXTI_LINE0 0
#define MEXTI_LINE1 1

void MEXTI_vidSetEXTIMode(u8 ID, u8 Mode);
void MEXTI_vidEnable(u8 ID);
void MEXTI_vidEnable(u8 ID);
void MEXTI_vidSetInterruptMask(u8 u8LineCpy);
void MEXTI_vidSetEventMask(u8 u8LineCpy);
void MEXTI_vidSetPending(u8 u8LineCpy);
void MEXTI_vidSetFallingTrigger(u8 u8LineCpy);
void MEXTI_vidSetRisingTrigger(u8 u8LineCpy);

void MEXTI_vidSetCallBack(void (*funcPtr) (void));

#endif
