/*
 * Timer driver for Tiva C
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TM4C123.h"                    // Device header


static void (*TIMER0A_vidCallBack) (void);
static void (*TIMER0B_vidCallBack) (void);

void TIMERS_vidPutFunction(u8 u8Timer,void (*ptFun) (void)) {
		switch(u8Timer)
		{
			case TIMERS_TIMER0A:
		TIMER0A_vidCallBack = ptFun;
		break;
			case TIMERS_TIMER0B:
				TIMER0B_vidCallBack = ptFun;
				break;
		}
		
}

/*A function that activates the timer on one-shoot mode*/
void TIMERS_vidStartOneShoot(u8 times)
{
    u8 i = 0;
    for (i = 0; i < times; i++)
    {

        GPTM0_CTL = 0x0;
        GPTM0_CFG = 0x00;
        GPTM0_CFG = 0x04;
        GPTM0_TAMR |= 0x01;
        GPTM0_TAMR |= TIMERS_TIMA_COUNT_UP;
        GPTM0_ICR |= 0x01;
        GPTM0_TAILR |= 65000;
        GPTM0_ICR |= 0x01;
        GPTM0_CTL |= 0x01;
        while (GET_BIT(GPTM0_RIS,0) == 0);
        GPTM0_ICR |= 0x01;
       
    }
}

void TIMERS_vidStartPeriodic(u16 u16Value)
{
    GPTM0_CTL = 0x0;
    GPTM0_CFG = 0x00;
    GPTM0_CFG = 0x04; /*16-bit timer*/
    GPTM0_TAMR |= 0x02; /*Periodic mode configured*/
    GPTM0_TAMR |= TIMERS_TIMA_COUNT_UP;
    GPTM0_IMR |= (1 <<0); /*Enable time-out interrupt*/
    GPTM0_ICR |= 0x01;
    GPTM0_TAILR |= u16Value;
    GPTM0_CTL |= 0x01; /*Enable timer*/
}

void vidInitEdgeCount(void)
{
	CLEAR_BIT(TIMER0->CTL,0); /*Ensuring that the timer is disabled*/
	TIMER0->CFG |= 0x4; /*16 bit timer configuration*/
	CLEAR_BIT(TIMER0->TAMR,2); /*Edge count*/
	TIMER0->TAMR |= 0x3; /*Capture mode*/
	SET_BIT(TIMER0->TAMR,4); /*Count direction: up*/
	TIMER0->TAMATCHR = 0xFFFF;
	TIMER0->TAPMR = 0xFF;
	CLEAR_BIT(TIMER0->CTL,2); /*Positive edge*/
	TIMER0->CTL |= (1<<0); /*Start timer*/
}

u16 TIMER0_u16GetCount(void)
{
	return (u16) TIMER0->TAR;

}


void TIMER0A_Handler(void) {
		TIMER0A_vidCallBack();
	  GPTM0_ICR = 0x01; /*To clear interrupt flag*/

}

void TIMER0B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER0B_vidCallBack();
	SET_BIT(GPTM0_ICR,8);
}

