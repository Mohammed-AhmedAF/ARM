//
// Author: Mohammed Ahmed Abd Al-Fattah
// Project: First Tiva-c, from udemy course
//
//


#include "TM4C123.h"                    // Device header

#define GREEN (1U<<3) //Green LED is connected to PIN3 

void delay(int time); //A delay function

int main(void) {
	SYSCTL->RCGCGPIO |= (1U<<5); //Connecting the clock to PORTF
	//The LED is connected to that port.
	GPIOF->DIR |=GREEN;
	GPIOF->DEN |=GREEN;
	GPIOF->DATA |=GREEN;

	while(1) {
		delay(1000000);
		GPIOF->DATA ^= GREEN;
		delay(2000000);
	}
	return 0;
}

void delay(int time) {
	int delay = 0;
	while (delay < time) {
		delay++;
	}
}
