#include <stdint.h>
#include <stdio.h>
#include "BIT_MATH.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"

/*Pointer to callback functions*/
static void (*ptrF_Timer2) (void);
static void (*ptrF_Timer3) (void);
static void (*ptrF_Timer4) (void);
static void (*ptrF_Timer5) (void);
static void (*ptrF_Timer6) (void);
static void (*ptrF_Timer7) (void);

/*Function used to initialize timers*/
void TIMERS_vidInit(TIMERConfig_t * TIMERConfig)
{
	/*Disable timer*/
	TIMERS_vidDisableTimer(TIMERConfig->u8TimerID);

	/*Reload value*/
	TIMERS_vidSetReloadValue(TIMERConfig->u8TimerID, TIMERConfig->u16ReloadValue);

	/*Interrupt*/
	SET_BIT(TIM2->DIER,0);
	TIMERS_vidPutISRFunction(TIMERConfig->u8TimerID,TIMERConfig->ptrFCalback);
	TIMERS_vidEnableInterrupt(TIMERConfig->u8TimerID,TIMERConfig->u8Interrupt);

	/*Enable timer*/
	TIMERS_vidEnableTimer(TIMERConfig->u8TimerID);
}

void TIMERS_vidEnableTimer(uint8_t u8TimerID)
{
	switch(u8TimerID)
	{
	case TIMERS_TIMER_2:
		SET_BIT(TIM2->CR1,0);
		break;
	case TIMERS_TIMER_3:
		SET_BIT(TIM3->CR1,0);
		break;
	case TIMERS_TIMER_4:
		SET_BIT(TIM4->CR1,0);
		break;
	case TIMERS_TIMER_5:
		SET_BIT(TIM5->CR1,0);
		break;
	}
}

void TIMERS_vidDisableTimer(uint8_t u8TimerID)
{
	switch(u8TimerID)
	{
	case TIMERS_TIMER_2:
		CLR_BIT(TIM2->CR1,0);
		break;
	case TIMERS_TIMER_3:
		CLR_BIT(TIM3->CR1,0);
		break;
	case TIMERS_TIMER_4:
		CLR_BIT(TIM4->CR1,0);
		break;
	case TIMERS_TIMER_5:
		CLR_BIT(TIM5->CR1,0);
		break;
	}
}

void TIMERS_vidSetReloadValue(uint8_t u8TimerID, uint16_t u16Value)
{
	switch(u8TimerID)
	{
	case TIMERS_TIMER_2:
		TIM2->ARR = u16Value;
		break;
	case TIMERS_TIMER_3:
		TIM3->ARR = u16Value;
		break;
	case TIMERS_TIMER_4:
		TIM4->ARR = u16Value;
		break;
	case TIMERS_TIMER_5:
		TIM5->ARR = u16Value;
		break;
	}
}


void TIMERS_vidPutISRFunction(uint8_t u8TimerID, void (*ptrF) (void))
{
	switch(u8TimerID)
	{
	case TIMERS_TIMER_2:
		ptrF_Timer2 = ptrF;
	break;
	case TIMERS_TIMER_3:
		ptrF_Timer3 = ptrF;
		break;
	case TIMERS_TIMER_4:
		ptrF_Timer4 = ptrF;
	break;
	case TIMERS_TIMER_5:
		ptrF_Timer5 = ptrF;
	break;
	}
}

void TIMERS_vidEnableInterrupt(uint8_t u8TimerID, uint8_t u8Interrupt)
{
	switch(u8TimerID)
	{
	case TIMERS_TIMER_2:
		TIM2->DIER |= (1<<u8Interrupt);
	break;
	case TIMERS_TIMER_3:
		TIM3->DIER |= (1<<u8Interrupt);
	break;
	case TIMERS_TIMER_4:
		TIM4->DIER |= (1<<u8Interrupt);
	break;
	case TIMERS_TIMER_5:
		TIM5->DIER |= (1<<u8Interrupt);
	break;
	}
}

void TIM2_IRQHandler(void)
{
	ptrF_Timer2();

}

void TIM3_IRQHandler(void)
{
	ptrF_Timer3();
}

void TIM4_IRQHandler(void)
{
	ptrF_Timer4();
}

void TIM5_IRQHandler(void)
{
	ptrF_Timer5();
}

void TIM6_IRQHandler(void)
{
	ptrF_Timer6();
}

void TIM7_IRQHandler(void)
{
	ptrF_Timer7();
}
