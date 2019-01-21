/*
* A program that uses SysTick as a timer to toggle blue LED
	on Tiva C 
*
*/

#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

#define LED_ON (1U<<5)


#define RCGCGPIO *((unsigned int *) 0x400FE608)



int main(void) {
	RCGCGPIO |= (1U<<5);
	u32 flag = 0;
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	SysTick_vidInit(SYSTICK_SYSTEM_CLOCK,SYSTICK_NO_INTERRUPT);
	SysTick_vidSetValue(800000);
	SysTick_vidStart();
	
	while(1) {	
		if(SysTick_u32GetCurrentValue() == 1) {
			if (flag == 1) {
					GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_HIGH);
					flag = 0;
			}
			else {
					GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);
					flag = 1;

			}
		}
	}
}