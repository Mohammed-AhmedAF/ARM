#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H

/*Function defintions*/
void TIMER0_vidInitOneShoot(u16 u16LoadVal);
void TIMER0_vidInit(u16 u16LoadVal, u16 u16PrescaleVal);
void TIMER0_vidPutISRFunction(void (*ptrF) (void));
void TIMER0_vidDelayMicro_old(u32 u32Micro);
void TIMER0_vidDelayMirco(u32 u32Micro);
void TIMER0_vidDelayMilli(u32 u32Milli);
void TIMER0_viDelayMirco_test2(u32 u32Micro);
void TIMER0A_Handler(void);

#define TIMER0_MICRO_DIV 4

/*Macro function*/
#define TIMER0_DISABLE_TIMER() TIM0_CTL=0
#define TIMER0_ENABLE_TIMER() TIM0_CTL=1

#endif
