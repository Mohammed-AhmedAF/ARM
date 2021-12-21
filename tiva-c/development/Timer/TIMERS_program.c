/*
 * Timer driver for Tiva C
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TM4C123.h" // Device header

static void (*TIMER0A_vidCallBack)(void);
static void (*TIMER0B_vidCallBack)(void);
static void (*TIMER1A_vidCallBack)(void);
static void (*TIMER1B_vidCallBack)(void);
static void (*TIMER2A_vidCallBack)(void);
static void (*TIMER2B_vidCallBack)(void);
static void (*TIMER3A_vidCallBack)(void);
static void (*TIMER3B_vidCallBack)(void);
static void (*TIMER4A_vidCallBack)(void);
static void (*TIMER4B_vidCallBack)(void);
static void (*TIMER5A_vidCallBack)(void);
static void (*TIMER5B_vidCallBack)(void);

void TIMERS_vidInit(TIMERConfig_t *TIMERConfig)
{
	/*Disable timer*/
	TIMERS_vidDisableTimer(TIMERConfig->u8TimerID, TIMERConfig->u8TimerBlock);

	/*Timer configuration*/
	TIMERS_vidSelectTimerConfig(TIMERConfig->u8TimerID, TIMERConfig->u8Config);

	if (TIMERConfig->u8TimerBlock == TIMERS_BLOCK_A)
	{
		/*Timer mode*/
		TIMERS_vidSelectModeA(TIMERConfig->u8TimerID, TIMERConfig->u8TimerMode);
		
		/*Setting load value*/
		TIMERS_vidSetLoadValueA(TIMERConfig->u8TimerID,TIMERConfig->u16ReloadValue);

		/*Setting prescaler*/
		TIMERS_vidSetPrescalerValueA(TIMERConfig->u8TimerID,TIMERConfig->u16PrescalerValue);

		/*Count direction*/
		TIMERS_vidSelectCountDirectionA(TIMERConfig->u8TimerID, TIMERConfig->u8TimerCountDir);
		
		/*Match*/
		TIMERS_vidSetMatchValueA(TIMERConfig->u8TimerID,TIMERConfig->u32MatchValue);
		
		/*PWM*/
		TIMERS_vidConfigPWMA(TIMERConfig->u8TimerID,TIMERConfig->u8PWM);
		
		
		/*Interrupt mask*/
		TIMERS_vidEnableInterruptA(TIMERConfig->u8TimerID,TIMERConfig->u8InterruptMask);
		
		/*Capture mode*/
		TIMERS_vidSelectCaptModeA(TIMERConfig->u8TimerID, TIMERConfig->u8TimerCaptMode);
		
		/*Event mode*/
		TIMERS_vidSelectEventModeA(TIMERConfig->u8TimerID,TIMERConfig->u8TimerEventMode);
	}
	else
	{
		/*Timer mode*/
		TIMERS_vidSelectModeB(TIMERConfig->u8TimerID, TIMERConfig->u8TimerMode);
		
		/*Load value*/
		TIMERS_vidSetLoadValueB(TIMERConfig->u8TimerID,TIMERConfig->u16ReloadValue);
		
		/*Prescaler*/
		TIMERS_vidSetPrescalerValueB(TIMERConfig->u8TimerID,TIMERConfig->u16PrescalerValue);
		
		/*Count direction*/
		TIMERS_vidSelectCountDirectionB(TIMERConfig->u8TimerID, TIMERConfig->u8TimerCountDir);
		
		/*Match*/
		TIMERS_vidSetMatchValueB(TIMERConfig->u8TimerID,TIMERConfig->u32MatchValue);
		
		/*PWM*/
		TIMERS_vidConfigPWMB(TIMERConfig->u8TimerID,TIMERConfig->u8PWM);
		
		/*PWM inversion*/
		TIMERS_vidInvertPWMB(TIMERConfig->u8TimerID,TIMERConfig->u8PWMInverted);
		
		/*Enable interrupt*/
		TIMERS_vidEnableInterruptB(TIMERConfig->u8TimerID,TIMERConfig->u8InterruptMask);
	}
	


	u8 u8InterruptID = TIMERS_u8GetInterruptID(TIMERConfig->u8TimerID,TIMERConfig->u8TimerBlock);
	TIMERS_vidPutFunction(u8InterruptID,TIMERConfig->ptrFunc);
	/*Enable timer 0*/
	TIMERS_vidEnableTimer(TIMERConfig->u8TimerID,TIMERConfig->u8TimerBlock);
}

