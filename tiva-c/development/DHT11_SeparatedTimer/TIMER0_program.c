#include "Macros.h"
#include "STD_TYPES.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"


static void (*ptrFCallback) (void) = NULL;
u32 u32OVFCount = 0;
volatile u8 u8DelayFlag = 0;
volatile u32 u32DelayMicro = 0;

void vidCountOVF(void)
{
	u32OVFCount++;
}

inline void TIMER0_vidInitOneShoot(u16 u16LoadVal)
{
	
	/*Timer configuration (16-bit)*/
	SET_BIT(TIMER0->CFG,2);
	
	/**Timer mode**/
	/*One-Shoot mode, count down*/
	TIMER0->TAMR |= 0x11;
	
	/*Prescaler*/ 
	//TIMER0->TAPR = u16PrescaleVal;
	
	/*Load value*/
	TIMER0->TAILR = u16LoadVal;
		
	/*Enable timer*/
	SET_BIT(TIMER0->CTL,0);
}

void TIMER0_vidInit(u16 u16LoadVal, u16 u16PrescaleVal)
{
	/*Timer configuration (16-bit)*/
	SET_BIT(TIMER0->CFG,2);
	
	/**Timer mode**/
	/*Periodic-shot mode, count down*/
	TIMER0->TAMR |= 0x12;
	
	/*Prescaler*/ 
//	TIMER0->TAPR = u16PrescaleVal;
	
	/*Load value*/
	TIMER0->TAILR = u16LoadVal;
	
	SET_BIT(TIMER0->ICR,0);	
	
	/*Enable timer*/
	SET_BIT(TIMER0->CTL,0);
	
}

void TIMER0_vidDisableTimer(void)
{
	TIM0_CTL=0;
}

void TIMER0_vidPutISRFunction(void (*ptrF) (void))
{
	ptrFCallback = ptrF;
}

__inline void TIMER0_vidDelayMirco_test2(u32 u32Micro)
{
	static u32 i;
	
	TIMER0_vidInitOneShoot((16*u32Micro));
	while((TIMER0->RIS & 0x1) == 0);
	SET_BIT(TIMER0->ICR,0);
}

__inline void TIMER0_vidDelayMirco(u32 u32Micro)
{
	static u32 i;
	
	TIMER0_vidInit((16)*u32Micro,0);
	while((TIMER0->RIS & 0x1) == 0);
	SET_BIT(TIMER0->ICR,0);
}

void TIMER0_vidDelayMilli(u32 u32MilliDelay)
{
		u32 i;
		TIMER0_vidInit(16000-1,0);
    for(i = 0; i < u32MilliDelay; i++) {
			while ((TIMER0->RIS & 0x1) == 0);      /* wait for TimerA timeout flag */
      TIMER0->ICR = 0x1;      /* clear the TimerA timeout flag */
    }
}

void TIMER0_vidDelayMicro_old(u32 u32Micro)
{
	TIMER0->TAV = 0;
	u32DelayMicro = u32Micro;
	u8DelayFlag = 1;
	while(u8DelayFlag)
	{
		__disable_irq();
		if (u32OVFCount == u32DelayMicro)
		{
			u32OVFCount = 0;
			break;
		}
		__enable_irq();
	}
}

void TIMER0A_Handler(void)
{
	if (ptrFCallback != NULL)
	{
		ptrFCallback();
	}
	SET_BIT(TIMER0->ICR,0);
}
