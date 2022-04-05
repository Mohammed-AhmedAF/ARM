#ifndef _SCB_INTERFACE_H
#define _SCB_INTERFACE_H

/*Function definitions*/
void SCB_vidTriggerPendSV(void);
void SCB_vidPutISR(u8 u8InterruptID, void (*ptrF)(void));

/*Macros*/
#define SCB_INTERRUPT_PENDSV 22

#endif