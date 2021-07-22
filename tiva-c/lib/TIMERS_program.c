/*
 * Timer driver for Tiva C
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TM4C123.h"                    // Device header


static void (*TIMERS_vidCallBack) (void);

void TIMERS_vidPutFunction(void (*ptFun) (void)) {
		TIMERS_vidCallBack = ptFun;
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

void TIMER0A_Handler(void) {
		TIMERS_vidCallBack();
	  GPTM0_ICR = 0x01; /*To clear interrupt flag*/

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
    /* enable Timer0A */
		SET_BIT(GPTM0_CTL,0);

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
				  GPTM0_IMR |= (1 <<0); /*Enable time-out interrupt*/
					GPTM0_ICR |= 0x01;
					TIMERS_vidPutFunction(TIMERConfig->ptrFunc);
				break;
		}
    /* enable Timer0A */
		SET_BIT(GPTM0_CTL,0);


}