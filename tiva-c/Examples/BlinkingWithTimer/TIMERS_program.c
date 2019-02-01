/*
 * Timer driver for Tiva C
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"


/*A function that activates the timer on one-shoot mode*/
void TIMERS_vidStartOneShoot(u8 times) {
    u8 i = 0;
    for (i = 0; i < times; i++) {

        GPTM0_CTL = 0x0;
                GPTM0_CFG = 0x00;
                GPTM0_CFG = 0x04;
                GPTM0_TAMR |= 0x01;
                GPTM0_TAMR |= TIMERS_TIMA_COUNT_UP;
                GPTM0_ICR |= 0x01;
                GPTM0_TAILR |= 65000;
                GPTM0_ICR |= 0x01;
                GPTM0_CTL |= 0x01;
        while(GET_BIT(GPTM0_RIS,0) == 0);
        GPTM0_ICR |= 0x01;
        /*
        TIMER0_CTL_R = 0x0;
        TIMER0_CFG_R = 0x00;
        TIMER0_CFG_R = 0x04;
        TIMER0_TAMR_R |= 0x01;
        TIMER0_TAMR_R |= TIMERS_TIMA_COUNT_UP;
        TIMER0_ICR_R |= 0x01;
        TIMER0_TAILR_R |= 65000;
        TIMER0_ICR_R |= 0x01;
        TIMER0_CTL_R |= 0x01;
        while(GET_BIT(TIMER0_RIS_R,0) == 0);
        TIMER0_ICR_R |= 0x01;
        TIMER0_ICR_R |= 0x00;
        */
    }
    }

