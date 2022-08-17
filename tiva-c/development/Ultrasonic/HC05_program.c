#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TIMER1_interface.h"
#include "HC05_interface.h"
#include "TM4C123.h"                    // Device header


void HC05_vidInit(void)
{

}

/* This function captures consecutive rising and falling edges of a periodic signal */
/* from Timer Block 0 Timer A and returns the time difference (the period of the signal). */
u32 HC05_u32GetDistance(void)
{

	int lastEdge, thisEdge;
	
	/* Given 10us trigger pulse */
	/* make trigger  pin Low */
	GPIO_vidSetPinValue(GPIO_PORTA,GPIO_PIN5,STD_LOW);
	TIMER1_vidDelayMicro(2);
	GPIO_vidSetPinValue(GPIO_PORTA,GPIO_PIN5,STD_HIGH);
	TIMER1_vidDelayMicro(10); /*10 seconds delay */
	GPIO_vidSetPinValue(GPIO_PORTA,GPIO_PIN5,STD_LOW);

 	while(1)
	{
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & 4) == 0) ;    /* wait till captured */
	  if(GPIOB->DATA & (1<<6)) /*check if rising edge occurs */
		{
    lastEdge = TIMER0->TAR;     /* save the timestamp */
		/* detect falling edge */
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & 4) == 0) ;    /* wait till captured */
    thisEdge = TIMER0->TAR;     /* save the timestamp */
		return (thisEdge - lastEdge); /* return the time difference */
		}
	}
}