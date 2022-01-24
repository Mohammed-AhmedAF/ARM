#include "Macros.h"
#include "STD_TYPES.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "TM4C123.h"                    // Device header

void (*ptrFCallback) (void);

void TIMER0_vidInit(void)
{
	/*Enabling clock access to timer*/
	SET_BIT(SYSCTL->RCGCTIMER,0); 

	/*Timer configuration (16-bit)*/
	SET_BIT(TIM0_CFG,2);
	
	/**Timer mode**/
	/*Periodic*/
	SET_BIT(TIM0_TAMR,1);
	/*Count direction: down*/
	CLEAR_BIT(TIM0_TAMR,4);
	
	/*Prescaler (250)*/
	TIM0_TAPR = 250-1;
	
	/*Load value*/
	TIM0_TAILR = 64-1;
	
	/*Interrupt on timer-out*/
	SET_BIT(TIM0_IMR,0);
	
	/*Enable timer*/
	SET_BIT(TIM0_CTL,0);
	
	/*Enabling interrupt of timer0A in NVIC*/
	SET_BIT(NVIC->ISER[0],19);
}

void TIMER0_vidPutISRFunction(void (*ptrF) (void))
{
	ptrFCallback = ptrF;
}

void TIMER0A_Handler()
{
	ptrFCallback();
	SET_BIT(TIM0_ICR,0);
}