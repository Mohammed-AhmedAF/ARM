#include "TM4C123.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include <stdint.h>
#include <stdlib.h>
#include "SysTick_interface.h"
void Delay(unsigned long counter);
char UART0_Receiver(void);
void UART0_Transmitter(unsigned char data);
void printstring(char *str);
void doInSysTick(void);
void initSwitches(void);

volatile u8 u8Flag = 0;

int main(void)
{
	  SYSCTL->RCGCUART |= 0x01;  /* enable clock to UART0 */
    SYSCTL->RCGCGPIO |= 0x01;  /* enable clock to PORTA for PA0/Rx and RA0/Tx */
		SYSCTL->RCGCGPIO |= 0x20; /* enable clock for PORTF*/
    Delay(1);
    /* UART0 initialization */
    UART0->CTL = 0;         /* UART5 module disbable */
    UART0->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART0->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART0->CC = 0;          /*select system clock*/
		UART0->DR &= 0;
    UART0->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
    UART0->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */
		UART0->IM |= 0x0010;
    /* UART0 TX0 and RX0 use PA0 and PA0. Configure them digital and enable alternate function */
    GPIOA->DEN |= 0x03;      /* set PE4 and PE5 as digital */
    GPIOA->AFSEL |= 0x03;    /* Use PE4,PE5 alternate function */
    GPIOA->AMSEL = 0;    /* Turn off analg function*/
    GPIOA->PCTL |= 0x11;     /* configure PE4 and PE5 for UART */
	
		GPIOF->DIR |= (1<<3);
		GPIOF->DEN |= (1<<3);
		GPIOF->DATA |= (1<<3);
	
		SysTick_vidInit(SYSTICK_SYSTEM_CLOCK,SYSTICK_INTERRUPT_ENABLED);
		SysTick_vidSetValue(40000000);
		SysTick_vidPutISR(doInSysTick);
		SysTick_vidStart();
		
		initSwitches();
		
	NVIC->IP[5] = 3 << 5;
	NVIC->ISER[0] |= 0x00000020;
	
	NVIC->IP[30] = 2 << 5;     /* set interrupt priority to 3 */
  NVIC->ISER[0] |= (1<<30);  /* enable IRQ30 (D30 of ISER[0]) */
	
	/*Enabling general interrupt*/
	__enable_irq();
	
	while(1)
	{
		char c = UART0_Receiver();          /* get a character from UART5 */
		UART0_Transmitter(c); 
		printstring("\r\nHello world\r\n");
	}
}

char UART0_Receiver(void)  
{
    char data;
	  while((UART0->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = (char) UART0->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

void UART0_Transmitter(unsigned char data)  
{
    while((UART0->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART0->DR = data;                  /* before giving it another byte */
}

void printstring(char *str)
{
  while(*str)
	{
		UART0_Transmitter(*(str++));
	}
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}

void UART0_Handler()
{
	UART0_Transmitter('s');
	UART0->ICR = 0x0010;
}


void doInSysTick()
{
	static u8 u8Flag;
	if (u8Flag == 1){
		u8Flag = 0;
	}
	else {
		u8Flag = 1;
	}
	GPIOF->DATA ^= (1<<3);
}

/*External Interrupt handler*/
void GPIOF_Handler()
{
	if (GPIOF->MIS & 0x10) /* check if interrupt causes by PF4/SW1*/
    {   
				if (u8Flag == 0) {
					printstring("S&0001A");
					u8Flag = 1;
				}
				else {
					printstring("S&0001N");
					u8Flag = 0;
				}
				GPIOF->ICR |= 0x10; /* clear the interrupt flag */
     } 
    else if (GPIOF->MIS & 0x01) /* check if interrupt causes by PF0/SW2 */
    {   
				if (u8Flag == 0) {
					printstring("S&0000A&0001A");
					u8Flag = 1;
				}
				else {
					printstring("S&0000N&0000A");
					u8Flag = 0;
				}
				GPIOF->ICR |= 0x01; /* clear the interrupt flag */
    }
}

void initSwitches(void){
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR |= 0x01;
	GPIOF->LOCK = 0;
	
	/*F0,F4 digital pins*/
	GPIOF->DEN |= 0x11;
	/*F0,F4 are input pins*/
	GPIOF->DIR &= ~(1<<0) | ~(1<<4);
	/*Enabling pull-up*/
	GPIOF->PUR |= 0x11;
	
	GPIOF->IS &= 0x00;
	/*Interrupt generation is controlled by IEV*/
	GPIOF->IBE &= ~(1<<4)|~(1<<0);
	/*Interrupt on falling edge*/
	GPIOF->IEV &= ~(1<<3)|~(1<<0);
	/*Interrupt enable mask*/
	
	GPIOF->ICR &= ~(1<<4)|~(1<<0);
	GPIOF->IM |= 0x11;
	
}
