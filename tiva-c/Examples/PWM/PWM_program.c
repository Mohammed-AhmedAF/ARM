/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: PWM driver for Tiva-C tm4c123gh6pm
 *
 *
 */

#include "Macros.h"
#include "STD_TYPES.h"
#include "PWM_private.h"
#include "PWM_interface.h"

void PWM_vidStart(void) {
	/*Disabling PWM*/
	PWM_M0_MCTL = 0x00;
	/*PWM Action*/
	PWM_M0_GENA0 = 0x0000008C; /*Drive low on count=0 and count=LOAD*/
	PWM_M0_GENB0 = 0x0000080C;

	/*Setting load, defining the period*/
	PWM_M0_LOAD0 = 0x0000018F; /*399 in decimal*/
	/*Duty cycle*/
	PWM_M0_CMPA0 = 0x0000012B; 

	/*Start PWM generator*/
	SET_BIT(PWM_M0_0CTL,1);

	/*Enable PWM Output*/
	SET_BIT(PWM_M0_ENABLE,0);
	SET_BIT(PWM_M0_ENABLE,1);

}
