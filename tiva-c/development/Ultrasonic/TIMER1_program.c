#include "Macros.h"
#include "STD_TYPES.h"
#include "TIMER1_private.h"
#include "TIMER1_interface.h"

void TIMER1_vidInit(u16 u16LoadVal, u16 u16PrescaleVal)
{
	/*Timer configuration (16-bit)*/
	SET_BIT(TIMER1->CFG,2);
	
	/**Timer mode**/
	/*Periodic-shot mode, count down*/
	TIMER1->TAMR |= 0x12;
	
	/*Prescaler*/ 
//	TIMER0->TAPR = u16PrescaleVal;
	
	/*Load value*/
	TIMER1->TAILR = u16LoadVal;
	
	SET_BIT(TIMER1->ICR,0);	
	
	/*Enable timer*/
	SET_BIT(TIMER1->CTL,0);
	
}

void TIMER1_vidDelayMicro(u32 u32Micro)
{
	static u32 i;
	
	TIMER1_vidInit((16)*u32Micro,0);
	while((TIMER1->RIS & 0x1) == 0);
	SET_BIT(TIMER1->ICR,0);
}