u8 TIMERS_u8GetInterruptID(u8 u8TimerID, u8 u8TimerBlock)
{
	u8 u8InterruptID = TIMERS_TIMER0A;
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER0A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER0B;
			}
			break;
		case TIMERS_TIMER_1:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER1A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER1B;
			}
			break;
		case TIMERS_TIMER_2:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER2A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER2B;
			}
			break;
		case TIMERS_TIMER_3:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER3A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER3B;
			}
			break;
		case TIMERS_TIMER_4:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER4A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER4B;
			}
			break;
		case TIMERS_TIMER_5:
			if (u8TimerBlock == TIMERS_BLOCK_A)
			{
				u8InterruptID = TIMERS_TIMER5A;
			}
			else
			{
				u8InterruptID = TIMERS_TIMER5B;
			}
			break;
	}
	return u8InterruptID;
}

void TIMERS_vidPutFunction(u8 u8Timer, void (*ptFun)(void))
{
	switch (u8Timer)
	{
	case TIMERS_TIMER0A:
		TIMER0A_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER0B:
		TIMER0B_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER1A:
		TIMER1A_vidCallBack = ptFun;
	break;
	case TIMERS_TIMER1B:
		TIMER1B_vidCallBack = ptFun;
	break;
	case TIMERS_TIMER2A:
		TIMER2B_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER2B:
		TIMER2B_vidCallBack = ptFun;
	break;
	case TIMERS_TIMER3A:
		TIMER3A_vidCallBack = ptFun;
	break;
	case TIMERS_TIMER3B:
		TIMER3B_vidCallBack = ptFun;
	break;
	case TIMERS_TIMER4A:
		TIMER4A_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER4B:
		TIMER4B_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER5A:
		TIMER5A_vidCallBack = ptFun;
		break;
	case TIMERS_TIMER5B:
		TIMER5B_vidCallBack = ptFun;
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
		while (GET_BIT(GPTM0_RIS, 0) == 0)
			;
		GPTM0_ICR |= 0x01;
	}
}

void TIMERS_vidStartPeriodic(u16 u16Value)
{
	GPTM0_CTL = 0x0;
	GPTM0_CFG = 0x00;
	GPTM0_CFG = 0x04;	/*16-bit timer*/
	GPTM0_TAMR |= 0x02; /*Periodic mode configured*/
	GPTM0_TAMR |= TIMERS_TIMA_COUNT_UP;
	GPTM0_IMR |= (1 << 0); /*Enable time-out interrupt*/
	GPTM0_ICR |= 0x01;
	GPTM0_TAILR |= u16Value;
	GPTM0_CTL |= 0x01; /*Enable timer*/
}

void TIMER0A_vidConfigInputCapt(TIMERConfig_t *TIMERConfig)
{

	CLEAR_BIT(GPTM0_CTL, 0);

	switch (TIMERConfig->u8Config)
	{
	case TIMER_CONFIG_1632_16BIT:
		GPTM0_CFG |= 0x04;
		break;
	case TIMER_CONFIG_3264_32BIT:
		GPTM0_CFG |= 0x04;
		break;
	}
	/*Timer0 A mode*/
	switch (TIMERConfig->u8TimerMode)
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
	switch (TIMERConfig->u8TimerCaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM0_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM0_TAMR, 2);
		break;
	}
	/*Count direction*/
	switch (TIMERConfig->u8TimerCountDir)
	{
	case TIMER_TIMERA_COUNTDIR_DOWN:
		CLEAR_BIT(GPTM0_TAMR, 4);
		break;
	case TIMER_TIMERA_COUNTDIR_UP:
		SET_BIT(GPTM0_TAMR, 4);
		break;
	}

	/*Event mode*/
	switch (TIMERConfig->u8TimerEventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER0->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM0_CTL, 3);
		SET_BIT(GPTM0_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM0_CTL, 3);
		SET_BIT(GPTM0_CTL, 2);
		break;
	}
}

