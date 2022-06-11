#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H

void TIMER0_vidInit(u16 u16LoadVal, u16 u16PrescaleVal);
void TIMER0_vidPutISRFunction(void (*ptrF) (void));
void TIMER0_vidDelayMicro(u32 u32Micro);
void TIMER0_viDelayMirco_test(u32 u32Micro);
void TIMER0_vidDelayMilli(u32 u32Milli);
#define TIMER0_MICRO_DIV 4

#endif