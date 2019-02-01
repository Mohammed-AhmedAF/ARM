/*
* A program that uses timer and interrupt to toggle blue LED
    on Tiva C.
*
*/

#include "Std_Types.h"
#include "GPIO_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "tm4c123gh6pm.h"


#define RCGCGPIO * ((unsigned int *) 0x400FE608)
#define RCGCTIMER * ((unsigned int *) 0x400FE604)

volatile u32 u32OVFCount = 0;
volatile u8 u8flag = 0;
int main(void) {
    RCGCGPIO |= (1U<<5); /*Enable clock for Port F*/
    RCGCTIMER |= (1U<<0); /*Enable clock for timer0*/

    /**/
    GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
    GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
    TIMERS_vidStartPeriodic(60000);
    /*NVIC Enable Timer0A Interrupt*/
    NVIC_EN0_R = (1<<19);
		NVIC_PRI4_R |= (3<<29); 
    while(1);
}

void TIMER0A_Handler(void) {

    u32OVFCount++;
    if (u32OVFCount == 160) {
        if (u8flag == 0) {
            GPIO_vidSetPinValue(GPIO_PORTF, GPIO_PIN3, STD_HIGH);
            u8flag = 1;
        }else {
            GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
            u8flag = 0;
        }
        u32OVFCount = 0;
    }
    GPTM0_ICR = 0x01; /*To clear interrupt flag*/

}