u32 TIMER0A_u32MeasureTimerPeriod(void)
{
	int risingEdge, fallingEdge;
	/* detect first rising edge */
	TIMER0->ICR = 4; /* clear timer0A capture flag */
	while ((TIMER0->RIS & (1 << 2)) == 0)
		;					  /* wait till first positive edge captured */
	risingEdge = TIMER0->TAR; /* save the timestamp */
							  /* detect second rising edge */
	TIMER0->ICR = 4;		  /* clear timer0A capture flag */
	while ((TIMER0->RIS & (1 << 2)) == 0)
		;											/* wait till second positive edge captured*/
	fallingEdge = TIMER0->TAR;						/* save the timestamp */
	return (fallingEdge - risingEdge) & 0x00FFFFFF; /* return the time difference which is time period */
}

void TIMER0B_vidInit(TIMERConfig_t *TIMERConfig)
{
	/*Disable interrupt*/
	CLEAR_BIT(GPTM0_CTL, 8);

	/*Timer configuration*/
	TIMERS_vidSelectTimerConfig(TIMERS_TIMER_0, TIMERConfig->u8Config);

	/*Timer0 B mode*/
	switch (TIMERConfig->u8TimerMode)
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
	switch (TIMERConfig->u8TimerCaptMode)
	{
	case TIMER_TIMERB_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM0_TBMR, 2);
		break;
	case TIMER_TIMERB_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM0_TBMR, 2);
		break;
	}
	/*Count direction*/
	switch (TIMERConfig->u8TimerCountDir)
	{
	case TIMER_TIMERB_COUNTDIR_DOWN:
		CLEAR_BIT(GPTM0_TBMR, 4);
		break;
	case TIMER_TIMERB_COUNTDIR_UP:
		SET_BIT(GPTM0_TBMR, 4);
		break;
	}

	/*Event mode*/

	switch (TIMERConfig->u8TimerEventMode)
	{
	case TIMER_TIMERB_EVENTMODE_POSITIVE:
		TIMER0->CTL &= ~(1 << 10) | ~(1 << 11); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERB_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM0_CTL, 11);
		SET_BIT(GPTM0_CTL, 10);
		break;
	case TIMER_TIMERB_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM0_CTL, 10);
		SET_BIT(GPTM0_CTL, 10);
		break;
	}

	/*Interrupt mask*/
	switch (TIMERConfig->u8InterruptMask)
	{
	case TIMER_TIMERB_INTERRUPT_TIMEOUT:
		GPTM0_IMR |= (1 << 8); /*Enable time-out interrupt*/
		SET_BIT(GPTM0_ICR, 8);
		TIMERS_vidPutFunction(TIMERS_TIMER0B, TIMERConfig->ptrFunc);
		break;
	case TIMER_TIMERB_INTERRUPT_CAPTUREMODE_MATCH:
		GPTM0_IMR |= (1 << 9);
		GPTM0_ICR |= (1 << 9);
		break;
	case TIMER_TIMERB_INTERRUPT_CAPTUREMODE_EVENT:
		GPTM0_IMR |= (1 << 10);
		GPTM0_ICR |= (1 << 10);
		break;
	}

	/*Enable Timer0B*/
	SET_BIT(GPTM0_CTL, 8);
}

void TIMERS_vidSelectModeA(u8 u8TimerID, u8 u8Mode)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		switch (u8Mode)
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
		break;

	case TIMERS_TIMER_1:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM1_TAMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM1_TAMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM1_TAMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_2:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM2_TAMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM2_TAMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM2_TAMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_3:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM3_TAMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM3_TAMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM3_TAMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_4:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM4_TAMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM4_TAMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM4_TAMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_5:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM5_TAMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM5_TAMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM5_TAMR |= 0x03;
			break;
		}
		break;
	}
}

