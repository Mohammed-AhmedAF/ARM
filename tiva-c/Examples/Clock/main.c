/*
* Author: Mohamed Ahmed Abd Al-Fattah
* Purpose: Clock project using LCD on ARM-based Tiva-C 
* tm4c123gh6pm
*
*/

#include "Std_Types.h"
#include "RCC_private.h"
#include "GPIO_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "NVIC_private.h"
#include "LCD_interface.h"
#include "CLOCK_interface.h"

void vidBlink(void);


volatile u32 u32OVFCount = 0;
volatile u8 u8flag = 0;
int main(void) {
    RCGCGPIO |= (1U<<5); /*Enable clock for Port F*/
    RCGCTIMER |= (1U<<0); /*Enable clock for timer0*/

		RCGCGPIO |= (1U<<0); /*Enable clock for Port A*/
		RCGCGPIO |= (1U<<1); /*Enable clock for Port B*/
	
		
		LCD_vidInit();
    /**/
    GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
    GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
    TIMERS_vidStartPeriodic(65535);
		TIMERS_vidPutFunction(CLOCK_vidCount);
    /*NVIC Enable Timer0A Interrupt*/
    NVIC_EN0_R = (1<<19);
		NVIC_PRI4_R |= (3<<29);
	
    while(1);
}


void vidBlink(void) {
	u32OVFCount++;
	if(u32OVFCount == 500) {
		if(u8flag == 1) {
			u8flag = 0;
			GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_HIGH);
		}
		else {
			u8flag = 1;
			GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN3,STD_LOW);
		}
		u32OVFCount = 0;
		
	}
}