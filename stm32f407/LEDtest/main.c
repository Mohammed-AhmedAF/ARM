/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Testing first program on STM32F407
 *
 */

#include "RCC_private.h"
#include "GPIO_private.h"

void main(void) {
	/*HSI enable*/
	RCC_CR |= (1<<0);
	/*Selecting HSI (internal clock)*/
	RCC_CFGR |= (0<<21);
	RCC_CFGR |= (0<<22);
	/*Setting running clock for port B*/
	RCC_AHB1ENR |= (1<<1);

	/*Initial configuration for port B pin4 */
	GPIO_PORTB->OTYPER |= (0<<4); /*Push-pull*/
	/*Setting mode register for port B pin4*/
	GPIO_PORTB->MODER |= (1<<8);
	GPIO_PORTB->MODER |= (0<<9);
	/*Setting value  for data register*/
	GPIO_PORTB->ODR |= (1<<4);
	while(1);
}