void TIMERS_vidSelectModeB(u8 u8TimerID, u8 u8Mode)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM0_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM0_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM0_TBMR |= 0x03;
			break;
		}
		break;

	case TIMERS_TIMER_1:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM1_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM1_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM1_TBMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_2:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM2_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM2_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM2_TBMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_3:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM3_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM3_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM3_TBMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_4:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM4_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM4_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM4_TBMR |= 0x03;
			break;
		}
		break;
	case TIMERS_TIMER_5:
		switch (u8Mode)
		{
		case TIMER_TIMERA_MODE_ONESHOOT:
			GPTM5_TBMR |= 0x01;
			break;
		case TIMER_TIMERA_MODE_PERIODIC:
			GPTM5_TBMR |= 0x02;
			break;
		case TIMER_TIMERA_MODE_CAPTURE:
			GPTM5_TBMR |= 0x03;
			break;
		}
		break;
	}
}


void TIMER0_vidDisable(u8 u8Timer0Sub)
{
	switch (u8Timer0Sub)
	{
	case TIMERS_TIMER0A:
		CLEAR_BIT(GPTM0_CTL, 0);
		break;
	case TIMERS_TIMER0B:
		CLEAR_BIT(GPTM0_CTL, 8);
		break;
	}
}

void TIMER0_vidStart(void)
{
	/* enable Timer0A */
	SET_BIT(GPTM0_CTL, 0);
}

void TIMERS_vidSelectCountDirectionA(u8 u8TimerID, u8 u8CountDir)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM0_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM0_TAMR, 4);
		}
		break;
	case TIMERS_TIMER_1:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM1_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM1_TAMR, 4);
		}
		break;
	case TIMERS_TIMER_2:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM2_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM2_TAMR, 4);
		}
		break;
	case TIMERS_TIMER_3:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM3_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM3_TAMR, 4);
		}
		break;
	case TIMERS_TIMER_4:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM4_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM4_TAMR, 4);
		}
		break;
	case TIMERS_TIMER_5:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM5_TAMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM5_TAMR, 4);
		}
		break;
	}
}

void TIMERS_vidSelectCountDirectionB(u8 u8TimerID, u8 u8CountDir)
{
		switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM0_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM0_TBMR, 4);
		}
		break;
	case TIMERS_TIMER_1:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM1_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM1_TBMR, 4);
		}
		break;
	case TIMERS_TIMER_2:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM2_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM2_TBMR, 4);
		}
		break;
	case TIMERS_TIMER_3:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM3_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM3_TBMR, 4);
		}
		break;
	case TIMERS_TIMER_4:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM4_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM4_TBMR, 4);
		}
		break;
	case TIMERS_TIMER_5:
		if (u8CountDir == TIMERS_COUNTDIR_UP)
		{
			SET_BIT(GPTM5_TBMR, 4);
		}
		else
		{
			CLEAR_BIT(GPTM5_TBMR, 4);
		}
		break;
	}
}

void TIMERS_vidEnableInterruptA(u8 u8Timer, u8 u8Interrupt)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			switch (u8Interrupt)
	{
	case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM0_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM0_ICR |= 0x01;
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
			break;
		case TIMERS_TIMER_1:
						switch (u8Interrupt)
	{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM1_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM1_ICR |= 0x01;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM1_IMR |= (1<<1);
					GPTM1_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM1_IMR |= (1<<2);
					GPTM1_ICR |= (1<<2);
				break;
	}
			break;
		case TIMERS_TIMER_2:
			switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM2_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM2_ICR |= 0x01;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM2_IMR |= (1<<1);
					GPTM2_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM2_IMR |= (1<<2);
					GPTM2_ICR |= (1<<2);
				break;
		}
			break;
		case TIMERS_TIMER_3:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM3_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM3_ICR |= 0x01;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM3_IMR |= (1<<1);
					GPTM3_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM3_IMR |= (1<<2);
					GPTM3_ICR |= (1<<2);
				break;
		}
			break;
		case TIMERS_TIMER_4:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM4_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM4_ICR |= 0x01;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM4_IMR |= (1<<1);
					GPTM4_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM4_IMR |= (1<<2);
					GPTM4_ICR |= (1<<2);
				break;
		}
			break;
		case TIMERS_TIMER_5:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM5_IMR |= (1<<0); /*Enable time-out interrupt*/
					GPTM5_ICR |= 0x01;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM5_IMR |= (1<<1);
					GPTM5_ICR |= (1<<1);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM5_IMR |= (1<<2);
					GPTM5_ICR |= (1<<2);
				break;
		}
			break;
	}
}

