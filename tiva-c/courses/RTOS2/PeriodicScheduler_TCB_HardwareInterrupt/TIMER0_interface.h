#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H

void TIMER0_vidInit(void);
void TIMER0_vidPutISRFunction(void (*ptrF) (void));

#endif