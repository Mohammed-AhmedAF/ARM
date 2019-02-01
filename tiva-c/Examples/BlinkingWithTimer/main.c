/*
* A program that uses SysTick as a timer to toggle blue LED
    on Tiva C
*
*/

#include "Std_Types.h"
#include "GPIO_interface.h"
#include "TIMERS_interface.h"

#define LED_ON (1U<<5)


#define RCGCGPIO * ((unsigned int *) 0x400FE608)
#define RCGCTIMER * ((unsigned int *) 0x400FE604)



int main(void) {
    RCGCGPIO |= (1U<<5); /*Enable clock for Port F*/
    RCGCTIMER |= (1U<<0); /*Enable clock for timer0*/

    GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
    GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);

    while(1) {

          GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
          TIMERS_vidStartOneShoot(160);
          GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
          TIMERS_vidStartOneShoot(160);

    }
}