void TIMERS_vidEnableInterruptB(u8 u8Timer, u8 u8Interrupt)
{
switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			switch (u8Interrupt)
	{
	case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM0_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM0_ICR |= (1<<8);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM0_IMR |= (1<<9);
					GPTM0_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM0_IMR |= (1<<10);
					GPTM0_ICR |= (1<<10);
				break;
	}
			break;
		case TIMERS_TIMER_1:
						switch (u8Interrupt)
	{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM1_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM1_ICR |= 1<<8;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM1_IMR |= (1<<9);
					GPTM1_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM1_IMR |= (1<<10);
					GPTM1_ICR |= (1<<10);
				break;
	}
			break;
		case TIMERS_TIMER_2:
			switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM2_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM2_ICR |= (1<<8);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM2_IMR |= (1<<9);
					GPTM2_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM2_IMR |= (1<<10);
					GPTM2_ICR |= (1<<10);
				break;
		}
			break;
		case TIMERS_TIMER_3:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM3_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM3_ICR |= 1<<8;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM3_IMR |= (1<<9);
					GPTM3_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM3_IMR |= (1<<10);
					GPTM3_ICR |= (1<<10);
				break;
		}
			break;
		case TIMERS_TIMER_4:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM4_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM4_ICR |= 1<<8;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM4_IMR |= (1<<9);
					GPTM4_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM4_IMR |= (1<<10);
					GPTM4_ICR |= (1<<10);
				break;
		}
			break;
		case TIMERS_TIMER_5:
				switch(u8Interrupt)
			{
			case TIMER_TIMERA_INTERRUPT_TIMEOUT:
				  GPTM5_IMR |= (1<<8); /*Enable time-out interrupt*/
					GPTM5_ICR |= 1<<8;
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_MATCH:
					GPTM5_IMR |= (1<<9);
					GPTM5_ICR |= (1<<9);
				break;
			case TIMER_TIMERA_INTERRUPT_CAPTUREMODE_EVENT:
				GPTM5_IMR |= (1<<10);
					GPTM5_ICR |= (1<<10);
				break;
		}
			break;
	}
}

void TIMERS_vidSelectCaptModeA(u8 u8Timer, u8 u8CaptMode)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM0_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM0_TAMR, 2);
		break;
	}
			break;
		case TIMERS_TIMER_1:
					switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM1_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM1_TAMR, 2);
		break;
	}
			break;
		case TIMERS_TIMER_2:
					switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM2_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM2_TAMR, 2);
		break;
	}
			break;
		case TIMERS_TIMER_3:
					switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM3_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM3_TAMR, 2);
		break;
	}
			break;
		case TIMERS_TIMER_4:
					switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM4_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM4_TAMR, 2);
		break;
	}
			break;
		case TIMERS_TIMER_5:
					switch (u8CaptMode)
	{
	case TIMER_TIMERA_CAPTMODE_EDGECOUNT:
		CLEAR_BIT(GPTM5_TAMR, 2);
		break;
	case TIMER_TIMERA_CAPTMODE_EDGETIMER:
		SET_BIT(GPTM5_TAMR, 2);
		break;
	}
		break;
	}
}

void TIMERS_vidSetLoadValueA(u8 u8Timer, u32 u32LoadValue)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			GPTM0_TAILR = u32LoadValue;
			break;
		case TIMERS_TIMER_1:
			GPTM1_TAILR = u32LoadValue;
			break;
		case TIMERS_TIMER_2:
			GPTM2_TAILR = u32LoadValue;
			break;
		case TIMERS_TIMER_3:
			GPTM3_TAILR = u32LoadValue;
			break;
		case TIMERS_TIMER_4:
			GPTM4_TAILR = u32LoadValue;
			break;
		case TIMERS_TIMER_5:
			GPTM5_TAILR = u32LoadValue;
			break;
	}
}

void TIMERS_vidSetLoadValueB(u8 u8Timer, u32 u32LoadValue)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			GPTM0_TBILR = u32LoadValue;
			break;
		case TIMERS_TIMER_1:
			GPTM1_TBILR = u32LoadValue;
			break;
		case TIMERS_TIMER_2:
			GPTM2_TBILR = u32LoadValue;
			break;
		case TIMERS_TIMER_3:
			GPTM3_TBILR = u32LoadValue;
			break;
		case TIMERS_TIMER_4:
			GPTM4_TBILR = u32LoadValue;
			break;
		case TIMERS_TIMER_5:
			GPTM5_TBILR = u32LoadValue;
			break;
	}
}

