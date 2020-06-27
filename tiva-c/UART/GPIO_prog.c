/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: GPIO driver for Tiva-C
 * Date: 16-10-2018
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_private.h"
#include "SYSCNTRL_private.h"
#include "GPIO_interface.h"

void GPIO_vidSetPinDirection(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8DirectionCpy) {

	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOA_DIR,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOB_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DIR,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOC_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOD_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DIR,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8DirectionCpy == GPIO_OUTPUT) {
				SET_BIT(GPIOF_DIR,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DIR,u8PinNumCpy);
			}
			break;
	}

}


void GPIO_vidSetPinValue(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8Value) {
	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOA_DATA,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOB_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DATA,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOC_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOD_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DATA,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8Value == STD_HIGH) {
				SET_BIT(GPIOF_DATA,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DATA,u8PinNumCpy);
			}
			break;
	}
}

void GPIO_vidSetPinDigEnable(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8DigEnable) {
	switch (u8PortNumCpy) {
		case GPIO_PORTA:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOA_DEN,u8PinNumCpy);	
			}
			else {
				CLEAR_BIT(GPIOA_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTB:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOB_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOB_DEN,u8PinNumCpy);	
			}
			break;
		case GPIO_PORTC:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOC_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTD:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOD_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOD_DEN,u8PinNumCpy);
			}
			break;
		case GPIO_PORTF:
			if (u8DigEnable == GPIO_DEN_SET) {
				SET_BIT(GPIOF_DEN,u8PinNumCpy);
			}
			else {
				CLEAR_BIT(GPIOF_DEN,u8PinNumCpy);
			}
			break;
			
	}
}