void TIMER0A_vidConfigInputCapt(TIMERConfig_t * TIMERConfig)
{

		CLEAR_BIT(GPTM0_CTL,0);
		
		switch(TIMERConfig->u8Config)
		{
			case TIMER_CONFIG_1632_16BIT:
				GPTM0_CFG |= 0x04;
				break;
			case TIMER_CONFIG_3264_32BIT:
				GPTM0_CFG |= 0x04;
				break;
			
		}
		/*Timer0 A mode*/
		switch(TIMERConfig->u8TimerAMode)
		{
			case TIMER_TIMERA_MODE_ONESHOOT:
				GPTM0_TAMR |= 0x01;
			break;
			case TIMER_TIMERA_MODE_PERIODIC:
				GPTM0_TAMR |= 0x02;
			break;
			case TIMER_TIMERA_MODE_CAPTURE:	
		GPTM0_TAMR |= 0x03;
			break;
		}
		
		/*Capture mode*/
		switch(TIMERConfig->u8TimerACaptMode)
		{
			case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
				CLEAR_BIT(GPTM0_TAMR,2);
			break;
			case TIMER_TIMERA_CAPTMODE_EDGETIMER:
				SET_BIT(GPTM0_TAMR,2);
			break;
		}
		/*Count direction*/
		switch(TIMERConfig->u8TimerACountDir)
		{
			case TIMER_TIMERA_COUNTDIR_DOWN:
				CLEAR_BIT(GPTM0_TAMR,4);
				break;
			case TIMER_TIMERA_COUNTDIR_UP:
				SET_BIT(GPTM0_TAMR,4);
			break;
		}
		
		/*Event mode*/
		switch(TIMERConfig->u8TimerAEventMode)
		{
			case TIMER_TIMERA_EVENTMODE_POSITIVE:
				TIMER0->CTL &= ~(1<<3)|~(1<<2);   /* capture rising edges on PB6 pin */
				break;
			case TIMER_TIMERA_EVENTMODE_NEGATIVE:
				CLEAR_BIT(GPTM0_CTL,3);
				SET_BIT(GPTM0_CTL,2);
			break;
			case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
				SET_BIT(GPTM0_CTL,3);
				SET_BIT(GPTM0_CTL,2);
			break;
		}

}

u32 TIMER0A_u32MeasureTimerPeriod(void)
{
int risingEdge, fallingEdge;
	  /* detect first rising edge */
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & (1<<2)) == 0) ;    /* wait till first positive edge captured */
    risingEdge = TIMER0->TAR;     /* save the timestamp */
		/* detect second rising edge */
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & (1<<2)) == 0) ;    /* wait till second positive edge captured*/
    fallingEdge = TIMER0->TAR;     /* save the timestamp */
		return (fallingEdge - risingEdge) & 0x00FFFFFF; /* return the time difference which is time period */	
}

void TIMERS_vidInit(TIMERConfig_t * TIMERConfig)
{
		CLEAR_BIT(GPTM0_CTL,0);
		
		switch(TIMERConfig->u8Config)
		{
			case TIMER_CONFIG_1632_16BIT:
				GPTM0_CFG |= 0x04;
				break;
			case TIMER_CONFIG_3264_32BIT:
				GPTM0_CFG |= 0x04;
				break;
			
		}
		/*Timer0 A mode*/
		switch(TIMERConfig->u8TimerAMode)
		{
			case TIMER_TIMERA_MODE_ONESHOOT:
				GPTM0_TAMR |= 0x01;
			break;
			case TIMER_TIMERA_MODE_PERIODIC:
				GPTM0_TAMR |= 0x02;
				GPTM0_TAILR |= TIMERConfig->u16ReloadValue;
			break;
			case TIMER_TIMERA_MODE_CAPTURE:	
		GPTM0_TAMR |= 0x03;
			break;
		}
		
		/*Capture mode*/
		switch(TIMERConfig->u8TimerACaptMode)
		{
			case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
				CLEAR_BIT(GPTM0_TAMR,2);
			break;
			case TIMER_TIMERA_CAPTMODE_EDGETIMER:
				SET_BIT(GPTM0_TAMR,2);
			break;
		}
		/*Count direction*/
		switch(TIMERConfig->u8TimerACountDir)
		{
			case TIMER_TIMERA_COUNTDIR_DOWN:
				CLEAR_BIT(GPTM0_TAMR,4);
				break;
			case TIMER_TIMERA_COUNTDIR_UP:
				SET_BIT(GPTM0_TAMR,4);
			break;
		}
		
		/*Event mode*/
		switch(TIMERConfig->u8TimerAEventMode)
		{
			case TIMER_TIMERA_EVENTMODE_POSITIVE:
				TIMER0->CTL &= ~(1<<3)|~(1<<2);   /* capture rising edges on PB6 pin */
				break;
			case TIMER_TIMERA_EVENTMODE_NEGATIVE:
				CLEAR_BIT(GPTM0_CTL,3);
				SET_BIT(GPTM0_CTL,2);
			break;
			case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
				SET_BIT(GPTM0_CTL,3);
				SET_BIT(GPTM0_CTL,2);
			break;
		}
		
		/*Interrupt mask*/
		switch(TIMERConfig->u8InterruptMask)
		{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM0_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM0_ICR |= 0x01;
					TIMERS_vidPutFunction(TIMERS_TIMER0A,TIMERConfig->ptrFunc);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM0_IMR |= (1<<1);
					GPTM0_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM0_IMR |= (1<<2);
					GPTM0_ICR |= (1<<2);
				break;
		}
    /* enable Timer0A */
		SET_BIT(GPTM0_CTL,0);
}

