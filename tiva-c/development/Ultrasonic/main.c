/* This example code Measures the distance using HC-SR04 Ultrasonic range sensor*/
/* It displays the measured distance value on computer using UART communication moduel of TM4C123 */
/* Timer0A is used to measure distance by measuring pulse duration of Echo output signal */
/* Timer1A is used to make percise microsecond delay function */

/*header files for TM4C123 device and sprintf library */
#include "TM4C123GH6PM.h"
#include <stdio.h>
#include "Macros.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "TIMER1_interface.h"
#include "HC05_interface.h"

/*Function prototype for Timer0A and UART module initialization */
void Timer0ACapture_init(void);
void Delay_MicroSecond(int time);
void UART5_init(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void Delay(unsigned long counter);

/* global variables to store and display distance in cm */
uint32_t time; /*stores pulse on time */
uint32_t distance; /* stores measured distance value */
char mesg[20];  /* string format of distance value */

/* main code to take distance measurement and send data to UART terminal */
int main(void)
{
	SCB->CPACR |= 0x00F00000;
	SYSCTL->RCGCTIMER |= 2;     /* enable clock to Timer Block 1 */

	Timer0ACapture_init();  /*initialize Timer0A in edge edge time */
	UART5_init(); /* initialize UART5 module to transmit data to computer */
	
	while(1)
	{
		time = HC05_u32GetDistance(); /* take pulse duration measurement */ 
		distance = (time * 10625)/10000000; /* convert pulse duration into distance */
		sprintf(mesg, "\r\nDistance = %d cm", distance); /*convert float type distance data into string */
		printstring(mesg); /*transmit data to computer */
		Delay(2000);
	}
	
}

/* Timer0A initialization function */
/* Initialize Timer0A in input-edge time mode with up-count mode */
void Timer0ACapture_init(void)
{
    SYSCTL->RCGCTIMER |= 1;     /* enable clock to Timer Block 0 */
    SYSCTL->RCGCGPIO |= 2;      /* enable clock to PORTB */
    
    GPIOB->DIR &= ~0x40;        /* make PB6 an input pin */
    GPIOB->DEN |= 0x40;         /* make PB6 as digital pin */
    GPIOB->AFSEL |= 0x40;       /* use PB6 alternate function */
    GPIOB->PCTL &= ~0x0F000000;  /* configure PB6 for T0CCP0 */
    GPIOB->PCTL |= 0x07000000;
    
	  /* PB2 as a digital output signal to provide trigger signal */
	  SYSCTL->RCGCGPIO |= 1;      /* enable clock to PORTA */
	  GPIOA->DIR |=(1<<5);         /* set PB2 as a digial output pin */
	  GPIOA->DEN |=(1<<5);         /* make PB2 as digital pin */

    TIMER0->CTL &= ~1;          /* disable timer0A during setup */
    TIMER0->CFG = 4;            /* 16-bit timer mode */
    TIMER0->TAMR = 0x17;        /* up-count, edge-time, capture mode */
    TIMER0->CTL |=0x0C;        /* capture the rising edge */
    TIMER0->CTL |= (1<<0);           /* enable timer0A */
}

void UART5_init(void)
{
	  SYSCTL->RCGCUART |= 0x20;  /* enable clock to UART5 */
    SYSCTL->RCGCGPIO |= 0x10;  /* enable clock to PORTE for PE4/Rx and RE5/Tx */
    /* UART0 initialization */
    UART5->CTL = 0;         /* UART5 module disbable */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          /*select system clock*/
    UART5->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x30;      /* set PE4 and PE5 as digital */
    GPIOE->AFSEL = 0x30;    /* Use PE4,PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analg function*/
    GPIOE->PCTL = 0x00110000;     /* configure PE4 and PE5 for UART */
}
void UART5_Transmitter(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

void printstring(char *str)
{
  while(*str)
	{
		UART5_Transmitter(*(str++));
	}
}
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter*1000; i++);
}