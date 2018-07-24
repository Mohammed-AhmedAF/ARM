#include "LSTD_TYPES.h"
#include "Macros.h"
#include "MRCC_private.h"
#include "MRCC_interface.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"

void MDIO_vidInit(void) {
	MRCC->APB2ENR |= 4;
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

void MDIO_vidSetPinConfiguration(u8 u8PortNum, u8 u8PinNumCpy, u8 u8ConfCpy) {
	if (u8PinNumCpy < MDIO_PIN8){
		switch (u8ConfCpy) {
			case MDIO_GPOUT_PP:
				if (u8PortNum == MDIO_PORTA) {
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*2+3);	
				}
				else if (u8PortNum == MDIO_PORTB) {
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_GPOUT_OD:
				if (u8PortNum == MDIO_PORTA) {
					SET_BIT(GPIOA->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					SET_BIT(GPIOB->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum ==  MDIO_PORTC) {
					SET_BIT(GPIOC->CRL,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_AFOUT_PP:
				if (u8PortNum == MDIO_PORTA) {
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOA->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOB->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOC->CRL,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_AFOUT_OD:
				if (u8PortNum ==  MDIO_PORTA) {
					SET_BIT(GPIOA->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOA->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					SET_BIT(GPIOB->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOB->CRL,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					SET_BIT(GPIOC->CRL,u8PinNumCpy*2+2);
					SET_BIT(GPIOC->CRL,u8PinNumCpy*2+3);
				}
				break;
		}
	}
	else {
		switch (u8ConfCpy) {
			case MDIO_GPOUT_PP:
				if (u8PortNum == MDIO_PORTA) {
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*2+3);	
				}
				else if (u8PortNum == MDIO_PORTB) {
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_GPOUT_OD:
				if (u8PortNum == MDIO_PORTA) {
					SET_BIT(GPIOA->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					SET_BIT(GPIOB->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum ==  MDIO_PORTC) {
					SET_BIT(GPIOC->CRH,u8PinNumCpy*2+2);
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_AFOUT_PP:
				if (u8PortNum == MDIO_PORTA) {
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOA->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOB->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOC->CRH,u8PinNumCpy*2+3);
				}
				break;
			case MDIO_AFOUT_OD:
				if (u8PortNum ==  MDIO_PORTA) {
					SET_BIT(GPIOA->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOA->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTB) {
					SET_BIT(GPIOB->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOB->CRH,u8PinNumCpy*2+3);
				}
				else if (u8PortNum == MDIO_PORTC) {
					SET_BIT(GPIOC->CRH,u8PinNumCpy*2+2);
					SET_BIT(GPIOC->CRH,u8PinNumCpy*2+3);
				}
				break;
		}
	}
}

void MDIO_vidSetPinMode(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8ModeCpy) {
	if (u8ModeCpy == MDIO_OUTSPEED_10) {
		if (u8PortNumCpy == MDIO_PORTA) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOA->CRH,u8PinNumCpy*2);
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == MDIO_PORTB) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if (u8PortNumCpy == MDIO_PORTC) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
	else if (u8ModeCpy  == MDIO_OUTSPEED_2) {
		if (u8PortNumCpy ==  MDIO_PORTA) {
			if (u8PinNumCpy < MDIO_PIN8) {
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == MDIO_PORTB) {
			if (u8PinNumCpy < MDIO_PIN8) {
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == MDIO_PORTC) {
			if (u8PinNumCpy < MDIO_PIN8) {
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
	else if (u8ModeCpy == MDIO_OUTSPEED_50) {
		if (u8PortNumCpy == MDIO_PORTA) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if	(u8PortNumCpy == MDIO_PORTB) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if (u8PortNumCpy == MDIO_PORTC) {
			if (u8PinNumCpy < MDIO_PIN8) {
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
}