void TIMER0B_vidInit(TIMERConfig_t * TIMERConfig)
{
		
		CLEAR_BIT(GPTM0_CTL,8);

		switch(TIMERConfig->u8Config)
		{
			case TIMER_CONFIG_1632_16BIT:
				GPTM0_CFG |= 0x04;
				break;
			case TIMER_CONFIG_3264_32BIT:
				GPTM0_CFG |= 0x04;
				break;
			
		}
		/*Timer0 B mode*/
		switch(TIMERConfig->u8TimerAMode)
		{
			case TIMER_TIMERB_MODE_ONESHOOT:
				GPTM0_TBMR |= 0x01;
			break;
			case TIMER_TIMERB_MODE_PERIODIC:
				GPTM0_TBMR |= 0x02;
				GPTM0_TBILR |= TIMERConfig->u16ReloadValue;
			break;
			case TIMER_TIMERB_MODE_CAPTURE:	
		GPTM0_TBMR |= 0x03;
			break;
		}
		
		/*Capture mode*/
		switch(TIMERConfig->u8TimerACaptMode)
		{
			case TIMER_TIMERB_CAPTMODE_EDGECOUNT:
				CLEAR_BIT(GPTM0_TBMR,2);
			break;
			case TIMER_TIMERB_CAPTMODE_EDGETIMER:
				SET_BIT(GPTM0_TBMR,2);
			break;
		}
		/*Count direction*/
		switch(TIMERConfig->u8TimerACountDir)
		{
			case TIMER_TIMERB_COUNTDIR_DOWN:
				CLEAR_BIT(GPTM0_TBMR,4);
				break;
			case TIMER_TIMERB_COUNTDIR_UP:
				SET_BIT(GPTM0_TBMR,4);
			break;
		}
		
		/*Event mode*/
		switch(TIMERConfig->u8TimerAEventMode)
		{
			case TIMER_TIMERB_EVENTMODE_POSITIVE:
				TIMER0->CTL &= ~(1<<10)|~(1<<11);   /* capture rising edges on PB6 pin */
				break;
			case TIMER_TIMERB_EVENTMODE_NEGATIVE:
				CLEAR_BIT(GPTM0_CTL,11);
				SET_BIT(GPTM0_CTL,10);
			break;
			case TIMER_TIMERB_EVENTMODE_BOTHEDGES:
				SET_BIT(GPTM0_CTL,10);
				SET_BIT(GPTM0_CTL,10);
			break;
		}
		
		/*Interrupt mask*/
		switch(TIMERConfig->u8InterruptMask)
		{
			case TIMER_TIMERB_INTERRUPT_TIMEOUT:
				  GPTM0_IMR |= (1<<8); /*Enable time-out interrupt*/
					SET_BIT(GPTM0_ICR,8);
					TIMERS_vidPutFunction(TIMERS_TIMER0B,TIMERConfig->ptrFunc);
				break;
			case TIMER_TIMERB_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM0_IMR |= (1<<9);
					GPTM0_ICR |= (1<<9);
				break;
			case TIMER_TIMERB_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM0_IMR |= (1<<10);
					GPTM0_ICR |= (1<<10);
				break;
		}
   
				/*Enable Timer0B*/
				SET_BIT(GPTM0_CTL,8);
}

void TIMER0_vidDisable(u8 u8Timer0Sub)
{
	switch(u8Timer0Sub)
	{
		case TIMERS_TIMER0A:
		CLEAR_BIT(GPTM0_CTL,0);
		break;
		case TIMERS_TIMER0B:
		CLEAR_BIT(GPTM0_CTL,8);
		break;
	}
}	
	
void TIMER0_vidStart(void)
{
 /* enable Timer0A */
		SET_BIT(GPTM0_CTL,0);

}
