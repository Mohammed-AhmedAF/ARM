#include "TM4C123.h"

int main()
{
	/*Port F*/
	SYSCTL->RCGCGPIO |= 0x20;

	/*Setting all GPIOs as outputs*/
	GPIOF->DIR |= 0x0E;
	
	/*All pins are digital pins*/
	GPIOF->DEN |= 0x0E;
	
	/*Systick configuration*/
	__disable_irq();
	
	SysTick->LOAD = 16000000-1;
	
	/*Enable systick, use interrupt, and system clock*/
	SysTick->CTRL = 7;
	
	__enable_irq();
		
	
	while(1);
}

void SysTick_Handler()
{
	GPIOF->DATA ^= 0x02;
}