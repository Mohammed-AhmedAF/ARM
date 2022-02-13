/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Purpose: DIO driver for STM32F103 MCU
 *
 */

#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_private.h"
#include "RCC_private.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"

void GPIO_vidInit(void) {
	RCC_APB2ENR |= 12;
	GPIOA->CRL= 0x33;

}

void GPIO_vidSetPinValue(u8 u8PortNum, u8 u8PinNum, u8 u8PinValue) {
	if (u8PortNum == GPIO_PORTA) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOA->ODR,u8PinNum);
		}
		else {
			CLEAR_BIT(GPIOA->ODR,u8PinNum);	
		}
	}
	else if (u8PortNum == GPIO_PORTB) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOB->ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOB->ODR,u8PinNum);
		}
	}
	else if (u8PortNum == GPIO_PORTC) {
		if (u8PinValue == STD_HIGH) {
			SET_BIT(GPIOC->ODR,u8PinNum);	
		}
		else {
			CLEAR_BIT(GPIOC->ODR,u8PinNum);
		}
	}
}

u8 GPIO_u8GetPinValue(u8 u8PortNum, u8 u8PinNum) {
	if (u8PortNum == GPIO_PORTA) {
		return (u8)  GET_BIT(GPIOA->IDR,u8PinNum);
	}
	else if(u8PortNum == GPIO_PORTB) {
		return (u8) GET_BIT(GPIOB->IDR,u8PinNum);	
	}
	else if(u8PortNum == GPIO_PORTC) {
		return (u8) GET_BIT(GPIOC->IDR,u8PinNum);
	}
	return 0;
}

void GPIO_vidSetPinConfiguration(u8 u8PortNum, u8 u8PinNumCpy, u8 u8ConfCpy) {
	if (u8PinNumCpy < GPIO_PIN8){
		switch (u8ConfCpy) {
			case GPIO_GPOUT_PP:
				if (u8PortNum == GPIO_PORTA) {
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+3);	
				}
				else if (u8PortNum == GPIO_PORTB) {
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_GPOUT_OD:
				if (u8PortNum == GPIO_PORTA) {
					SET_BIT(GPIOA->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					SET_BIT(GPIOB->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum ==  GPIO_PORTC) {
					SET_BIT(GPIOC->CRL,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_AFOUT_PP:
				if (u8PortNum == GPIO_PORTA) {
					CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOA->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOB->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOC->CRL,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_AFOUT_OD:
				if (u8PortNum ==  GPIO_PORTA) {
					SET_BIT(GPIOA->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOA->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					SET_BIT(GPIOB->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOB->CRL,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					SET_BIT(GPIOC->CRL,u8PinNumCpy*4+2);
					SET_BIT(GPIOC->CRL,u8PinNumCpy*4+3);
				}
				break;
		}
	}
	else {
		u8PinNumCpy = u8PinNumCpy - 8;
		switch (u8ConfCpy) {
			case GPIO_GPOUT_PP:
				if (u8PortNum == GPIO_PORTA) {
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+3);	
				}
				else if (u8PortNum == GPIO_PORTB) {
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_GPOUT_OD:
				if (u8PortNum == GPIO_PORTA) {
					SET_BIT(GPIOA->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					SET_BIT(GPIOB->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum ==  GPIO_PORTC) {
					SET_BIT(GPIOC->CRH,u8PinNumCpy*4+2);
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_AFOUT_PP:
				if (u8PortNum == GPIO_PORTA) {
					CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOA->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOB->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOC->CRH,u8PinNumCpy*4+3);
				}
				break;
			case GPIO_AFOUT_OD:
				if (u8PortNum ==  GPIO_PORTA) {
					SET_BIT(GPIOA->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOA->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTB) {
					SET_BIT(GPIOB->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOB->CRH,u8PinNumCpy*4+3);
				}
				else if (u8PortNum == GPIO_PORTC) {
					SET_BIT(GPIOC->CRH,u8PinNumCpy*4+2);
					SET_BIT(GPIOC->CRH,u8PinNumCpy*4+3);
				}
				break;
		}
	}
}

void GPIO_vidSetPinMode(u8 u8PortNumCpy, u8 u8PinNumCpy, u8 u8ModeCpy) {
	if (u8ModeCpy == GPIO_OUTSPEED_10) {
		if (u8PortNumCpy == GPIO_PORTA) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == GPIO_PORTB) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if (u8PortNumCpy == GPIO_PORTC) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
	else if (u8ModeCpy  == GPIO_OUTSPEED_2) {
		if (u8PortNumCpy ==  GPIO_PORTA) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == GPIO_PORTB) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if(u8PortNumCpy == GPIO_PORTC) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
	else if (u8ModeCpy == GPIO_OUTSPEED_50) {
		if (u8PortNumCpy == GPIO_PORTA) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if	(u8PortNumCpy == GPIO_PORTB) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if (u8PortNumCpy == GPIO_PORTC) {
			if (u8PinNumCpy < GPIO_PIN8) {
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4);
				SET_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}
	}
	else if (u8ModeCpy == GPIO_INPUTMODE) {
		if (u8PortNumCpy == GPIO_PORTA) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOA->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOA->CRH,u8PinNumCpy*4+1);
			}
		}
		else if	(u8PortNumCpy == GPIO_PORTB) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOB->CRH,u8PinNumCpy*4+1);
			}
		}
		else if (u8PortNumCpy == GPIO_PORTC) {
			if (u8PinNumCpy < GPIO_PIN8) {
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRL,u8PinNumCpy*4+1);
			}
			else {
				u8PinNumCpy = u8PinNumCpy - 8;
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4);
				CLEAR_BIT(GPIOC->CRH,u8PinNumCpy*4+1);
			}
		}

	}
}

void GPIO_vidTogglePin(u8 u8Port, u8 u8Pin)
{
	switch(u8Port)
	{
		case GPIO_PORTA:
			TOGGLE_BIT(GPIOA->ODR,u8Pin);
			break;
		case GPIO_PORTB:
			TOGGLE_BIT(GPIOB->ODR,u8Pin);
			break;
		case GPIO_PORTC:
			TOGGLE_BIT(GPIOC->ODR,u8Pin);
			break;
	}
}