void TIMERS_vidSelectEventModeA(u8 u8Timer, u8 u8EventMode)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER0->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM0_CTL, 3);
		SET_BIT(GPTM0_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM0_CTL, 3);
		SET_BIT(GPTM0_CTL, 2);
		break;
	}
			break;
		case TIMERS_TIMER_1:
				switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER1->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM1_CTL, 3);
		SET_BIT(GPTM1_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM1_CTL, 3);
		SET_BIT(GPTM1_CTL, 2);
		break;
	}
			break;
		case TIMERS_TIMER_2:
			switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER2->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM2_CTL, 3);
		SET_BIT(GPTM2_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM2_CTL, 3);
		SET_BIT(GPTM2_CTL, 2);
		break;
	}
			break;
		case TIMERS_TIMER_3:
			switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER3->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM3_CTL, 3);
		SET_BIT(GPTM3_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM3_CTL, 3);
		SET_BIT(GPTM3_CTL, 2);
		break;
	}
			break;
		case TIMERS_TIMER_4:
			switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER4->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM4_CTL, 3);
		SET_BIT(GPTM4_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM4_CTL, 3);
		SET_BIT(GPTM4_CTL, 2);
		break;
	}
			break;
		case TIMERS_TIMER_5:
			switch (u8EventMode)
	{
	case TIMER_TIMERA_EVENTMODE_POSITIVE:
		TIMER5->CTL &= ~(1 << 3) | ~(1 << 2); /* capture rising edges on PB6 pin */
		break;
	case TIMER_TIMERA_EVENTMODE_NEGATIVE:
		CLEAR_BIT(GPTM5_CTL, 3);
		SET_BIT(GPTM5_CTL, 2);
		break;
	case TIMER_TIMERA_EVENTMODE_BOTHEDGES:
		SET_BIT(GPTM5_CTL, 3);
		SET_BIT(GPTM5_CTL, 2);
		break;
	}
			break;
	}
}

void TIMERS_vidClearInterruptFlag(u8 u8Timer, u8 u8InterruptFlag)
{
	switch(u8Timer)
	{
		case TIMERS_TIMER_0:
			SET_BIT(GPTM0_ICR,u8InterruptFlag);
			break;
		case TIMERS_TIMER_1:
			SET_BIT(GPTM1_ICR,u8InterruptFlag);
			break;
		case TIMERS_TIMER_2:
			SET_BIT(GPTM2_ICR,u8InterruptFlag);
			break;
		case TIMERS_TIMER_3:
			SET_BIT(GPTM3_ICR,u8InterruptFlag);
			break;
		case TIMERS_TIMER_4:
			SET_BIT(GPTM4_ICR,u8InterruptFlag);
			break;
		case TIMERS_TIMER_5:
			SET_BIT(GPTM5_ICR,u8InterruptFlag);
			break;
	}

}

void TIMERS_vidSelectTimerConfig(u8 u8TimerID, u8 u8TimerConfig)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM0_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM0_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM0_CFG = 0x04;
		}
		break;
	case TIMERS_TIMER_1:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM1_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM1_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM1_CFG = 0x04;
		}
		break;
	case TIMERS_TIMER_2:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM2_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM2_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM2_CFG = 0x04;
		}
		break;
	case TIMERS_TIMER_3:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM3_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM3_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM3_CFG = 0x04;
		}
		break;
	case TIMERS_TIMER_4:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM4_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM4_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM4_CFG = 0x04;
		}
		break;
	case TIMERS_TIMER_5:
		if (u8TimerConfig == TIMER_CONFIG_1632_32BIT)
		{
			GPTM5_CFG = 0x00;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_32BIT_RTC)
		{
			GPTM5_CFG = 0x01;
		}
		else if (u8TimerConfig == TIMER_CONFIG_1632_16BIT)
		{
			GPTM5_CFG = 0x04;
		}
		break;
	}
}

