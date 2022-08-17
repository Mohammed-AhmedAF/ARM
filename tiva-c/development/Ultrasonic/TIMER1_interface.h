#ifndef _TIMER1_INTERFACE_H
#define _TIMER1_INTERFACE_H
void TIMER1_vidInit(u16 u16LoadVal, u16 u16PrescaleVal);
void TIMER1_vidDelayMicro(u32 u32Micro);
#endif