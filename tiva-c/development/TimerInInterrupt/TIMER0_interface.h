#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H

void TIMER0_vidInit(u16 u16LoadVal, u16 u16PrescaleVal);
void TIMER0_vidPutISRFunction(void (*ptrF) (void));
void TIMER0_vidDelayMicro(u32 u32Micro);

#define TIMER0_MICRO_DIV 4

#endif