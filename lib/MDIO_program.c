#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MRCC_private.h"
#include "MRCC_interface.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"

void MDIO_vidInit(void) {
	MRCC->APB2ENR |= 4;
	GPIOA->CRL= 0x33;
}

void MDIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8PinValue) {
	if (u8PortNum == MDIO_PORTA) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOA->ODR,u8PinNum);		
		}
		else {
			CLEAR_BIT(GPIOA->ODR,u8PinNum);	
		}
	}
	else if (u8PortNum == MDIO_PORTB) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOB->ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOB->ODR,u8PinNum);
		}
	}
	else if (u8PortNum == MDIO_PORTC) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOC->ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOC->ODR,u8PinNum);
		}
	}
}

u8 MDIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum) {
	if (u8PortNum == MDIO_PORTA) {
		return (u8)  GET_BIT(GPIOA->IDR,u8PinNum);
	}
	else if(u8PortNum == MDIO_PORTB) {
		return (u8) GET_BIT(GPIOB->IDR,u8PinNum);	
	}
	else if(u8PortNum == MDIO_PORTC) {
		return (u8) GET_BIT(GPIOC->IDR,u8PinNum);
	}
	return 0;
}
