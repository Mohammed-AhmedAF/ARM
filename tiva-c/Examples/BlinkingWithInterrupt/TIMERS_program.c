/*
 * Timer driver for Tiva C
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"

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
        while (GET_BIT(GPTM0_RIS,0) == 0);            ;
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

