/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Example for the use of PWM
 * in Tiva-C tm4c123gh6pm
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "RCC_private.h"
#include "GPIO_interface.h"
#include "PWM_interface.h"

void main(void) {
	/*Clock to PWM module0*/
	RCGC0 |= (1<<20);
	/*Clock to GPIO PortB*/
	RCGC2 |= (1<<1);
	/*Selecting alternate function*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN6);
	/*Selecting peripheral connected to pin*/
	GPIOB_PCTL |= (GPIO_PERIPHERAL_PWM<<6*4);
	/*Selecting clock divider for PWM*/
	RCC |= (1<<20);
	/*Dividing the clock by 2*/
	CLEAR_BIT(RCC,17);
	CLEAR_BIT(RCC,18);
	CLEAR_BIT(RCC,19);

	PWM_vidStart();	
	/*Initialization*/
	while(1) {
	
	};
}
