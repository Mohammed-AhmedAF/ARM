#include "TM4C123.h"                    // Device header

void initSystem(void);
void initTimer0(void);

volatile int count = 0;

int main(void)
{
	initSystem();
	initTimer0();
	
	while(1)
	{
	}
}

void initSystem(void)
{
	/*Clock to Port F*/
	SYSCTL->RCGCGPIO |= 0x20;
	
	GPIOF->DIR |= (1<<2);
	GPIOF->DEN |= (1<<2);
	/*Clock to timer0*/
	SYSCTL->RCGCTIMER |= 0x01;
}

void initTimer0(void)
{
	TIMER0->CFG = 0x04;
	/*Periodic mode*/
	TIMER0->TAMR = 0x2;
	
	/*Timer load*/
	TIMER0->TAILR = 10000;
	
	/*Clearing timer flag*/
	TIMER0->ICR = 0x01;
	
	/*Interrupt mask*/
	TIMER0->IMR = 0x01;
	
	TIMER0->CTL = 0x01;
	
	__disable_irq();
	
	NVIC->IP[19] = 4 << 5;
	NVIC->ISER[0] |= (1<<19);
	
	__enable_irq();
}

/*Name of handler and IRQ number is in startup.c*/
void TIMER0A_Handler(void)
{
	count++;
	int readback;
	TIMER0->ICR = 0x01;
	if(count == 1000)
	{
		GPIOF->DATA ^= (1<<2);
		count = 0;

	}
	/*Read to force clearing*/
	readback = TIMER0->ICR;
}