void TIMERS_vidEnableTimer(u8 u8TimerID, u8 u8TimerBlock)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		if (u8TimerBlock == TIMERS_BLOCK_A)
			SET_BIT(GPTM0_CTL, 0);
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM0_CTL, 8);
		}
		break;
	case TIMERS_TIMER_1:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			SET_BIT(GPTM1_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM1_CTL, 8);
		}
		break;
	case TIMERS_TIMER_2:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			SET_BIT(GPTM2_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM2_CTL, 8);
		}
		break;
	case TIMERS_TIMER_3:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			SET_BIT(GPTM3_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM3_CTL, 8);
		}
		break;
	case TIMERS_TIMER_4:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			SET_BIT(GPTM4_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM4_CTL, 8);
		}
		break;
	case TIMERS_TIMER_5:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			SET_BIT(GPTM5_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			SET_BIT(GPTM5_CTL, 8);
		}
		break;
	}
}

void TIMERS_vidDisableTimer(u8 u8TimerID, u8 u8TimerBlock)
{
	switch (u8TimerID)
	{
	case TIMERS_TIMER_0:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM0_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM0_CTL, 8);
		}
		break;
	case TIMERS_TIMER_1:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM1_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM1_CTL, 8);
		}
		break;
	case TIMERS_TIMER_2:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM2_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM2_CTL, 8);
		}
		break;
	case TIMERS_TIMER_3:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM3_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM3_CTL, 8);
		}
		break;
	case TIMERS_TIMER_4:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM4_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM4_CTL, 8);
		}
		break;
	case TIMERS_TIMER_5:
		if (u8TimerBlock == TIMERS_BLOCK_A)
		{
			CLEAR_BIT(GPTM5_CTL, 0);
		}
		else if (u8TimerBlock == TIMERS_BLOCK_B)
		{
			CLEAR_BIT(GPTM5_CTL, 8);
		}
		break;
	}
}

/*Interrupt handler*/
void TIMER0A_Handler(void)
{
	TIMER0A_vidCallBack();
	SET_BIT(GPTM0_ICR, 0); /*To clear interrupt flag*/
}

void TIMERS_vidSetPrescalerValueA(u8 u8TimerID,u16 u16PrescalerValue)
{
switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			TIMER0->TAPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_1:
			TIMER1->TAPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_2:
			TIMER2->TAPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_3:
			TIMER3->TAPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_4:
			TIMER4->TAPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_5:
			TIMER5->TAPR = u16PrescalerValue;
			break;
	}
}

void TIMERS_vidSetPrescalerValueB(u8 u8TimerID,u16 u16PrescalerValue)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			TIMER0->TBPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_1:
			TIMER1->TBPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_2:
			TIMER2->TBPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_3:
			TIMER3->TBPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_4:
			TIMER4->TBPR = u16PrescalerValue;
			break;
		case TIMERS_TIMER_5:
			TIMER5->TBPR = u16PrescalerValue;
			break;
	}
}

void TIMERS_vidSetMatchValueA(u8 u8TimerID, u32 u32MatchValue)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			TIMER0->TAMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_1:
			TIMER1->TAMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_2:
			TIMER2->TAMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_3:
			TIMER2->TAMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_4:
			TIMER2->TAMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_5:
			TIMER2->TAMATCHR = u32MatchValue;
			break;
	}
}

void TIMERS_vidSetMatchValueB(u8 u8TimerID,u32 u32MatchValue)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			TIMER0->TBMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_1:
			TIMER1->TBMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_2:
			TIMER2->TBMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_3:
			TIMER2->TBMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_4:
			TIMER2->TBMATCHR = u32MatchValue;
			break;
		case TIMERS_TIMER_5:
			TIMER2->TBMATCHR = u32MatchValue;
			break;
	}
}

void TIMERS_vidConfigPWMA(u8 u8TimerID, u8 u8PWM)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER0->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER0->TAMR,3);
			}
			break;
		case TIMERS_TIMER_1:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER1->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER1->TAMR,3);
			}
			break;
		case TIMERS_TIMER_2:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER2->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER2->TAMR,3);
			}
			break;
		case TIMERS_TIMER_3:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER3->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER3->TAMR,3);
			}
			break;
		case TIMERS_TIMER_4:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER4->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER4->TAMR,3);
			}
			break;
		case TIMERS_TIMER_5:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER5->TAMR,3);
			}
			else
			{
				SET_BIT(TIMER5->TAMR,3);
			}
			break;
	}

}

