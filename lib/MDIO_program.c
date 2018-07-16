#include "Std_Types.h"
#include "Macros.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"

void MDIO_vidInit(void) {
	
}

void MDIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8PinValue) {
	if (u8PortNum == DIO_PORTA) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOB_ODR,u8PinNum);		
		}
		else {
			CLEAR_BIT(GPIOB_ODR,u8PinNum);	
		}
	}
	else if (u8PortNum == DIO_PORTB) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOB_ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOB_ODR,u8PinNum);:
		}
	}
	else if (u8PortNum == DIO_PORTC) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOC_ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOC_ODR,u8PinNum);
		}
	}
}
/*
u8 MDIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum) {
	if (u8PortNum == DIO_PORTA) {
	
	}
	else if(u8PortNum == DIO_PORTB) {
	
	}
	else if(u8PortNum == DIO_PORTC) {
		
	}
}*/