void TIMERS_vidConfigPWMB(u8 u8TimerID, u8 u8PWM)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER0->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER0->TBMR,3);
			}
			break;
		case TIMERS_TIMER_1:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER1->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER1->TBMR,3);
			}
			break;
		case TIMERS_TIMER_2:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER2->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER2->TBMR,3);
			}
			break;
		case TIMERS_TIMER_3:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER3->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER3->TBMR,3);
			}
			break;
		case TIMERS_TIMER_4:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER4->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER4->TBMR,3);
			}
			break;
		case TIMERS_TIMER_5:
			if (u8PWM == TIMERS_PWM_DISABELD)
			{
				CLEAR_BIT(TIMER5->TBMR,3);
			}
			else
			{
				SET_BIT(TIMER5->TBMR,3);
			}
			break;
	}

}

void TIMERS_vidInvertPWMA(u8 u8TimerID, u8 u8PWMInverted)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER0->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER0->CTL,6);
			}
			break;
		case TIMERS_TIMER_1:
				if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER1->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER1->CTL,6);
			}
			break;
		case TIMERS_TIMER_2:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER2->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER2->CTL,6);
			}
			break;
		case TIMERS_TIMER_3:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER3->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER3->CTL,6);
			}
			break;
		case TIMERS_TIMER_4:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER4->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER4->CTL,6);
			}
			break;
		case TIMERS_TIMER_5:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER5->CTL,6);
			}
			else
			{
				CLEAR_BIT(TIMER5->CTL,6);
			}
			break;
	}
}

void TIMERS_vidInvertPWMB(u8 u8TimerID, u8 u8PWMInverted)
{
	switch(u8TimerID)
	{
		case TIMERS_TIMER_0:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER0->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER0->CTL,14);
			}
			break;
		case TIMERS_TIMER_1:
				if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER1->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER1->CTL,14);
			}
			break;
		case TIMERS_TIMER_2:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER2->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER2->CTL,14);
			}
			break;
		case TIMERS_TIMER_3:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER3->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER3->CTL,14);
			}
			break;
		case TIMERS_TIMER_4:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER4->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER4->CTL,14);
			}
			break;
		case TIMERS_TIMER_5:
			if (u8PWMInverted == TIMERS_PWM_INVERTED)
			{
				SET_BIT(TIMER5->CTL,14);
			}
			else
			{
				CLEAR_BIT(TIMER5->CTL,14);
			}
			break;
	}
}

void TIMER0B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER0B_vidCallBack();
	SET_BIT(GPTM0_ICR, 8);
}

void TIMER1A_Handler(void)
{
	TIMER1A_vidCallBack();
	SET_BIT(GPTM1_ICR, 0);
}

void TIMER1B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER1B_vidCallBack();
	SET_BIT(GPTM1_ICR, 8);
}

void TIMER2A_Handler(void)
{
	TIMER2A_vidCallBack();
	SET_BIT(GPTM2_ICR, 0);
}

void TIMER2B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER2B_vidCallBack();
	SET_BIT(GPTM2_ICR, 8);
}

void TIMER3A_Handler(void)
{
	TIMER3A_vidCallBack();
	SET_BIT(GPTM3_ICR, 0);
}

void TIMER3B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER3B_vidCallBack();
	SET_BIT(GPTM3_ICR, 8);
}

void TIMER4A_Handler(void)
{
	TIMER4A_vidCallBack();
	SET_BIT(GPTM4_ICR, 0);
}

void TIMER4B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER4B_vidCallBack();
	SET_BIT(GPTM4_ICR, 8);
}

void TIMER5A_Handler(void)
{
	TIMER5A_vidCallBack();
	SET_BIT(GPTM5_ICR, 0);
}

void TIMER5B_Handler(void)
{
	/*Clear interrupt flag*/
	TIMER5B_vidCallBack();
	SET_BIT(GPTM5_ICR, 8);
}